#ifndef _RAND_UTILS_H_
#define _RAND_UTILS_H_

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <limits>
#include <random>
#include <vector>

namespace util {

class RandUtils {
 public:

  template<class T>
  static T SimpleIntRangeRand(T from, T to) {
    static_assert(std::numeric_limits<T>::is_integer,
                  "SimpleIntRangeRand only supports integer types");
    return rand() % (to-from+1) + from;
  }

  template<class T>
  static void GenerateIntVector(int size, T from, T to, std::vector<T>* vec) {
    static_assert(std::numeric_limits<T>::is_integer,
                  "GenerateIntVector only supports integer types");
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<T> distribution(from, to);
    vec->resize(size);
    for (auto& x : *vec) {
      x = distribution(rng);
    }
  }

};

}  // namespace util. 

#endif 
