#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Node {
  std::map<char, int> transitions;
  bool terminal = false;
  Node() = default;
};
class Trie {

 private:
  std::vector<Node> trie_;

 public:
  Trie() {
    Node root;
    trie_.emplace_back(root);
  };

  void Insert(const std::string& s) {
    int state = 0;
    auto size = static_cast<int>(s.size());
    for (int i = 0; i < size; ++i) {
      if (!trie_[state].transitions.count(s[i])) {
        trie_.emplace_back();
        trie_[state].transitions[s[i]] = (static_cast<int>(trie_.size())) - 1;
      }
      state = trie_[state].transitions[s[i]];
    }
    trie_[state].terminal = true;
  }

  bool Find(const std::string& s) {
    int state = 0;
    auto size = static_cast<int>(s.size());
    for (int i = 0; i < size; ++i) {
      if (trie_[state].transitions.count(s[i]) == 0) {
        return false;
      }
      state = trie_[state].transitions[s[i]];
    }
    return trie_[state].terminal;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string s;
  char cmd = 0;
  Trie trie;
  std::cin >> cmd;

  while (cmd != '#') {
    std::cin >> s;
    if (cmd == '+') {
      trie.Insert(s);
    } else {
      if (cmd == '?') {
        if (trie.Find(s)) {
          std::cout << "YES" << '\n';
        } else {
          std::cout << "NO" << '\n';
        }
      }
    }
    std::cin >> cmd;
  }
}