void Player::pick_an_item(Object &object) {
  auto choosed = choose_what_thing(object);
  if (choosed == "\0") {
    return;
  }
  auto t = object.take_thing(choosed);
  _inventory.add_to_inventory(*t);
}

std::string choose_what_thing(Object &object) {
  //player must decide what thing is he taking
  if (object.has_thing() == false) {
    return "\0";
  }
  std::string all_things = object.view_all_things();
  return all_things.substr(0, all_things.find(';')); 
}


