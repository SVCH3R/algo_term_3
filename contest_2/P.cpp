#include <iostream>
#include <string>
#include <map>
#include <vector>
struct Node {
  std::map<char, int64_t> transitions;
  int64_t length;
  int64_t end_pos;
  int64_t res;
};
class Automaton {
  std::vector<Node> states_;

  int64_t last_;
  int64_t size_;

 public:
  Automaton() : states_(1), last_(0), size_(0) {
    states_[0].end_pos = -1;
    states_[0].length = 0;
  }
  explicit Automaton(const std::string& s) : states_(2 * s.size()), last_(0), size_(0) {
    states_[0].end_pos = -1;
    states_[0].length = 0;
    for (auto i : s) {
      AddSymbol(i);
    }
  }
  void AddSymbol(const char& c) {
    int64_t curr = ++size_;
    states_[curr].length = states_[last_].length + 1;
    int64_t p = last_;
    while (p != -1 && states_[p].transitions.find(c) == states_[p].transitions.end()) {
      states_[p].transitions[c] = curr;
      p = states_[p].end_pos;
    }
    if (p == -1) {
      states_[curr].end_pos = 0;
    } else {
      int64_t q = states_[p].transitions[c];
      if (states_[q].length == states_[p].length + 1) {
        states_[curr].end_pos = q;
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
        states_[curr].end_pos = size_;
      }
    }
    states_[curr].res = states_[curr].length - states_[states_[curr].end_pos].length + states_[last_].res;
    std::cout << states_[curr].res << '\n';
    last_ = curr;
  }
};

int main() {
  std::string s;
  std::cin >> s;
  Automaton automaton(s);
}