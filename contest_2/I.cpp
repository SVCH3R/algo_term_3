#include <iostream>
#include <string>
#include <vector>

std::vector<int> PalindromeLength(const std::vector<int>& array) {
  int size = static_cast<int>(array.size());
  std::vector<int> palindrome(size, 0);
  int left = 0;
  int right = 0;
  for (int i = 1; i < size; ++i) {
    if (i <= right) {
      palindrome[i] = std::max(std::min(right - i + 1, palindrome[right - i + 1 + left]), 0);
    }
    while ((i + palindrome[i] < size) && (i - palindrome[i] - 1 >= 0) &&
           (array[i + palindrome[i]] == array[i - palindrome[i] - 1])) {
      ++palindrome[i];
    }
    if (i + palindrome[i] - 1 > right) {
      left = i - palindrome[i];
      right = i + palindrome[i] - 1;
    }
  }
  return palindrome;
}
int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<int> array(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i];
  }

  std::vector<int> palindrome = PalindromeLength(array);
  for (int i = n; i > 0; --i) {
    if (palindrome[i - 1] - i + 1 == 0) {
      std::cout << n - palindrome[i - 1] << ' ';
    }
  }
}