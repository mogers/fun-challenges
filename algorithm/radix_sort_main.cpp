#include "radix_sort.h"
#include "../util/rand_utils.h"
#include "../util/time_measure.h"

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <limits>
#include <vector>

typedef unsigned long long uint64;

template<class T>
class RadixSortInstance {
 public:

  RadixSortInstance() { }

  const std::vector<T>& GetData() { return data; }

  void InitWithRandomData(int size, T from, T to) {
    util::RandUtils::GenerateIntVector(size, from, to, &data);
  }

  void RunTomekVersion() {
    algorithm::RadixSortTomek<T>(data);
  }

 private:
  std::vector<T> data;

};

void RunPerformanceTest(int data_size) {
  RadixSortInstance<uint64> instance;
  instance.InitWithRandomData(data_size, 0, std::numeric_limits<uint64>::max());

  std::function<void(RadixSortInstance<uint64>&)> f_run =
      &RadixSortInstance<uint64>::RunTomekVersion;
  util::ReportTime(instance, f_run);
}

int main(int argc, char* argv[]) {
  int data_size = 100000;
  if (argc > 1) {
    data_size = atoi(argv[1]);
  }
  RunPerformanceTest(data_size);
  return 0;
}
