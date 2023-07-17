#include <Rcpp.h>
using namespace Rcpp;

#include <vector>
#include <algorithm>

using namespace std;
// This is a simple function using Rcpp that creates an R list
// containing a character vector and a numeric vector.
//
// Learn more about how to use Rcpp at:
//
//   http://www.rcpp.org/
//   http://adv-r.had.co.nz/Rcpp.html
//
// and browse examples of code using Rcpp at:
//
//   http://gallery.rcpp.org/
//


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

double medianOfMedians(vector<double> vec, int low, int high) {
  std::vector<double> medians;
  for(int i = low; i <= high; i += 5) {
    std::vector<double> part(vec.begin()+ i, vec.begin() + std::min(i + 5, high+1));

    insertSort(part);
    double med = part[(int) (part.size() / 2)];
    medians.push_back(med);
  }

  if(medians.size() == 1) {
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
double quickselect(std::vector<double> vec, int k) {
  return quickselect_impl(vec, 0, vec.size() - 1, k);
}



