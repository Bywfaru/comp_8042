#include "../include/MergeSort.h"

/**
 * Sorts the given array in-place.
 * @param arr The array to sort
 */
template<typename T>
void MergeSort<T>::sort(std::vector<T> &arr) {
    if (arr.size() == 1) return;

    const int middleIndex = arr.size() / 2;
    std::vector<T> left(arr.begin(), arr.begin() + middleIndex);
    std::vector<T> right(arr.begin() + middleIndex + 1, arr.end());
}

/**
 *
 * @param arr
 * @param left
 * @param right
 */
template<typename T>
void MergeSort<T>::merge(std::vector<T> &arr, const std::vector<T> &left, const std::vector<T> &right) {
}
