#include <iostream>
#include <vector>

int main() {
  int64_t n = 0;
  std::cin >> n;

  std::vector<int> sus_rate(n);
  for (int64_t i = 0; i < n; i++) {
    std::cin >> sus_rate[i];
  }
  int sus_ans = sus_rate[0];
  int left = 0;
  int right = 0;
  int sus_sum = 0;
  int negative_pos = -1;

  for (int i = 0; i < n; ++i) {
    sus_sum += sus_rate[i];

    if (sus_sum > sus_ans) {
      sus_ans = sus_sum;
      left = negative_pos + 1;
      right = i;
    }

    if (sus_sum < 0) {
      sus_sum = 0;
      negative_pos = i;
    }
  }
  std::cout << left + 1 << ' ' << right + 1 << ' ' << sus_ans;
}
