#pragma once

#include <string>
#include <cstdint>

class Thing {
private:
  std::string _name;
  uint32_t _weight;
  std::string _description;
public:
  Thing(const std::string &name, const uint32_t weight, const std::string &description);
  ~Thing();

  std::string view_description();

  std::string get_name();

  uint32_t get_weight();
};

class Note : public Thing {
private:
  std::string _containing;
public:
  Note(const std::string &containing, const std::string &name, const std::string &description);
  ~Note();

  std::string view_containings();
};

//other things