#include "solver/solver.hpp"

namespace constants {
  constexpr static double pi = M_PI;
  constexpr static double sphere_volume_coef = pi * (4.0 / 3.0);
  constexpr static double water_density = 1000;
}

static double sphere_volume(double radius) {
  return std::pow(radius, 3) * constants::sphere_volume_coef;
}

// radius in m, density must be in kg/m^3
double calculate_depth(double radius, double density) {
  double underwater_volume = (density * sphere_volume(radius)) / constants::water_density;
  ComputedFunc f = [&](double h) {
    return (constants::pi * pow(h, 2) * (3 * radius - h)) / 3 - underwater_volume;
  };
  auto ranges = split_ranges(Range(0, radius * 2.1), f);
  if (ranges.empty()) {
    throw std::runtime_error("can not solve with parameters radius = {}, density = {}");
  }
  const auto &range = ranges[0];
  double eps = std::pow(10.0, -6);
  double h = solve(range, eps, f, nullptr, SolveMethod::Bissection);
  return h;
}

static void print_table(double radius = 0.62) {
  using Row = std::pair<std::string_view, double>;
  static std::array table {
    Row("Пробка        ", 250),
    Row("Бамбук        ", 400),
    Row("Сосна         ", 500),
    Row("Кедр          ", 550),
    Row("Дуб           ", 700),
    Row("Бук           ", 750),
    Row("Красное дерево", 800),
    Row("Тиковое дерево", 850),
    Row("Парафин       ", 900),
    Row("Лед/Полиэтилен", 920),
    Row("Пчелиный воск ", 950),
  };

  std::println("radius = {}", radius);
  for (auto &&[name, density] : table) {
    std::println("{} | {} kg/m^3 | {:.3}", name, density, calculate_depth(radius, density));
  }
}

int main() {
  std::println("Finding ball underwater depth");

  print_table();

  double radius;
  std::print("input radius (m): ");
  std::cin >> radius;
  double density;
  std::print("input density (kg/m^3): ");
  std::cin >> density;

  double depth = calculate_depth(radius, density);
  std::println("underwater depth is {}", depth);
}