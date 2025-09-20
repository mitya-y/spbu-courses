#include <print>
#include <filesystem>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <expected>
#include <assert.h>

enum struct ParseError {
  BracketErr,
  ParseErr,
};

struct Grammar {
  std::string data;
  std::unordered_map<uint32_t, std::string_view>
    terminals,
    not_terminals,
    rules;
};

static std::string read_from_file(std::filesystem::path filename) {
  std::ifstream file(filename, std::ios_base::ate);
  size_t lenght = file.tellg();
  std::string str;
  str.resize(lenght + 1);
  file.seekg(0);
  file.read(str.data(), lenght);
  return str;
}

constexpr static char get_open_pair_bracket(char bracket) {
  switch (bracket) {
    case ')': return '(';
    case ']': return '[';
    case '>': return '<';
    default: return 0;
  }
}

// now only checks correct order
static std::expected<char *, ParseError> handle_brackets(char *current, std::vector<char> &stack) {
  while (*current) {
    if (*current == '(' || *current == '[' || *current == '<') {
      stack.push_back(*current);
    } else if (*current == ')' || *current == ']' || *current == '>') {
      if (stack.empty() || stack.back() != get_open_pair_bracket(*current)) {
        return std::unexpected(ParseError::BracketErr);
      }
      stack.pop_back();
    } else {
      break;
    }
  }
  if (not *current && not stack.empty()) {
    return std::unexpected(ParseError::BracketErr);
  }
  return current;
}

static std::expected<Grammar, ParseError> parse(std::filesystem::path filename) {
  Grammar grammar;
  grammar.data = read_from_file(filename);

  char *current = grammar.data.data();
  std::vector<char> brackets_stack;

  while (*current) {
    auto res = handle_brackets(current, brackets_stack);
    if (not res) {
      return std::unexpected(ParseError::ParseErr);
    }
    current = *res;
  }

  return grammar;
}

int main() {
}