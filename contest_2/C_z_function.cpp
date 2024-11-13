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

int main() {
  std::string s;
  std::cin >> s;
  std::vector<int> pref = Z(s);
  for (auto i : pref) {
    std::cout << i << ' ';
  }
}