#include <iostream>
#include <vector>

int main() {
  int64_t n = 0;
  int64_t k = 0;
  int64_t l = 0;
  int64_t r = 0;
  std::cin >> n;

  std::vector<int64_t> rates(n);
  for (int64_t i = 0; i < n; i++) {
    std::cin >> rates[i];
  }

  std::cin >> k;
  std::vector<int64_t> p(n + 1, 0);
  for (int64_t i = 0; i < n; i++) {
    p[i + 1] = p[i] + rates[i];
  }

  for (int64_t i = 0; i < k; i++) {
    std::cin >> l >> r;
    std::cout << p[r] - p[l - 1] << ' ';
  }
}
