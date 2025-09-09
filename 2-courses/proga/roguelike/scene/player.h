#pragma once

#include "inventory.h"
#include "scene.h"
#include "application.hpp"
#include "game_objs.hpp"

class Player : public Unit {
private:
	glm::vec2 _pos {};
	Inventory _inventory;

public:
	Player(const glm::vec2 &pos = {});

	~Player() override;

	void pick_an_item(Object *_object);
	std::string choose_what_take(Object *_object);

	void talk(Person* talker);

	void draw() override;

	void update() override;

private:
	bool check_next(glm::vec2 position) { return false; }
};