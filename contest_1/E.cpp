#include <iostream>
#include <vector>

struct FenwickTree {

  std::vector<int64_t> bit;
  int64_t size;

  FenwickTree() = default;

  explicit FenwickTree(const std::vector<int64_t>& array) {
    size = static_cast<int64_t>(array.size());
    bit.resize(size, 0);
    for (int64_t i = 0; i < size; ++i) {
      Update(i, array[i]);
    }
  }

  int64_t Query(const int64_t& k) {
    int64_t sum = 0;
    for (int64_t i = k; i >= 0; i = (i & (i + 1)) - 1) {
      sum += bit[i];
    }
    return sum;
  }

  void Update(const int64_t& k, const int64_t& delta) {
    for (int64_t i = k; i < size; i = i | (i + 1)) {
      bit[i] += delta;
    }
  }

  int64_t Query(const int64_t& l, const int64_t& r) {
    if (l == 0) {
      return Query(r);
    }
    return Query(r) - Query(l - 1);
  }
};

int main() {
  int64_t n = 0;
  int64_t m = 0;
  int64_t l = 0;
  int64_t r = 0;
  char cmd = 0;

  std::cin >> n;
  std::vector<int64_t> array(n);
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> array[i];
  }
  FenwickTree bit(array);

  std::cin >> m;

  while (m--) {
    std::cin >> cmd >> l >> r;
    if (cmd == 's') {
      std::cout << bit.Query(l - 1, r - 1) << ' ';
    } else {

      int64_t delta = r - array[l - 1];
      array[l - 1] = r;
      bit.Update(l - 1, delta);
    }
  }
}