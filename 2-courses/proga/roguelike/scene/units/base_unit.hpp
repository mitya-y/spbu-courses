#pragma once

class Unit {
public:
  virtual void draw() {}
  virtual void update() {}
  // virtual char *serealize() {}
  // virtual Unit deserealize() {}

  Unit(int x = 0, int y = 0) {}
  virtual ~Unit() {}
};

