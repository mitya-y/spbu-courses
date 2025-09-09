#pragma once

#include "../../model/model.h"
#include "base_unit.hpp"
#include "game_objs.hpp"

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <vector>

class field : public Unit {
private:
  std::vector<Model> models;
  std::vector<Table> tables;

public:
  field(int x = 0, int y = 0) { load("../scene.txt"); }

  void load(const std::string &path) {
    std::ifstream file(path);

    if (!file) {
      throw std::runtime_error("Can't open file : {" + path + "}");
    }

    int w, h;
    file >> w >> h;
    models.reserve(w * h);
    std::string input;
    float delta_pos_y = 2, delta_pos_x = 2, scale = 2,
          pos_y = -1 * (float(h) / 2) * scale,
          pos_x = -1 * (float(w) / 2) * scale;

    std::cout << pos_y << ", " << pos_y << std::endl;
    models.emplace_back(Model::GeometryType::Plane);
    models.back().load_texture("../datasets/textures/caver.jpg");
    models.back().scale(glm::vec3(w * scale - 1, 0, h * scale));
    models.back().translate(glm::vec3(-1, 0, -1));
    while (file >> input) {
      if (input == "q") {
        break;
      }
      pos_x = -1 * (float(w) / 2) * scale;
      for (const auto x : input) {
        if (x == '*') {
          models.emplace_back("models/box", "box.obj");
          models.back().scale(glm::vec3(1, 1, 1));
          models.back().translate(glm::vec3(pos_x, 0, pos_y));
        } else if (x == 'p') {
          models.emplace_back("models/chair", "chair.obj");
          models.back().scale(glm::vec3(0.03, 0.03, 0.03));
          models.back().translate(glm::vec3(pos_x, 0, pos_y));
          models.back().rotate({0, 1, 1}, M_PI);
          models.back().rotate({0, 0, 1}, M_PI);
          models.back().rotate({0, 0, 1}, M_PI / 2);
          models.back().rotate({0, 0, 1}, 0);
        } else if (x == 'i') {
          models.emplace_back("models/chair", "chair.obj");
          models.back().scale(glm::vec3(0.03, 0.03, 0.03));
          models.back().translate(glm::vec3(pos_x, 0, pos_y));
          models.back().rotate({0, 1, 1}, M_PI);
          models.back().rotate({0, 0, 1}, M_PI);
          models.back().rotate({0, 0, 1}, M_PI);
          models.back().rotate({0, 0, 1}, 0);
        } else if (x == 'l') {
          models.emplace_back("models/chair", "chair.obj");
          models.back().scale(glm::vec3(0.03, 0.03, 0.03));
          models.back().translate(glm::vec3(pos_x, 0, pos_y));
          models.back().rotate({0, 1, 1}, M_PI);
          models.back().rotate({0, 0, 1}, M_PI);
          models.back().rotate({0, 0, 1}, 0);
          models.back().rotate({0, 0, 1}, 0);
        } else if (x == 'q') {
          models.emplace_back("models/chair", "chair.obj");
          models.back().scale(glm::vec3(0.03, 0.03, 0.03));
          models.back().translate(glm::vec3(pos_x, 0, pos_y));
          models.back().rotate({0, 1, 1}, M_PI);
          models.back().rotate({0, 0, 1}, M_PI);
          models.back().rotate({0, 0, 1}, -M_PI / 2);
          models.back().rotate({0, 0, 1}, 0);
        } else if (x == 'c') {
          float has_book = rand() % 2;
          if (has_book) {
            tables.emplace_back(1, 1);
            tables.back().set_pos(pos_x, 0, pos_y);
            tables.back().add_book();
          }
          models.emplace_back("model/book", "book.obj");
          models.back().scale(glm::vec3(0.01, 0.01, 0.01));
          models.back().translate(glm::vec3(pos_x, 0, pos_y));
          models.emplace_back("models/table", "table.obj");
          models.back().scale(glm::vec3(0.01, 0.01, 0.01));
          models.back().translate(glm::vec3(pos_x, 0, pos_y));
        } else if (x == '1') {
          models.emplace_back(Model::GeometryType::Plane);
          models.back().scale(glm::vec3(scale, scale, scale));
          models.back().translate(glm::vec3(pos_x, 0, pos_y));
        } else if (x == '2') {
          models.emplace_back(Model::GeometryType::Plane);
          models.back().scale(glm::vec3(scale, scale, scale));
          models.back().translate(glm::vec3(pos_x, 0, pos_y));
        } else if (x == '3') {
          models.emplace_back(Model::GeometryType::Plane);
          models.back().scale(glm::vec3(scale, scale, scale));
          models.back().translate(glm::vec3(pos_x, 0, pos_y));
        } else if (x == '4') {
          models.emplace_back(Model::GeometryType::Plane);
          models.back().scale(glm::vec3(scale, scale, scale));
          models.back().translate(glm::vec3(pos_x, 0, pos_y));
        }
        pos_x += delta_pos_x;
      }
      pos_y += delta_pos_y;
    }
    file.close();
  }

  void draw() override {
    for (auto &model : models) {
      model.draw();
    }
  }

  void update() override {}

  // char *serealize() override {}
  // Unit deserealize() override {}

  ~field() {}
};
