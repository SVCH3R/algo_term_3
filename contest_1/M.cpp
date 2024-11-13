#include <iostream>
#include <random>
#include <vector>

const uint32_t kN = 1 << 24;

uint32_t NextRand(const uint32_t& a, const uint32_t& b, uint32_t& cur) {
  cur = cur * a + b;
  return cur >> 8;
}

std::vector<uint32_t> Updates(uint32_t& m, const uint32_t& a, const uint32_t& b, uint32_t& cur) {
  std::vector<uint32_t> result(kN, 0);
  while (m--) {
    uint32_t add = NextRand(a, b, cur);
    uint32_t l = NextRand(a, b, cur);
    uint32_t r = NextRand(a, b, cur);
    if (l > r) {
      std::swap(l, r);
    }
    result[l] += add;
    result[r + 1] -= add;
  }
  return result;
}

// 0 3 0 0-3 0 0
// 0 3 3 3 0 0 0
// 0 3 6 9 9 9 9

uint32_t Queries(const std::vector<uint32_t>& updates, uint32_t& q, const uint32_t& a, const uint32_t& b,
                 uint32_t& cur) {
  uint32_t sum = 0;
  uint32_t curr = 0;
  uint32_t temp = 0;
  std::vector<uint32_t> pref(kN, 0);
  for (uint32_t i = 0; i < kN; ++i) {
    curr += updates[i];
    temp += curr;
    pref[i] = temp;
  }

  while (q--) {
    uint32_t l = NextRand(a, b, cur);
    uint32_t r = NextRand(a, b, cur);
    if (l > r) {
      std::swap(l, r);
    }
    if (l == 0) {
      sum += pref[r];
    } else {
      sum += (pref[r] - pref[l - 1]);
    }
  }
  return sum;
}

int main() {
  uint32_t q = 0;
  uint32_t m = 0;
  std::cin >> m >> q;
  uint32_t a = 0;
  uint32_t b = 0;
  uint32_t cur = 0;
  std::cin >> a >> b;
  std::cout << Queries(Updates(m, a, b, cur), q, a, b, cur);
}