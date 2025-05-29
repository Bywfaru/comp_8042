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
    std::vector<T> right(arr.begin() + middleIndex, arr.end());

    sort(left);
    sort(right);

    merge(arr, left, right);
}

/**
 * Merges the two arrays into a sorted array.
 * @param arr The array to insert the sorted values into
 * @param left The left array to merge
 * @param right The right array to merge
 */
template<typename T>
void MergeSort<T>::merge(std::vector<T> &arr, const std::vector<T> &left, const std::vector<T> &right) {
    int leftIndex = 0;
    int rightIndex = 0;

    while (leftIndex < left.size() && rightIndex < right.size()) {
        if (compare(left[leftIndex], right[rightIndex])) {
            arr[leftIndex + rightIndex] = left[leftIndex];
            leftIndex += 1;
        } else {
            arr[leftIndex + rightIndex] = right[rightIndex];
            rightIndex += 1;
        }
    }

    for (int i = leftIndex; i < left.size(); i++) {
        arr[i + rightIndex] = left[i];
    }

    for (int i = rightIndex; i < right.size(); i++) {
        arr[i + leftIndex] = right[i];
    }
}
