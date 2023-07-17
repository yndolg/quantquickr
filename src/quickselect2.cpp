#include <Rcpp.h>
using namespace Rcpp;

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

namespace quickselect_fast{
void insertSort(vector<double>& vec){
  for(int i = 0; i < vec.size(); i++){
    int j = i - 1;
    double key = vec[i];
    while(j >= 0 && vec[j] > key) {
      vec[j + 1] = vec[j];
      j = j - 1;
    }
    vec[j + 1] = key;
  }
}

template <typename Iterator>
void insertionSort(Iterator begin, Iterator end) {
  for (auto it = begin; it != end; ++it) {
    auto key = *it;
    auto prevIt = it;

    while (prevIt != begin && *(prevIt - 1) > key) {
      *prevIt = *(prevIt - 1);
      --prevIt;
    }

    *prevIt = key;
  }
}

double findMedianOfFive(vector<double> numbers, int startPos) {
  double a = numbers[startPos];
  double b = numbers[startPos + 1];
  double c = numbers[startPos + 2];
  double d = numbers[startPos + 3];
  double e = numbers[startPos + 4];

  // Sort the first two elements (a and b)
  if (a > b) std::swap(a, b);

  // Sort the last two elements (d and e)
  if (d > e) std::swap(d, e);

  // Sort the middle three elements (b, c, and d)
  if (b > c) std::swap(b, c);
  if (c > d) std::swap(c, d);

  // Compare the second and fourth elements (b and d)
  if (b > d)
    return d;
  else
    return b;
}
double quickselect_impl(std::vector<double>& vec, int low, int high, int k);


double medianOfMedians(vector<double> vec, int low, int high) {
  std::vector<double> medians;
  for(int i = low; i <= high; i += 5) {
    //std::vector<double> part(vec.begin()+ i, vec.begin() + std::min(i + 5, high+1));
    int end = std::min(i + 5, high+1);
    int length = end - i;

    insertionSort(vec.begin() + i, vec.begin() + end);

    //insertSort(part);
    //double med = part[(int) (part.size() / 2)];
    medians.push_back(*(vec.begin() + i + (int) (length/2.0) /* (int) ((end-i) /2))*/));
    //medians.push_back(med);
  }

  if(medians.size() <= 2) {
    return medians[0];
  }
  return medianOfMedians(medians, 0, medians.size()-1);

}

double partition(std::vector<double>& arr, int left, int right, double pivot) {
  int i;
  for (i = left; i < right; i++)
    if (arr[i] == pivot)
      break;
    std::swap(arr[i], arr[right]);

    i = left;
    for (int j = left; j <= right - 1; j++) {
      if (arr[j] <= pivot) {
        std::swap(arr[i], arr[j]);
        i++;
      }
    }
    std::swap(arr[i], arr[right]);
    return i;
}

double quickselect_impl(std::vector<double>& vec, int low, int high, int k) {
  if (low <= high) {
    int pivotIndex = partition(vec, low, high, medianOfMedians(vec, low, high));
    if (pivotIndex == k - 1) {
      return vec[pivotIndex];
    } else if (pivotIndex > k - 1) {
      return quickselect_impl(vec, low, pivotIndex - 1, k);
    } else {
      return quickselect_impl(vec, pivotIndex + 1, high, k);
    }
  }
  return -1;
}
}
//' Finds the k-th element in the sorted list efficiently
//'
//' This function finds the k-th element in the sorted list using the Quickselect algorithm.
//'
//' @param vec A numeric vector.
//' @param k The desired rank of the element (1-based index).
//'
//' @return The k-th element in the sorted list.
//'
//' @examples
//' vec <- c(3, 1, 4, 2, 5)
//' quickselect(vec, 3)
//'
//' @export
// [[Rcpp::export]]
double quickselect2(std::vector<double> vec, int k) {
  return quickselect_fast::quickselect_impl(vec, 0, vec.size() - 1, k);
}

