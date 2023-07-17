# QuantQuickR

## Description
We present an R-package for finding the k-th largest element in an
    array that performs better than the base R quantile function
    for small inputs. Our efficient Rcpp implementation utilizes the
    [Quickselect-Algorithm](https://en.wikipedia.org/wiki/Quickselect)
    that has a theoretical time complexity of O(n) with the 
    [median-of-medians](https://en.wikipedia.org/wiki/Median_of_medians) 
    technique. It includes functions for calculating the median, quickselect, and quantile of a numeric vector.
    
![benchmark showing better performance of quantquickr for small data sizes](https://raw.githubusercontent.com/yndolg/quantquickr/master/benchmark.png)

## Installation

You can install QuantQuickR from GitHub using the `devtools` package:

```R
remotes::install_github("yndolg/quantquickr")
```
# Usage

The package provides the following functions:

## median

Calculates the median of a numeric vector using the quickselect algorithm.

**Syntax:** `median(vec)`

- **vec:** A numeric vector.

## quantile

Calculates the quantile of a numeric vector using the quickselect algorithm.

**Syntax:** `quantile(vec, quantile)`

- **vec:** A numeric vector.
- **quantile:** The quantile value (between 0 and 1).

# Examples

Here are some examples demonstrating the usage of the functions:

```r
library(quantquickr)

# Calculate the median
vec <- c(3, 1, 4, 2, 5)
median_value <- median(vec)
print(median_value)  # Output: 3

# Calculate the 0.25 quantile
quantile_value <- quantile(vec, 0.25)
print(quantile_value)  # Output: 2
```
