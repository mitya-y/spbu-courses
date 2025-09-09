#include <iostream>
#include <memory>

#include "application.hpp"
#include "scene.h"
#include "field.hpp"

int main() {
  Application::get_app();
  Scene roguelike("game");
  roguelike.create_unit<field>("field");
  Application::get_app().start(std::make_unique<Scene>(roguelike));
  std::cout << "cgsg forever\n";
}
