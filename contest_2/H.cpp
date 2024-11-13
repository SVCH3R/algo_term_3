#include <vector>
#include <string>
#include <iostream>

int P(const std::string& s) {
  size_t size = s.size();
  if (size == 0) {
    return 0;
  }
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
  return pref.back();
}

void MakePun(std::string& left, const std::string& right) {
  int intersection_size = 0;
  int ls = static_cast<int>(left.size());
  int rs = static_cast<int>(right.size());
  if (ls == 0 || rs == 0) {
    intersection_size = 0;
  } else {
    if (ls > rs) {
      intersection_size = P(right + '$' + left.substr(ls - rs, rs));
    } else {
      intersection_size = P(right + '$' + left);
    }
  }

  left += right.substr(intersection_size, rs - intersection_size);
}

int main() {
  int n = 0;
  std::cin >> n;
  std::string pun;
  std::string s;
  std::cin >> pun;
  for (int i = 1; i < n; ++i) {
    std::cin >> s;
    MakePun(pun, s);
  }
  std::cout << pun << '\n';
}