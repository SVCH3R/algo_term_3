#include <iostream>
#include <vector>
#include <cmath>

class SparseTable {

 private:
  std::vector<std::vector<std::vector<std::vector<int>>>> st_;

 public:
  explicit SparseTable() = default;
  explicit SparseTable(const std::vector<std::vector<int>>& array) {
    int m = static_cast<int>(array.size());
    int n = static_cast<int>(array[0].size());

    int logm = static_cast<int>(log2(m)) + 1;
    int logn = static_cast<int>(log2(n)) + 1;

    st_.assign(m, std::vector<std::vector<std::vector<int>>>(
                      logm, std::vector<std::vector<int>>(n, std::vector<int>(logn, 0))));

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        st_[i][0][j][0] = array[i][j];
      }
    }

    for (int k1 = 1; k1 < logm; ++k1) {
      for (int i = 0; i + (1 << k1) <= m; ++i) {
        for (int j = 0; j < n; ++j) {
          st_[i][k1][j][0] = std::min(st_[i][k1 - 1][j][0], st_[i + (1 << (k1 - 1))][k1 - 1][j][0]);
        }
      }
    }

    for (int k1 = 0; k1 < logm; ++k1) {
      for (int k2 = 1; k2 < logn; ++k2) {
        for (int i = 0; i < m; ++i) {
          for (int j = 0; j + (1 << k2) <= n; ++j) {
            st_[i][k1][j][k2] = std::min(st_[i][k1][j][k2 - 1], st_[i][k1][j + (1 << (k2 - 1))][k2 - 1]);
          }
        }
      }
    }
  }

  int Query(const int& x1, const int& y1, const int& x2, const int& y2) {
    int k1 = static_cast<int>(log2(x2 - x1 + 1));
    int k2 = static_cast<int>(log2(y2 - y1 + 1));

    return std::min(std::min(st_[x1][k1][y1][k2], st_[x1][k1][y2 - (1 << k2) + 1][k2]),
                    std::min(st_[x2 - (1 << k1) + 1][k1][y1][k2], st_[x2 - (1 << k1) + 1][k1][y2 - (1 << k2) + 1][k2]));
  }
};

int main() {
  int m = 0;
  int n = 0;
  std::cin >> m >> n;

  std::vector<std::vector<int>> array(m, std::vector<int>(n));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> array[i][j];
    }
  }

  SparseTable st(array);

  int q = 0;
  int x1 = 0;
  int y1 = 0;
  int x2 = 0;
  int y2 = 0;
  std::cin >> q;

  while (q--) {
    std::cin >> x1 >> y1 >> x2 >> y2;
    std::cout << st.Query(--x1, --y1, --x2, --y2) << '\n';
  }
}
