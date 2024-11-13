#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

std::vector<std::vector<int>> Build(const std::vector<int>& array) {
  int n = static_cast<int>(array.size());
  std::vector<std::vector<int>> st(n, std::vector<int>(static_cast<int>(log2(n)) + 1));
  for (int i = 0; i < n; i++) {
    st[i][0] = array[i];
  }
  for (int j = 1; (1 << j) <= n; j++) {
    for (int i = 0; i + (1 << j) <= n; i++) {
      st[i][j] = std::gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
  }
  return st;
}

int Query(const std::vector<std::vector<int>>& st, const int& l, const int& r) {
  int j = static_cast<int>(log2(r - l + 1));
  return std::gcd(st[l][j], st[r - (1 << j) + 1][j]);
}

int main() {
  int n = 0;
  int k = 0;
  int l = 0;
  int r = 0;

  std::cin >> n;

  std::vector<int> array(n);
  for (int i = 0; i < n; i++) {
    std::cin >> array[i];
  }

  std::vector<std::vector<int>> st = Build(array);

  std::cin >> k;

  while (k--) {
    std::cin >> l >> r;
    std::cout << Query(st, l - 1, r - 1) << '\n';
  }
}
