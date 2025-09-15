#include "solver/solver.hpp"

double sphere_volume(double radius) {
  static constexpr double coef = M_PI * 4.0 / 3.0;
  return std::pow(radius, 3) * coef;
}

double calculate_depth(double radius, double density) {
  return 0;
}

int main() {
  double radius;
  std::print("input radius: ");
  std::cin >> radius;
  double density;
  std::print("input density: ");
  std::cin >> density;

  double depth = calculate_depth(radius, density);
  std::println("depth is {}", depth);
}