
#include <iostream>
#include <string>
#include <vector>

std::vector<int> Z2P(const std::vector<int>& z) {
  int size = static_cast<int>(z.size());
  std::vector<int> pref(size, 0);
  for (int i = 1; i < size; ++i) {
    for (int j = z[i] - 1; j >= 0; --j) {
      if (pref[i + j] == 0) {
        pref[i + j] = j + 1;
      } else {
        break;
      }
    }
  }
  return pref;
}

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

std::string Z2S(const std::vector<int>& z) {
  return P2S(Z2P(z));
}

int main() {
  int n = 0;
  std::cin >> n;
  if (n != 0) {
    std::vector<int> z(n, 0);
    for (int i = 0; i < n; ++i) {
      std::cin >> z[i];
    }
    std::cout << Z2S(z);
  }
}
