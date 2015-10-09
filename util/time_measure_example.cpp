#include "time_measure.h"

#include <functional>

class Example {
 public:
  Example() {}

  void test() {
    int sum = 0;
    for (int i = 0; i < 1000000; i++) {
      int j = i * 2;
      sum += j;
    }
    sum = sum - 10;
  }
};

void fun() {
  int sum = 0;
  for (int i = 0; i < 1000000; i++) {
    int j = i * 2;
    sum += j;
  }
  sum = sum - 10;
}

int main() {
  std::function<void()> f_fun = fun;
  util::ReportMedianTime(f_fun, 50);
  
  Example e;
  std::function<void(Example&)> f_test = &Example::test;
  util::ReportMedianTime(e, f_test, 50);
  return 0;
}
