#include "../include/CircularQueue.h"

/**
 * Initializes the circular queue with the given capacity.
 * @param capacity the size of the circular queue.
 */
template<typename T>
CircularQueue<T>::CircularQueue(const int capacity) : buffer(std::vector<T>(capacity)), capacity(capacity),
                                                      frontIndex(0), rearIndex(0),
                                                      currentSize(0) {
}

/**
 * Returns whether the circular queue is empty.
 * @return whether the circular queue is empty
 */
template<typename T>
bool CircularQueue<T>::isEmpty() const {
    return currentSize == 0;
}

/**
 * Returns whether the circular queue is full.
 * @return whether the circular queue is full
 */
template<typename T>
bool CircularQueue<T>::isFull() const {
    return currentSize == capacity;
}

/**
 * Returns the number of elements in the circular queue.
 * @return the number of elements in the circular queue.
 */
template<typename T>
size_t CircularQueue<T>::size() const {
    return currentSize;
}

/**
 * Adds the given element to the end of the circular queue.
 * @param element the element to add to the end of the circular queue.
 */
template<typename T>
void CircularQueue<T>::enqueue(const T &element) {
    buffer[rearIndex] = element;
    rearIndex = (rearIndex + 1) % capacity;
    currentSize += 1;
}

/**
 * Removes the next element in the circular queue by shifting the front index by 1 and updating the current size.
 */
template<typename T>
void CircularQueue<T>::dequeue() {
    frontIndex = (frontIndex + 1) % capacity;
    currentSize -= 1;
}

/**
 * Returns (peaks) the first element in the circular without modifying it.
 * @return the first element in the circular queue
 */
template<typename T>
T &CircularQueue<T>::front() {
    return buffer[frontIndex];
}

/**
 * Returns (peaks) the first element in the circular without modifying it.
 * @return the first element in the circular queue
 */
template<typename T>
const T &CircularQueue<T>::front() const {
    return buffer[frontIndex];
}


