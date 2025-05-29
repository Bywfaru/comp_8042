#include "../include/MergeSort.h"

/**
 * Sorts the given array in-place.
 * @param arr The array to sort
 */
template<typename T>
void MergeSort<T>::sort(std::vector<T> &arr) {
    if (arr.size() == 1) return;

    std::vector<T> left, right;
    const int middleIndex = arr.size() / 2;

    // Split the array into two halves
    for (int i = 0; i < middleIndex; ++i) {
        left.push_back(arr[i]);
    }

    for (int i = middleIndex; i < arr.size(); ++i) {
        right.push_back(arr[i]);
    }

    sort(left);
    sort(right);

    merge(arr, left, right);
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
