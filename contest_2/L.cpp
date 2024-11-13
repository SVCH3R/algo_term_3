#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>

struct Node {
  std::unordered_map<char, int> next;
  int suff_ref;
  int exit_link;
  int pattern_index;
  int pattern_length;
  bool terminal = false;
  Node() = default;
};
struct Tripple {
  char symbol;
  int parent;
  int curr;
  Tripple(const char& csymbol, const int& cpattern, const int& ccurr) : symbol(csymbol), parent(cpattern), curr(ccurr) {
  }
  Tripple() = default;
};

class Trie {
 private:
  std::vector<Node> trie_;
  std::vector<std::vector<int>> result_;

 public:
  explicit Trie(const int& size) {
    std::string dict_str;
    trie_.emplace_back();
    result_.resize(size);
    for (int i = 0; i < size; ++i) {
      std::cin >> dict_str;
      Insert(dict_str, i);
    }
    BuildSuffixReferences();
    BuildExitLinks();
  }

  void Insert(std::string& s, const int& order) {
    int curr = 0;
    for (auto symbol : s) {
      int next = trie_[curr].next[symbol];
      if (next == 0) {
        trie_.emplace_back();
        next = static_cast<int>(trie_.size()) - 1;
        trie_[curr].next[symbol] = next;
      }
      curr = next;
    }
    trie_[curr].terminal = true;
    trie_[curr].pattern_index = order;
    trie_[curr].pattern_length = static_cast<int>(s.size());
  }
  void BuildSuffixReferences() {
    trie_[0].suff_ref = -1;
    std::queue<Tripple> queue;
    for (auto i : trie_[0].next) {
      queue.emplace(i.first, 0, i.second);
    }
    Tripple tmp;
    while (!queue.empty()) {
      tmp = queue.front();
      queue.pop();
      int curr_suff = tmp.parent;
      int curr_link = trie_[curr_suff].suff_ref;
      while ((curr_link != -1) && (trie_[curr_link].next.find(tmp.symbol) == trie_[curr_link].next.end())) {
        curr_link = trie_[curr_suff].suff_ref;
        curr_suff = curr_link;
      }
      if (curr_link == -1) {
        trie_[tmp.curr].suff_ref = 0;
      } else {
        trie_[tmp.curr].suff_ref = trie_[curr_link].next[tmp.symbol];
      }
      for (auto i : trie_[tmp.curr].next) {
        queue.emplace(i.first, tmp.curr, i.second);
      }
    }
  }
  void BuildExitLinks() {
    trie_[0].exit_link = -1;
    std::queue<int> queue;
    for (auto i : trie_[0].next) {
      queue.push(i.second);
    }
    int tmp = 0;
    while (!queue.empty()) {
      tmp = queue.front();
      queue.pop();
      int suff_link = trie_[tmp].suff_ref;
      if (suff_link != 0) {
        if (trie_[suff_link].terminal) {
          trie_[tmp].exit_link = suff_link;
        } else {
          trie_[tmp].exit_link = trie_[suff_link].exit_link;
        }
      }
      for (auto i : trie_[tmp].next) {
        queue.push(i.second);
      }
    }
  }

  int NextState(int node, const char& symbol) {
    while ((node != -1) && (trie_[node].next.find(symbol) == trie_[node].next.end())) {
      node = trie_[node].suff_ref;
    }
    return (node == -1 ? 0 : trie_[node].next[symbol]);
  }

  void PrintEntries(int index, int node) {
    if (!trie_[node].terminal) {
      node = trie_[node].exit_link;
    }
    while ((node != 0) && (node != -1)) {
      result_[trie_[node].pattern_index].push_back(index - trie_[node].pattern_length + 2);
      node = trie_[node].exit_link;
    }
  }

  std::vector<std::vector<int>> GetResult() {
    return result_;
  }
};

void AhoCorasik(std::string& s, int patterns) {
  Trie trie(patterns);
  trie.BuildSuffixReferences();
  trie.BuildExitLinks();

  int node = 0;
  int size = static_cast<int>(s.size());
  for (int i = 0; i < size; ++i) {
    node = trie.NextState(node, s[i]);
    trie.PrintEntries(i, node);
  }
  auto result = trie.GetResult();
  int n = static_cast<int>(result.size());
  for (int i = 0; i < n; ++i) {
    int currsize = static_cast<int>(result[i].size());
    std::cout << currsize << ' ';

    for (int j = 0; j < currsize; ++j) {
      std::cout << result[i][j] << ' ';
    }
    std::cout << '\n';
  }
}
int main() {
  std::string s;
  int n = 0;
  std::cin >> s >> n;

  AhoCorasik(s, n);
}