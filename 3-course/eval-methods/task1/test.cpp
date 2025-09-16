#include "solver/solver.hpp"

#include <ranges>

static bool test() {
  std::array test_funcs {
    ComputedFunc([](double x) { return x - 10 * std::sin(x); }),
    ComputedFunc([](double x) { return std::pow(2, -x) - std::sin(x); }),
    ComputedFunc([](double x) { return std::pow(2, x) - 2 * std::sin(x); }),
    ComputedFunc([](double x) { return std::sqrt(4 * x + 7) - 3 * std::cos(x); }),
    ComputedFunc([](double x) { return x * std::sin(x) - 1; }),
  };

  std::array test_funcs_ders {
    ComputedFunc([](double x) { return 1 - 10 * std::cos(x); }),
    ComputedFunc([](double x) { return -std::log(2) * std::pow(2, -x) - std::cos(x); }),
    ComputedFunc([](double x) { return std::log(2) * std::pow(2, x) - 2 * std::cos(x); }),
    ComputedFunc([](double x) { return 2 / std::sqrt(4 * x + 7) + 3 * std::sin(x); }),
    ComputedFunc([](double x) { return std::sin(x) + x * std::cos(x); }),
  };

  std::array test_ranges {
    Range(-5, 3),
    Range(-5, 10),
    Range(-8, 10),
    Range(-1.5, 2),
    Range(-10, 2),
  };

  std::array test_eps {
    std::pow(10, -6),
    std::pow(10, -6),
    std::pow(10, -6),
    std::pow(10, -8),
    std::pow(10, -5),
  };

  for (uint32_t i = 0; i < SolveMethod::MethodsNum; i++) {
    auto method = static_cast<SolveMethod>(i);
    if (method == SolveMethod::Newton2) continue;
    for (auto &&[f, df, range, eps] : std::views::zip(test_funcs, test_funcs_ders, test_ranges, test_eps)) {
      double root = solve(range, eps, f, df, method);
      if (std::abs(f(root)) > eps) {
        return false;
      }
    }
    std::println("test of method {} done", solve_method_name(method));
  }

  return true;
}

int main() {
  if (test()) {
    std::println("tests passed");
    return 0;
  } else {
    std::println("tests failed");
    return -1;
  }
}
