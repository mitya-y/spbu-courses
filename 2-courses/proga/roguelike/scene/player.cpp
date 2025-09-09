#include "player.h"
// #include "game_objs.hpp"

Player::Player(const glm::vec2 &pos) : _pos(pos),
	_inventory(20) {};

Player::~Player() = default;

void Player::pick_an_item(Object *_object) {
  std::string choosed = choose_what_take(_object);
  if (choosed == "\0") {
    return;
  }
  Thing t = _object->take_thing(choosed);
  _inventory.add_to_inventory(t);
}

std::string Player::choose_what_take(Object *_object) {
  if (_object->has_thing() == 0) {
    return "\0";
  }
  std::string choose = _object->view_things();
  return choose.substr(0, choose.find(';'));
}
void Player::talk(Person* talker) {}

void Player::draw() {}

void Player::update() {
	auto &app = Application::get_app();
	auto &scene = app.get_scene();

	for (auto &&[name, unit] : scene) {
		Person *pers = dynamic_cast<Person *>(unit.get());
		if (pers == nullptr) {
			continue;
		}
		if (check_next(pers->get_positions())) {
			pers->talk();
		}
	}

	if (app.key_pressed(GLFW_KEY_W)) {
		_pos.y++;
	}
	if (app.key_pressed(GLFW_KEY_A)) {
		_pos.x--;
	}
	if (app.key_pressed(GLFW_KEY_S)) {
		_pos.y--;
	}
	if (app.key_pressed(GLFW_KEY_D)) {
		_pos.x++;
	}
}

