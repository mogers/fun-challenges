#ifndef _SIMPLE_STREAM_H
#define _SIMPLE_STREAM_H

#include <queue>
#include <vector>

namespace ds {

template<typename T>
class SimpleStream {
 public:

  // Adds the given values to the stream.
  SimpleStream(const std::vector<std::pair<T, int>>& pairs) {
    for (const auto& p : pairs) {
      stream_.push(p);
    }
  }

  bool HasNext() {
    return !stream_.empty();
  }

  // Retrieves the next element of the stream. Assumes it is not empty.
  std::pair<T, int> Next() {
    auto p = stream_.front();
    stream_.pop();
    return p;
  }

 private:
  std::queue<std::pair<T, int>> stream_;

};

}  // namespace ds.

#endif
