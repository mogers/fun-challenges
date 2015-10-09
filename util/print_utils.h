#ifndef _PRINT_UTILS_H_
#define _PRINT_UTILS_H_

#include <iostream>

namespace util {

// Prints the elements of a given collection in a line, separated by spaces.
template<class Container>
inline void PrintCollection(const Container& collection) {
  for (const auto& element : collection) {
    std::cout << element << ' ';
  }
  std::cout << '\n';
}

}  // namespace util. 

#endif 

