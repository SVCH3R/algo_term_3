#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> Z(const std::string& s) {
  int size = static_cast<int>(s.size());
  std::vector<int> z(size, 0);
  int left = 0;
  int right = 0;
  for (int i = 1; i < size; ++i) {
    if (i < right) {
      z[i] = std::min(z[i - left], right - i);
    }
    while (i + z[i] < size && s[z[i]] == s[i + z[i]]) {
      ++z[i];
    }
    if (right < i + z[i]) {
      left = i;
      right = i + z[i];
    }
  }
  z[0] = size;
  return z;
}

std::vector<int> KMP(const std::string& s, const std::string& p) {
  int p_size = static_cast<int>(p.size());
  std::string conc(p + '#' + s);
  int c_size = static_cast<int>(conc.size());
  std::vector<int> z(Z(conc));
  std::vector<int> res;

  for (int i = p_size + 1; i < c_size; ++i) {
    if (z[i] == p_size) {
      res.emplace_back(static_cast<int>(i - p_size - 1));
    }
  }
  return res;
}

int main() {
  std::string s;
  std::string p;
  std::cin >> s;
  std::cin >> p;
  auto res = KMP(s, p);
  for (auto i : res) {
    std::cout << i << '\n';
  }
}