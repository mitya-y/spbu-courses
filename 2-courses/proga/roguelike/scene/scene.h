#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>

#include "base_unit.hpp"
#include <glm/glm.hpp>

#define txt "scene.txt";

class Scene {
private:
  using UnitContainer = std::map<std::string, std::shared_ptr<Unit>>;
  using UnitIter = UnitContainer::iterator;

  UnitContainer _units;

  int _width = 100;
  int _heigh = 100;

public:
  Scene(std::string_view sw);
  /*
    Scene() {}
    Scene(const Scene &other) = default;
    Scene &operator=(const Scene &other) = default;
    Scene(Scene &&other) = default;
    Scene &operator=(Scene &&other) = default;
  */

  ~Scene();

  void save_to_file(std::string_view filename);
  void draw();
  void update();

  template <typename UnitType, typename... Args>
  std::shared_ptr<UnitType> create_unit(std::string name, Args &&...args) {
    auto unit = std::make_shared<UnitType>(args...);
    _units[name] = unit;
    return unit;
  }

  void delete_unit(std::string name);

  glm::vec2 get_bound() { return {0, 0}; }

  UnitIter begin() noexcept { return _units.begin(); }
  UnitIter end() noexcept { return _units.end(); }
};
