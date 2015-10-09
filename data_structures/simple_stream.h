#ifndef _SIMPLE_STREAM_H
#define _SIMPLE_STREAM_H

#include <queue>
#include <vector>

namespace ds {

template<typename T>
class SimpleStream {
 public:

  // Adds the given values to the stream.
  SimpleStream(const std::vector<T>& values) {
    for (const auto& value : values) {
      stream_.push(value);
    }
  }

  bool HasNext() {
    return !stream_.empty();
  }

  // Retrieves the next element of the stream. Assumes it is not empty.
  T Next() {
    T p = stream_.front();
    stream_.pop();
    return p;
  }

 private:
  std::queue<T> stream_;

};

}  // namespace ds.

#endif
