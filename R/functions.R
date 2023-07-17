#' Calculate the Median of a Vector
#'
#' This function calculates the median of a numeric vector using the \code{\link{quickselect}} algorithm.
#'
#' @param vec A numeric vector.
#'
#' @return The median value of the input vector.
#'
#' @examples
#' vec <- c(3, 1, 4, 2, 5)
#' median(vec)
#'
#' @export
median <- function(vec) {
  return(quickselect(vec, floor(length(vec)/2)+1))
}

#' Calculate the Quantile of a Vector
#'
#' This function calculates the quantile of a numeric vector using the \code{\link{quickselect}} algorithm.
#'
#' @param vec A numeric vector.
#' @param quantile The quantile value (between 0 and 1).
#'
#' @return The quantile value of the input vector.
#'
#' @examples
#' vec <- c(3, 1, 4, 2, 5)
#' quantile(vec, 0.25)
#'
#' @export
quantile <- function(vec, quantile) {
  return(quickselect(vec, floor(length(vec) * quantile) + 1))
}

