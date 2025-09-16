#include <set>
#include "muParser.h"

#include "solver/solver.hpp"

static ComputedFunc str2func(std::string_view str) {
  static std::array<std::pair<double, mu::Parser>, 10000> _variables;
  static uint32_t _variables_size = 0;

  auto &[var, parser] = _variables[_variables_size++];
  parser.DefineVar("x", &var);

  parser.SetExpr(str.data());

  return [&var, &parser] (double x) { var = x; return parser.Eval(); };
}

static ComputedFunc parse_function() {
  std::println("input function of x: ");
  std::getchar();
  std::string func;
  std::getline(std::cin, func);
  return str2func(func);
}

void interractive_solve(const Range &range, ComputedFunc f, ComputedFunc df) {
  std::vector<Range> choosed;
  size_t prev_size = 0;
  while (true) {
    std::print("input step_number: ");
    uint32_t step_num;
    std::cin >> step_num;

    auto change_sign_ranges = split_ranges(range, f, step_num);

    std::println("ranges with sign changing{}:",
      change_sign_ranges.size() != prev_size ? " (new ranges found)" : "");
    prev_size = change_sign_ranges.size();
    for (uint32_t i = 0; i < change_sign_ranges.size(); i++) {
      std::println("  {}: {}", i, change_sign_ranges[i].to_str());
    }
    std::println("");

    std::print("input 0 to end or -1 to repeat: ");
    int res = 0;
    std::cin >> res;
    if (res == 0) {
      choosed = std::move(change_sign_ranges);
      break;
    }
  }

  while (true) {
    std::print("input range number: ");
    int range_idx = 0;
    std::cin >> range_idx;

    if (range_idx >= choosed.size()) {
      throw std::runtime_error(std::format("invalid range_idx: {}", range_idx));
    }

    auto choosed_range = choosed[range_idx];

    std::print("input eps: ");
    double eps;
    std::cin >> eps;

    std::print("choose method (-1 - all, {} - {}, {} - {}, {} - {}, {} - {}): ",
      std::to_underlying(SolveMethod::Bissection), solve_method_name(SolveMethod::Bissection),
      std::to_underlying(SolveMethod::Newton), solve_method_name(SolveMethod::Newton),
      std::to_underlying(SolveMethod::Newton2), solve_method_name(SolveMethod::Newton2),
      std::to_underlying(SolveMethod::Secants), solve_method_name(SolveMethod::Secants));
    int solve_method;
    std::cin >> solve_method;

    enable_logs();
    if (solve_method == -1) {
      for (int i = 0; i < SolveMethod::MethodsNum; i++) {
        SolveMethod method = static_cast<SolveMethod>(i);
        std::println("---------------------------------------------------");
        double root = solve(choosed_range, eps, f, df, method);
        std::println("root = {}", root);
      }
    } else {
      double root = solve(choosed_range, eps, f, df, static_cast<SolveMethod>(solve_method));
      std::println("root = {}", root);
    }
    disbale_logs();
  }
}

static double default_f(double x) { return std::pow(x - 2, 2) - 1; }
static double default_df(double x) { return 2 * (x - 2); }

int main() {
  std::println("Finding function roots");

  ComputedFunc f = default_f, df = default_df;
  std::string_view func = "(x - 2)^2 - 1";
  std::println("function: {}", func);
  // f = str2func(func);
  // f = parse_function();

  auto range = Range::parse();

  interractive_solve(range, f, df);
}
