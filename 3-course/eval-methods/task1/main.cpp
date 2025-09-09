#include <iostream>
#include <print>
#include <functional>
#include <numeric>

#include "muParser.h"

using ComputedFunc = std::function<double(double)>;

struct Range {
  double start = 0, end = 0;

  static Range parse() {
    Range range;
    std::print("input range start: ");
    std::cin >> range.start;
    std::print("input range end: ");
    std::cin >> range.end;
    return range;
  }

  Range(double start = 0, double end = 0) : start(start), end(end) {}
  std::string to_str() const {
    return std::format("[{}, {}]", start, end);
  }
  double length() const { return end - start; }
  std::tuple<double, double> bounds() const { return {start, end}; }
};

static double bissection_method(const Range &range, double eps, ComputedFunc input_func) {
  auto [start, end] = range.bounds();
  auto func = input_func;
  if (std::abs(func(start)) < eps) {
    return start;
  }
  if (std::abs(func(end)) < eps) {
    return end;
  }

  // We always work with increased function - this change is not make sense for root
  if (func(end) < 0) {
    func = [input_func](double x) { return -input_func(x); };
  }

  while (true) {
    double mid = std::midpoint(start, end);
    double value = func(mid);
    if (std::abs(value) <= eps) {
      return mid;
    }
    if (value > 0) {
      end = mid;
    } else {
      start = mid;
    }
  }
  return std::numeric_limits<double>::max();
}

static double newton_method(const Range &range, double eps, ComputedFunc func, ComputedFunc df) {
  double x = std::midpoint(range.start, range.end);
  while (std::abs(func(x)) >= eps) {
    x = x - (func(x) / df(x));
  }
  return x;
}

static double updated_newton_method(const Range &range, double eps, ComputedFunc func, ComputedFunc df) {
  double x = std::midpoint(range.start, range.end);
  double dfx0 = df(x);
  while (std::abs(func(x)) >= eps) {
    x = x - (func(x) / dfx0);
  }
  return x;
}

static double method_secants(const Range &range, double eps, ComputedFunc func) {
  double x0 = range.start;
  double x1 = range.end;
  while (std::abs(func(x1)) >= eps) {
    auto save = x1;
    double fx1 = func(x1);
    double inv_df = (x1 - x0) / (fx1 - func(x0));
    x1 = x1 - (fx1 * inv_df);
    x0 = save;
  }
  return x1;
}

std::vector<Range> split_ranges(const Range &range, ComputedFunc f, ComputedFunc df,
                                uint32_t step_numbers = 40) {
 std::vector<Range> change_sign_ranges;
  double step = range.length() / step_numbers;
  double start = range.start;
  for (uint32_t i = 0; i < step_numbers; i++) {
    double end = start + step;
    if (f(start) * f(end) <= 0) {
      change_sign_ranges.emplace_back(start, end);
    }
    start = end;
  }
  return change_sign_ranges;
}

std::vector<float> solve(const Range &range, float eps, ComputedFunc f, ComputedFunc df) {
  auto change_sign_ranges = split_ranges(range, f, df);

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

  // double root = bissection_method(change_sign_ranges[range_idx], eps, f);
  // double root = newton_method(change_sign_ranges[range_idx], eps, f, df);
  // double root = updated_newton_method(change_sign_ranges[range_idx], eps, f, df);
  double root = method_secants(change_sign_ranges[range_idx], eps, f);
  std::println("root = {}\n\n", root);

  return {};
}

static double default_f(double x) { return x * x - 1; }
static double default_df(double x) { return 2 * x; }

int main() {
  auto range = Range::parse();
  std::print("input eps: ");
  double eps;
  std::cin >> eps;
  solve(range, eps, default_f, default_df);
}