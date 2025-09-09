#include <iostream>
#include <stdexcept>

#include "scene.h"

Scene::Scene(std::string_view sw) {
  std::cout << "scene constructor" << std::endl;
}
Scene::~Scene() {
  std::cout << "scene distructor" << std::endl;
}

void Scene::save_to_file(std::string_view filename) {}

void Scene::draw() {
  for (auto &[_, unit] : _units) {
    unit->draw();
  }
}

void Scene::update() {
  for (auto &[_, unit] : _units) {
    unit->update();
  }
}

void Scene::delete_unit(std::string name) {
  if (!_units.contains(name)) {
    throw std::runtime_error("unit now exists");
  }
  _units.erase(_units.find(name));
}
