#ifndef _TIME_MEASURE_H_
#define _TIME_MEASURE_H_

#include "numeric_utils.h"

#include <algorithm>
#include <cstdio>
#include <ctime>
#include <functional>
#include <vector>

namespace util {

double TimeSpent(const clock_t& start, const clock_t& finish) {
  return static_cast<double>(finish-start) / CLOCKS_PER_SEC;
}

double MeasureTime(const std::function<void()>& function_to_measure) {
  clock_t start = clock();
  function_to_measure();
  clock_t finish = clock();
  return TimeSpent(start, finish);
}

template<class T>
double MeasureTime(T& obj, const std::function<void(T&)>& function) {
  clock_t start = clock();
  function(obj);
  clock_t finish = clock();
  return TimeSpent(start, finish);
}

double MeasureMedianTime(const std::function<void()>& func, int nruns) {
  std::vector<double> times(nruns);
  for (int i = 0; i < nruns; ++i) {
    times[i] = MeasureTime(func);
  }
  return NaiveMedian(times);
}

template<class T>
double MeasureMedianTime(T& obj, const std::function<void(T&)>& f, int nruns) {
  std::vector<double> times(nruns);
  for (int i = 0; i < nruns; ++i) {
    times[i] = MeasureTime(obj, f);
  }
  return NaiveMedian(times);
}

void ReportTime(const std::function<void()>& func) {
  printf("Spent %.6f secs\n", MeasureTime(func));
}

template<class T>
void ReportTime(T& obj, const std::function<void(T&)>& func) {
  printf("Spent %.6f secs\n", MeasureTime(obj, func));
}

void ReportMedianTime(const std::function<void()>& func, int nruns) {
  printf("Median time %.6f secs\n", MeasureMedianTime(func, nruns));
}

template<class T>
void ReportMedianTime(T& obj, const std::function<void(T&)>& func, int nruns) {
  printf("Median time %.6f secs\n", MeasureMedianTime(obj, func, nruns));
}

}  // namespace util

#endif // _TIME_MEASURE_H
