#include "../include/RadixSort.h"

/**
 * Sorts the elements in-place using LSD radix sort.
 */
template<typename T>
void RadixSort<T>::sort() {
}

/**
 * Returns the highest digit count amongst the elements.
 * @return The highest digit count amongst the elements
 */
template<typename T>
int RadixSort<T>::getMaxDigitCount() {
    int maxDigitCount = 0;

    for (int i = 0; i < elements_.size(); i++) {
        const int digitCount = getDigitCount(elements_[i]);

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


template<typename T>
void RadixSort<T>::countingSort(int digit) {
    std::vector<int> items;

    for (int i = 0; i < elements_.size(); i++) {
        items.push_back(getDigitValue(elements_[i], digit));
    }

    std::vector<int> counts(10, 0);

    for (const int item: items) {
        counts[item] += 1;
    }

    std::vector<int> runningSum(counts.begin(), counts.end());

    for (int i = 1; i < runningSum.size(); i++) {
        runningSum[i] += runningSum[i - 1];
    }

    std::vector<int> runningSumShifted(runningSum.size(), 0);

    for (int i = 1; i < items.size(); i++) {
        runningSumShifted[i] += runningSumShifted[i - 1];
    }

    std::vector<int> sorted(items.size());

    for (int i = 0; i < items.size(); i++) {
        sorted[runningSumShifted[items[i]]] = i;
    }
}

/**
 * Returns the digit value of the given number.
 * @param number The number to get the digit value of
 * @param digit The number's digit to get
 * @return The digit value of the given number
 */
template<typename T>
int RadixSort<T>::getDigitValue(int number, int digit) {
    return number % static_cast<int>(pow(10, digit));
}
