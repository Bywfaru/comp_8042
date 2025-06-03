#include "../include/RadixSort.h"

/**
 * Sorts the elements in-place using LSD radix sort.
 */
template<typename T>
void RadixSort<T>::sort() {
    const int maxDigitCount = getMaxDigitCount();

    for (int i = 1; i <= maxDigitCount; i++) {
        countingSort(i);
    }
}

/**
 * Returns the highest digit count amongst the elements.
 * @return The highest digit count amongst the elements
 */
template<typename T>
int RadixSort<T>::getMaxDigitCount() {
    int maxDigitCount = 0;

    for (T element: elements_) {
        const int digitCount = getDigitCount(getKeyFunction_(element));

        if (digitCount > maxDigitCount) maxDigitCount = digitCount;
    }

    return maxDigitCount;
}

/**
 * Returns the number of digits in the given number.
 * @param number Number to get the digit count of
 * @return The number of digits in the given number
 */
template<typename T>
int RadixSort<T>::getDigitCount(int number) {
    int count = 0;

    while (number > 0) {
        number /= 10;
        count += 1;
    }

    return count;
}

/**
 * Sorts the elements in-place by the given digit using counting sort.
 * @param digit The digit to sort by
 */
template<typename T>
void RadixSort<T>::countingSort(int digit) {
    std::vector<int> items;
    std::vector<int> counts(10, 0);

    for (int i = 0; i < elements_.size(); i++) {
        const int key = getKeyFunction_(elements_[i]);
        const int item = getDigitValue(key, digit);

        items.push_back(item);
        counts[item] += 1;
    }


    std::vector<int> prefixSum(counts.size(), 0);

    prefixSum[0] = counts[0];

    for (int i = 1; i < counts.size(); i++) {
        prefixSum[i] += prefixSum[i - 1] + counts[i];
    }

    std::vector<T> sorted(items.size());

    for (int i = items.size() - 1; i >= 0; i--) {
        const int item = items[i];
        int index = prefixSum[item] - 1;

        sorted[index] = elements_[i];

        prefixSum[item] -= 1;
    }

    elements_ = sorted;
}

/**
 * Returns the digit value of the given number.
 * @param number The number to get the digit value of
 * @param digit The number's digit to get
 * @return The digit value of the given number
 */
template<typename T>
int RadixSort<T>::getDigitValue(int number, int digit) {
    return (number % static_cast<int>(pow(10, digit))) / static_cast<int>(pow(10, digit - 1));;
}
