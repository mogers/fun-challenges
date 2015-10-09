#include "../data_structures/simple_stream.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

// Given a stream of pairs <value, weight>, selects a random value from the
// stream with probability proportional to its weight compared to the total
// weight sums. Assumes the stream is not empty.
template<typename T>
T Select(ds::SimpleStream<pair<T, int>>& stream) {
  pair<T, int> p = stream.Next();
  T selected_value = p.first;
  int sum = p.second;
  while (stream.HasNext()) {
    p = stream.Next();
    sum += p.second;
    // We should use a better random number generator.
    if (rand() % sum < p.second) {
      selected_value = p.first;
    }
  }
  return selected_value;
}

void SimpleTest() {
  vector<pair<int, int>> pairs{{0, 2}, {1, 2}, {2, 4}, {3, 10}, {4, 4}, {5, 3}};
  vector<int> times_selected(pairs.size(), 0);

  // Simulate 1 000 000 selections.
  int number_trials = 1000000;
  for (int t = 0; t < number_trials; ++t) {
    ds::SimpleStream<pair<int, int>> s(pairs);
    int id = Select<int>(s);
    ++times_selected[id];
  }

  // Check if the selection match the expected probabilities.
  int total_weight = 0;
  for (const auto& p : pairs) {
    total_weight += p.second;
  }
  for (size_t i = 0; i < pairs.size(); i++) {
    double expected = static_cast<double>(pairs[i].second) / total_weight;
    double got = static_cast<double>(times_selected[i]) / number_trials;
    printf("id %lu   expected %.4f  got %.4f\n", i, expected, got);
  }
}

int main() {
  srand(time(0));
  SimpleTest();
  return 0;
}
