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

void interractive_solve(const Range &range, float eps, ComputedFunc f, ComputedFunc df) {
  auto change_sign_ranges = split_ranges(range, f);

  std::println("ranges with sign changing:");
  for (uint32_t i = 0; i < change_sign_ranges.size(); i++) {
    std::println("  {}: {}", i, change_sign_ranges[i].to_str());
  }
  std::println("");
  std::print("choose range: ");
  uint32_t range_idx = 0;
  std::cin >> range_idx;
  if (range_idx >= change_sign_ranges.size()) {
    throw std::runtime_error(std::format("invalid range_idx: {}", range_idx));
  }

  std::print("choose method ({} - {}, {} - {}, {} - {}, {} - {}): ",
    std::to_underlying(SolveMethod::Bissection), solve_method_name(SolveMethod::Bissection),
    std::to_underlying(SolveMethod::Newton), solve_method_name(SolveMethod::Newton),
    std::to_underlying(SolveMethod::Newton2), solve_method_name(SolveMethod::Newton2),
    std::to_underlying(SolveMethod::Secants), solve_method_name(SolveMethod::Secants));
  uint32_t solve_method;
  std::cin >> solve_method;

  enable_logs();
  double root = solve(change_sign_ranges[range_idx], eps, f, df, static_cast<SolveMethod>(solve_method));
  disbale_logs();

  std::println("root = {}", root);
}

static double default_f(double x) { return std::pow(x - 2, 2) - 1; }
static double default_df(double x) { return 2 * (x - 2); }

int main() {
  std::println("Finding function roots");

  auto range = Range::parse();
  std::print("input eps: ");
  double eps;
  std::cin >> eps;

  ComputedFunc f = default_f, df = default_df;
  std::string_view func = "(x - 2)^2 - 1";
  std::println("function: {}", func);
  // f = str2func(func);
  // f = parse_function();
  interractive_solve(range, eps, f, df);
}
