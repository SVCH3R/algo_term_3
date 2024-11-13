#include <iostream>
#include <string>
#include <vector>
std::vector<int> Z(const std::string& s) {
  int size = static_cast<int>(s.size());
  std::vector<int> z(size, 0);
  int left = 0;
  int right = 0;
  for (int i = 1; i < size; ++i) {
    if (i < right) {
      z[i] = std::min(z[i - left], right - i);
    }
    while (i + z[i] < size && s[z[i]] == s[i + z[i]]) {
      ++z[i];
    }
    if (right < i + z[i]) {
      left = i;
      right = i + z[i];
    }
  }
  z[0] = size;
  return z;
}
int main() {
  int zachem = 0;
  std::cin >> zachem;
  std::string b;
  std::string a;
  std::cin >> a >> b;
  int first_size = static_cast<int>(a.size());
  int counter = 0;
  bool is_zero = false;
  int new_size = 3 * first_size + 2;

  std::string abob(a + '#' + b + '0' + b);
  std::vector<int> zf = Z(abob);
  for (int i = first_size + 1; i < new_size; ++i) {
    if (zf[i] == first_size) {
      ++counter;
      is_zero = true;
      break;
    }
  }

  std::string ab1b(a + '#' + b + '1' + b);
  zf = Z(ab1b);
  for (int i = first_size + 1; i < new_size; ++i) {
    if (zf[i] == first_size) {
      ++counter;
      break;
    }
  }

  if (counter == 2) {
    std::cout << "Random";
  } else if (is_zero) {
    std::cout << "No";
  } else {
    std::cout << "Yes";
  }
}