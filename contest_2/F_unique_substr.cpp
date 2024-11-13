#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

int SubstrNumber(const std::string& s) {
  int size = static_cast<int>(s.size());
  int res = 1;
  std::string new_str;
  for (int i = 1; i < size; ++i) {
    std::string rev(std::make_reverse_iterator(s.begin() + i), s.rend());
    new_str = s[i] + rev;
    int maxpf = -1;
    auto pf = P(new_str);
    for (auto i : pf) {
      if (i > maxpf) {
        maxpf = i;
      }
    }
    res += i + 1 - maxpf;
  }
  return res;
}

int main() {
  std::string s;
  std::cin >> s;
  std::cout << SubstrNumber(s);
}