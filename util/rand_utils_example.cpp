#include "rand_utils.h"

#include <cstdio>
#include <vector>
using std::vector;

int main() {
  int from = 0, to = 9;
  vector<int> vec;
  util::RandUtils::GenerateIntVector(10000000, from, to, &vec);
  vector<int> cnt(to-from+1, 0);
  for (int i : vec) {
    ++cnt[i];
  }
  for (int i = from; i <= to; ++i) {
    printf("%3d : %d\n", i, cnt[i-from]);
  }
  return 0;
}
