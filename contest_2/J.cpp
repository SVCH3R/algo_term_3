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
int main() {
  std::string s;
  std::string t;
  std::cin >> s >> t;
  std::vector<int> z = Z(s + '$' + t);
  int ssize = static_cast<int>(s.size()) + 1;
  int tsize = static_cast<int>(t.size());
  int size = ssize + tsize;
  int maxpos = ssize;
  std::vector<int> prefs(tsize);
  int wordsnumber = 0;

  if (z[ssize] != 0) {
    for (int i = ssize; i < size; ++i) {
      if (maxpos <= z[i] + i) {
        maxpos = z[i] + i;
        prefs[wordsnumber] = i;
        ++wordsnumber;
      }
      if ((i >= maxpos) && (z[i] == 0)) {
        std::cout << "Yes";
        return 0;
      }
    }
  } else {
    std::cout << "Yes";
    return 0;
  }

  std::cout << "No" << '\n';
  int prefend = prefs[1] - ssize;
  int prefstart = 0;
  for (int i = 1; i < wordsnumber; ++i) {
    std::cout << t.substr(prefstart, prefend - prefstart);

    std::cout << ' ';
    prefstart = prefend;
    prefend = prefs[(i + 1) % tsize] - ssize;
  }
  std::cout << t.substr(prefstart, tsize - prefstart);
}
