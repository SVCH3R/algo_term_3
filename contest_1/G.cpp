#include <cmath>
#include <iostream>
#include <vector>
#include <cstdint>

int64_t Parent(const int64_t &i) {
  return (i - 1) >> 1;
}

int64_t Left(const int64_t &i) {
  return (2 * i + 1);
}

int64_t Right(const int64_t &i) {
  return (2 * i + 2);
}

bool IsLeft(const int64_t &i) {
  return i % 2;
}

bool IsRight(const int64_t &i) {
  return !(i % 2);
}

class SegmentTree {
 private:
  std::vector<int64_t> tree_;

  int64_t Query(int64_t v, int64_t tl, int64_t tr, int64_t left, int64_t right) {
    if (tl >= left && tr <= right) {
      return tree_[v];
    }
    if (tr < left || tl > right) {
      return 0;
    }

    int64_t tm = ((tl + tr) >> 1);
    int64_t left_res = Query(Left(v), tl, tm, left, right);
    int64_t right_res = Query(Right(v), tm + 1, tr, left, right);

    return std::max(left_res, right_res);
  }

  int64_t Count(int64_t v, int64_t tl, int64_t tr, int64_t left, int64_t right, int64_t x) {
    if (tl >= left && tr <= right) {
      return tree_[v] == x;
    }
    if (tr < left || tl > right) {
      return 0;
    }

    int64_t tm = ((tl + tr) >> 1);
    int64_t left_count = Count(Left(v), tl, tm, left, right, x);
    int64_t right_count = Count(Right(v), tm + 1, tr, left, right, x);

    return left_count + right_count;
  }

 public:
  SegmentTree() = default;
  explicit SegmentTree(const std::vector<int64_t> &array) {
    auto size = static_cast<int64_t>(array.size());
    tree_.resize(2 * size - 1, 0);

    for (int64_t i = size - 1; i < 2 * size - 1; ++i) {
      tree_[i] = array[i - size + 1];
    }
    for (int64_t i = size - 2; i >= 0; --i) {
      tree_[i] = std::max(tree_[Left(i)], tree_[Right(i)]);
    }
  }

  int64_t Query(const int64_t &l, const int64_t &r, const int64_t &size) {
    return Query(0, size - 1, 2 * size - 2, l + size - 2, r + size - 2);
  }

  int64_t Count(int64_t l, int64_t r, int64_t x, const int64_t &size) {
    return Count(0, size - 1, 2 * size - 2, l + size - 2, r + size - 2, x);
  }
};

int main() {

  int64_t n = 0;
  std::cin >> n;

  std::vector<int64_t> array(1 << (static_cast<int>(log2(n) + 1)), 0);
  auto size = static_cast<int64_t>(array.size());
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> array[i];
  }

  SegmentTree st(array);

  int64_t q = 0;
  int64_t l = 0;
  int64_t r = 0;
  std::cin >> q;

  while (q--) {
    std::cin >> l >> r;
    int64_t max = st.Query(l, r, size);
    std::cout << max << ' ' << st.Count(l, r, max, size) << '\n';
  }
}