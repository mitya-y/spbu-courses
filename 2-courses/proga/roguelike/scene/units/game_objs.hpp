#pragma once

#include <glm/glm.hpp>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "base_unit.hpp"
#include "thing.h"

class Tree {
public:
  struct Node {
    std::string phrase;
    struct tnode *left;
    struct tnode *right;
  };
};

class Person : public Unit {
protected:
  Tree _tree_of_phrases;

public:
  virtual void talk() = 0;

  glm::vec2 get_positions() { return glm::vec2(0); }

  Person(glm::vec2 pos, Tree tree_of_phrases)
      : Unit((int)pos.x, (int)pos.y), _tree_of_phrases(tree_of_phrases){};
  ~Person() override = default;
};

class Object : public Unit {
protected:
  std::map<std::string, Thing> _container;

public:
  bool has_thing() { return _container.size() > 0 ? true : false; }

  Thing take_thing(std::string &name) {
    auto iter = _container.find(name);
    if (iter == _container.end()) {
      throw std::runtime_error("incorrect name to take");
    }
    Thing tmp = std::move(iter->second);
    _container.erase(name);
    return tmp;
  }

  std::string view_things() {
    std::string s = "";

    for (auto &item : _container) {
      s += item.first;
      s += ";";
    }

    return s;
  }

  Object(glm::vec2 pos, std::map<std::string, Thing> container)
      : Unit((int)pos.x, (int)pos.y), _container(container){};
  ~Object() override = default;
};

class Table : public Unit {
private:
  glm::vec3 pos;
  bool has_book;

public:
  Table(int x = 0, int y = 0) {}

  void set_pos(int x = 0, int y = 0, int z = 0) { pos = glm::vec3(x, y, z); }

  void add_book() { has_book = true; }

  void draw() override {}

  void update() override {}

  ~Table() {}
};
