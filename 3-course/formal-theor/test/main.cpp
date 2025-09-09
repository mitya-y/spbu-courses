#include <print>
#include <vector>
#include <string>
#include <iostream>

bool check(std::string_view line) {
  std::vector<char> stack;
  for (auto c : line) {
    if (c == '(' || c == '[') {
      stack.push_back(c);
    } else if (c == ')') {
      char p = stack.back();
      stack.pop_back();
      if (p != '(') {
        return false;
      }
    } else if (c == ']') {
      char p = stack.back();
      stack.pop_back();
      if (p != '[') {
        return false;
      }
    } else if (c == ' ') {
      continue;
    } else {
      std::println("invalid character {}", c);
    }
  }
  return stack.empty();
}

int main() {
  std::string line;
  std::cin >> line;
  std::println("sequence is {}", check(line) ? "valid" : "invalid");
}