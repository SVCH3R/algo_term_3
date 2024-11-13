#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  int k = 0;
  int l = 0;
  int r = 0;
  std::cin >> n >> k;

  std::vector<int> shows(n);
  for (int i = 0; i < n; i++) {
    std::cin >> shows[i];
  }

  std::vector<std::vector<int>> st(n, std::vector<int>(static_cast<int>(log2(n) + 1), 0));

  for (int i = 0; i < n; i++) {
    st[i][0] = shows[i];
  }

  for (int j = 1; (1 << j) <= n; ++j) {
    for (int i = 0; i + (1 << j) <= n; ++i) {
      st[i][j] = std::min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
  }
  std::vector<std::pair<int, int>> querry;
  for (int i = 0; i < k; i++) {
    std::cin >> l >> r;
    --l;
    --r;
    querry.emplace_back(l, r);
  }
  for (auto i : querry) {
    int j = static_cast<int>(log2(i.second - i.first + 1));
    std::cout << std::min(st[i.first][j], st[i.second - (1 << j) + 1][j]) << '\n';
  }
}
