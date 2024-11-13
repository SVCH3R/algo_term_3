#include <iostream>
#include <string>
#include <vector>

std::vector<int> P(const std::string& s) {
  size_t size = s.size();
  std::vector<int> pref(size, 0);
  pref[0] = 0;
  int k = 0;
  for (size_t i = 1; i < size; ++i) {
    k = pref[i - 1];
    while (k > 0 && s[i] != s[k]) {
      k = pref[k - 1];
    }
    if (s[i] == s[k]) {
      ++k;
    }
    pref[i] = k;
  }
  return pref;
}

int main() {
  std::string s;
  std::cin >> s;
  std::vector<int> pref = P(s);
  for (auto i : pref) {
    std::cout << i << ' ';
  }
}