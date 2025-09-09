#include "inventory.h"

Inventory::Inventory(uint32_t capacity) :
  _capacity(capacity), _inventory() {}
Inventory::~Inventory() = default;

void Inventory::add_to_inventory(Thing t) {
  std::string name = t.get_name();
  _inventory.insert({name, t});
  _capacity+=t.get_weight();
}

void Inventory::delete_from_inventory(std::string name) {
  auto iter = _inventory.find(name);
  if (iter == _inventory.end()) {
    throw std::runtime_error("inventory not exists");
  }

  _capacity -= iter->second.get_weight();
  _inventory.erase(iter);
}

std::string Inventory::view_inventory() {
  std::string s = "";

  for(auto &item : _inventory) {
    s += item.first;
    s += ";";
  }

  return s;
}

uint32_t Inventory::size_of_inventory() {
  return _inventory.size();
}