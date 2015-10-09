#ifndef _PRINT_UTILS_H_
#define _PRINT_UTILS_H_

#include <iostream>
#include <vector>

namespace util {

template<class T>
inline void PrintVector(const std::vector<T>& vec) {
  for (const auto& element : vec) {
    std::cout << element << ' ';
  }
  std::cout << '\n';
}

}  // namespace util. 

#endif 

