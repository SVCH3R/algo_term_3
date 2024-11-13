
#include <iostream>
#include <string>
#include <vector>

std::string P2S(const std::vector<int>& pref) {
  std::string s("a");
  size_t size = pref.size();
  for (size_t i = 1; i < size; ++i) {
    if (pref[i] != 0) {
      s += s[pref[i] - 1];
    } else {
      std::vector<bool> is_used(26, false);
      char first = 'a';
      int j = pref[i - 1];
      is_used[0] = true;
      while (j > 0) {
        is_used[s[j] - first] = true;
        j = pref[j - 1];
      }
      char nextletter = 'b';
      while (is_used[nextletter - first]) {
        ++nextletter;
      }
      s += nextletter;
    }
  }
  return s;
}

int main() {
  int n = 0;
  std::cin >> n;
  if (n != 0) {
    std::vector<int> pref(n, 0);
    for (int i = 0; i < n; ++i) {
      std::cin >> pref[i];
    }
    std::cout << P2S(pref);
  }
}
