#include <iostream>
#include <string>
#include <map>
#include <vector>
struct Node {
  int length;
  int link;
  int end_pos;
  std::map<char, int> next;
};
class Automaton {
  int last_;
  std::vector<Node> states_;
  int size_;

 public:
  explicit Automaton(const int& n) : last_(0), states_(2 * n), size_(0) {
    states_[0].link = -1;
    states_[0].length = 0;
    states_[0].end_pos = 0;
  }
  void AddSymbol(const char& c) {
    int new_node = size_ + 1;
    ++size_;
    states_[new_node].length = states_[last_].length + 1;
    states_[new_node].end_pos = states_[new_node].length - 1;
    int p = last_;
    while (p != -1 && states_[p].next.find(c) == states_[p].next.end()) {
      states_[p].next[c] = new_node;
      p = states_[p].link;
    }
    if (p == -1) {
      states_[new_node].link = 0;
    } else {
      int q = states_[p].next[c];
      if (states_[q].length == states_[p].length + 1) {
        states_[new_node].link = q;
      } else {
        ++size_;
        states_[size_].length = states_[p].length + 1;
        states_[size_].next = states_[q].next;
        states_[size_].link = states_[q].link;
        states_[size_].end_pos = states_[q].end_pos;
        while (p != -1 && states_[p].next[c] == q) {
          states_[p].next[c] = size_;
          p = states_[p].link;
        }
        states_[q].link = size_;
        states_[new_node].link = size_;
      }
    }
    last_ = new_node;
  }
  bool Find(const int& i) {
    return states_[states_[last_].link].length < i;
  }

  size_t Size() {
    return size_;
  }

  std::vector<Node> States() {
    return states_;
  }
};
int main() {
  int n = 0;
  char cmd = 0;
  char s = 0;
  int i = 0;
  std::cin >> n;
  Automaton automaton(n);
  while (n--) {
    std::cin >> cmd;
    if (cmd == '+') {
      std::cin >> s;
      automaton.AddSymbol(s);
    } else {
      std::cin >> i;
      if (automaton.Find(i)) {
        std::cout << '+' << '\n';
      } else {
        std::cout << '-' << '\n';
      }
    }
  }
}