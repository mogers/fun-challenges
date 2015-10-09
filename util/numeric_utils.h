#ifndef _NUMERIC_UTILS_H_
#define _NUMERIC_UTILS_H_

#include <vector>
#include <algorithm>

namespace util {

// For the sake of simplicity, the median is considered to be the middle
// element even when there is an even number of elements.
template<class T>
T NaiveMedian(std::vector<T>& data) {
  std::nth_element(data.begin(), data.begin() + data.size() / 2, data.end());
  return data[data.size() / 2];
}

}  // namespace util. 

#endif 

