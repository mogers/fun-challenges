#ifndef _RADIX_SORT_H_
#define _RADIX_SORT_H_

#include <limits.h>
#include <algorithm>
#include <iostream>
#include <vector>

namespace algorithm {

// Author: Tomek Czajka
// http://sorting-and-searching.blogspot.pt/2015/09/radix-sort-integer-sorting-often-better.html
template<class T>
static void RadixSortTomek(std::vector<T> &data) {
  static_assert(std::numeric_limits<T>::is_integer &&
      !std::numeric_limits<T>::is_signed,
      "radix_sort only supports unsigned integer types");
  constexpr int word_bits = std::numeric_limits<T>::digits;

  // max_bits = floor(log n / 3)
  // num_groups = ceil(word_bits / max_bits)
  int max_bits = 1;
  while ((size_t(1) << (3 * (max_bits+1))) <= data.size()) {
    ++max_bits;
  }
  const int num_groups = (word_bits + max_bits - 1) / max_bits;

  // Temporary arrays.
  std::vector<size_t> count;
  std::vector<T> new_data(data.size());

  // Iterate over bit groups, starting from the least significant.
  for (int group = 0; group < num_groups; ++group) {
    // The current bit range.
    const int start = group * word_bits / num_groups;
    const int end = (group+1) * word_bits / num_groups;
    const T mask = (size_t(1) << (end - start)) - T(1);

    // Count the values in the current bit range.
    count.assign(size_t(1) << (end - start), 0);
    for (const T &x : data) ++count[(x >> start) & mask];

    // Compute prefix sums in count.
    size_t sum = 0;
    for (size_t &c : count) {
      size_t new_sum = sum + c;
      c = sum;
      sum = new_sum;
    }

    // Shuffle data elements.
    for (const T &x : data) {
      size_t &pos = count[(x >> start) & mask];
      new_data[pos++] = x;
    }

    // Move the data to the original array.
    data.swap(new_data);
  }
}

}  // namespace algorithm. 

#endif // _RADIX_SORT_H_
