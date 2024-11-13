#include <cmath>
#include <iostream>
#include <vector>
#include <cstdint>

int Parent(const int &i) {
  return (i - 1) >> 1;
}

int Left(const int &i) {
  return (2 * i + 1);
}

int Right(const int &i) {
  return (2 * i + 2);
}

bool IsLeft(const int &i) {
  return i % 2;
}

bool IsRight(const int &i) {
  return !(i % 2);
}

class SegmentTree {
 private:
  std::vector<int> tree_;
  std::vector<int> promise_;

  void Push(const int &v) {
    tree_[v] += promise_[v];
    promise_[Left(v)] += promise_[v];
    promise_[Right(v)] += promise_[v];
    promise_[v] = 0;
  }

  int Query(int v, int tl, int tr, int left, int right) {
    if (tl >= left && tr <= right) {
      return tree_[v] + promise_[v];
    }
    if (tr < left || tl > right) {
      return 0;
    }

    int tm = ((tl + tr) >> 1);
    Push(v);
    int left_res = Query(Left(v), tl, tm, left, right);
    int right_res = Query(Right(v), tm + 1, tr, left, right);

    return std::max(left_res, right_res);
  }

  void Update(int v, int tl, int tr, int left, int right, const int &add) {
    if (tl >= left && tr <= right) {
      promise_[v] += add;
      return;
    }
    if (tr < left || tl > right) {
      return;
    }
    int tm = ((tl + tr) >> 1);
    Push(v);
    Update(Left(v), tl, tm, left, right, add);
    Update(Right(v), tm + 1, tr, left, right, add);

    tree_[v] = std::max(Query(Left(v), tl, tm, tl, tm), Query(Right(v), tm + 1, tr, tm + 1, tr));
  }

 public:
  SegmentTree() = default;
  explicit SegmentTree(const std::vector<int> &array) {
    int size = static_cast<int>(array.size());
    tree_.resize(2 * size - 1, 0);
    promise_.resize(2 * size - 1, 0);

    for (int i = size - 1; i < 2 * size - 1; ++i) {
      tree_[i] = array[i - size + 1];
    }
    for (int i = size - 2; i >= 0; --i) {
      tree_[i] = std::max(tree_[Left(i)], tree_[Right(i)]);
    }
  }

  int Query(const int &l, const int &r, const int &size) {
    return Query(0, size - 1, 2 * size - 2, l + size - 2, r + size - 2);
  }

  void Update(int l, int r, const int &add, int size) {
    return Update(0, size - 1, 2 * size - 2, l + size - 2, r + size - 2, add);
  }
};

int main() {

  int n = 0;
  std::cin >> n;

  std::vector<int> array(1 << (static_cast<int>(log2(n) + 1)), 0);
  int size = static_cast<int>(array.size());
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i];
  }

  SegmentTree st(array);

  int m = 0;
  int l = 0;
  int r = 0;
  char cmd = 0;
  std::cin >> m;

  for (int j = 0; j < m; ++j) {
    std::cin >> cmd;
    if (cmd == 'm') {
      std::cin >> l >> r;

      std::cout << st.Query(l, r, size) << ' ';
    } else {
      int l = 0;
      int r = 0;
      int add = 0;
      std::cin >> l >> r >> add;
      st.Update(l, r, add, size);
    }
  }
}