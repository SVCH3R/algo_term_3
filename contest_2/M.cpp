#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>

struct Border {
  int left;
  int right;
  int pattern_idx;
  std::string pattern;
};

struct Node {
  std::unordered_map<char, int> next;
  std::vector<Border> borders;
  int suff_ref;
  int exit_link;
  int pattern_length;
  bool terminal;
  Node() : suff_ref(-1), exit_link(-1), pattern_length(0), terminal(false) {
  }
};

struct Tripple {
  char symbol;
  int parent;
  int state;
  Tripple(char symbol, int parent, int state) : symbol(symbol), parent(parent), state(state) {
  }
};

class Trie {
 private:
  std::vector<Node> trie_;
  std::vector<bool> good_;

 public:
  void Insert(std::string& s) {
    int curr = 0;
    for (const auto& symbol : s) {
      int next = trie_[curr].next[symbol];
      if (next == 0) {
        trie_.emplace_back();
        next = static_cast<int>(trie_.size()) - 1;
        trie_[curr].next[symbol] = next;
      }
      curr = next;
    }
    trie_[curr].terminal = true;
    trie_[curr].pattern_length = static_cast<int>(s.size());
  }

  void AddSymbol(const Border& border) {
    int size = static_cast<int>(border.pattern.size());
    int state = 0;
    for (int i = 0; i < size; ++i) {
      if (trie_[state].next.find(border.pattern[i]) == trie_[state].next.end()) {
        trie_.emplace_back();
        trie_[state].next[border.pattern[i]] = static_cast<int>(trie_.size()) - 1;
      }
      state = trie_[state].next[border.pattern[i]];
    }
    trie_[state].borders.push_back(border);
    trie_[state].pattern_length = size;
    trie_[state].terminal = true;
  }

  void BuildSuffixReferences() {
    std::queue<Tripple> queue;
    for (const auto& i : trie_[0].next) {
      queue.emplace(i.first, 0, i.second);
    }

    while (!queue.empty()) {
      const auto& [symbol, parent, state] = queue.front();
      queue.pop();
      int suff = trie_[parent].suff_ref;
      while (suff != -1 && trie_[suff].next.find(symbol) == trie_[suff].next.end()) {
        suff = trie_[suff].suff_ref;
      }
      trie_[state].suff_ref = suff == -1 ? 0 : trie_[suff].next[symbol];
      for (const auto& [symbol, neighbor] : trie_[state].next) {
        queue.emplace(symbol, state, neighbor);
      }
    }
  }

  void BuildExitLinks() {
    std::queue<int> queue;
    for (const auto& [symbol, state] : trie_[0].next) {
      queue.push(state);
    }

    while (!queue.empty()) {
      int state = queue.front();
      queue.pop();
      int suff = trie_[state].suff_ref;

      if (suff != 0) {
        trie_[state].exit_link = trie_[suff].terminal ? suff : trie_[suff].exit_link;
      }

      for (const auto& [symbol, neighbor] : trie_[state].next) {
        queue.push(neighbor);
      }
    }
  }

  int NextState(int& state, const char& symbol) {
    while (state != -1 && trie_[state].next.find(symbol) == trie_[state].next.end()) {
      state = trie_[state].suff_ref;
    }
    return state == -1 ? 0 : trie_[state].next[symbol];
  }

  void PrintEntries(const int& idx, int state) {
    if (!trie_[state].terminal) {
      state = trie_[state].exit_link;
    }
    while (state != -1) {
      int left = idx - trie_[state].pattern_length + 2;
      int right = idx + 1;
      for (const auto& border : trie_[state].borders) {
        if (border.left <= left && right <= border.right) {
          good_[border.pattern_idx] = true;
        }
      }
      state = trie_[state].exit_link;
    }
  }

  explicit Trie(const std::vector<Border>& borders) {
    trie_.emplace_back();
    for (const auto& border : borders) {
      AddSymbol(border);
    }
    BuildSuffixReferences();
    BuildExitLinks();

    good_.resize(borders.size());
  }

  void AhoCorasick(const std::string& str) {
    int size = static_cast<int>(str.size());
    int state = 0;

    for (int i = 0; i < size; ++i) {
      state = NextState(state, str[i]);
      PrintEntries(i, state);
    }
    for (const auto& i : good_) {
      std::cout << (i ? '+' : '-');
    }
  }
};

int main() {
  std::string s;
  int n = 0;
  std::cin >> s >> n;
  std::vector<Border> borders(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> borders[i].left >> borders[i].right >> borders[i].pattern;
    borders[i].pattern_idx = i;
  }
  Trie tr(borders);
  tr.AhoCorasick(s);
}
