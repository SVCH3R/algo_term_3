#include <iostream>
#include <vector>

struct FenwickTree3D {
  std::vector<std::vector<std::vector<int>>> bit;
  int size;

  explicit FenwickTree3D(const int& n) : size(n) {
    bit.resize(size, std::vector<std::vector<int>>(size, std::vector<int>(size, 0)));
  }

  void Update(const int& x, const int& y, const int& z, const int& delta) {
    for (int i = x; i < size; i |= (i + 1)) {
      for (int j = y; j < size; j |= (j + 1)) {
        for (int k = z; k < size; k |= (k + 1)) {
          bit[i][j][k] += delta;
        }
      }
    }
  }

  int Query(const int& x, const int& y, const int& z) {
    int sum = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
      for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
        for (int k = z; k >= 0; k = (k & (k + 1)) - 1) {
          sum += bit[i][j][k];
        }
      }
    }
    return sum;
  }
};

int main() {
  int n = 0;
  int x = 0;
  int y = 0;
  int z = 0;
  int x1 = 0;
  int y1 = 0;
  int z1 = 0;
  int x2 = 0;
  int y2 = 0;
  int z2 = 0;
  int k = 0;
  int cmd = 0;
  std::cin >> n;

  FenwickTree3D bit(n);

  while (std::cin >> cmd && cmd != 3) {
    if (cmd == 1) {
      std::cin >> x >> y >> z >> k;
      bit.Update(x, y, z, k);
    } else {
      if (cmd == 2) {
        std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
        std::cout << bit.Query(x2, y2, z2) - bit.Query(x1 - 1, y2, z2) - bit.Query(x2, y1 - 1, z2) +
                         bit.Query(x1 - 1, y1 - 1, z2) - bit.Query(x2, y2, z1 - 1) + bit.Query(x1 - 1, y2, z1 - 1) +
                         bit.Query(x2, y1 - 1, z1 - 1) - bit.Query(x1 - 1, y1 - 1, z1 - 1)
                  << '\n';
      }
    }
  }
}
