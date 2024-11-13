#include <iostream>
#include <string>
#include <map>
#include <vector>

struct Node {
  std::map<char, int> transitions;
  int length;
  int end_pos;
};

class Automaton {
  std::vector<Node> states_;
  int last_;
  int size_;

 public:
  Automaton() = default;
  explicit Automaton(const std::string& s) : states_(2 * s.size()), last_(0), size_(0) {
    states_[0].end_pos = -1;
    states_[0].length = 0;

    for (auto symbol : s) {
      AddSymbol(symbol);
    }
  }
  void AddSymbol(const char& c) {
    int new_node = size_ + 1;
    ++size_;
    states_[new_node].length = states_[last_].length + 1;
    int p = last_;
    while (p != -1 && states_[p].transitions.find(c) == states_[p].transitions.end()) {
      states_[p].transitions[c] = new_node;
      p = states_[p].end_pos;
    }
    if (p == -1) {
      states_[new_node].end_pos = 0;
    } else {
      int q = states_[p].transitions[c];
      if (states_[q].length == states_[p].length + 1) {
        states_[new_node].end_pos = q;
      } else {
        ++size_;
        states_[size_].length = states_[p].length + 1;
        states_[size_].transitions = states_[q].transitions;
        states_[size_].end_pos = states_[q].end_pos;
        while (p != -1 && states_[p].transitions[c] == q) {
          states_[p].transitions[c] = size_;
          p = states_[p].end_pos;
        }
        states_[q].end_pos = size_;
        states_[new_node].end_pos = size_;
      }
    }
    last_ = new_node;
  }

  size_t Size() {
    return size_;
  }

  std::vector<Node> States() {
    return states_;
  }
};
int main() {
  std::string s;
  std::cin >> s;
  Automaton automaton(s);
  std::cout << automaton.Size() + 1 << '\n';
  auto states = automaton.States();
  size_t size = automaton.Size();
  for (size_t i = 0; i <= size; ++i) {
    for (auto j : states[i].transitions) {
      std::cout << i << ' ' << j.first << ' ' << j.second << '\n';
    }
  }
}