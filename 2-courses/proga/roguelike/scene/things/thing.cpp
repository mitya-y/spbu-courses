#include "thing.h"

Thing::Thing(const std::string &name, const uint32_t weight, const std::string &description) {
  _name = name;
  _weight = weight;
  _description = description;
}
Thing::~Thing() = default;

std::string Thing::get_name() {
  return _name;
}

uint32_t Thing::get_weight() {
  return _weight;
}

std::string Thing::view_description() {
  return _description;
}

Note::Note(const std::string &containing, const std::string &name, const std::string &description) :
  Thing(name, 1, description) {
  _containing = containing;
}

Note::~Note() = default;

std::string Note::view_containings() {
  return _containing;
}