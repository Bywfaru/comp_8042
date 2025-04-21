#include "CircularQueue.h"

template <typename T>
CircularQueue<T>::CircularQueue(int capacity) : capacity(capacity), frontIndex(0), rearIndex(0), currentSize(0) {}

template <typename T>
bool CircularQueue<T>::isEmpty() const {
  return currentSize == 0;
}

template <typename T>
bool CircularQueue<T>::isFull() const {
  return currentSize == capacity;
}

template <typename T>
size_t CircularQueue<T>::size() const {
  return currentSize;
}

template <typename T>
void CircularQueue<T>::enqueue(const T& element) {
  if (isFull()) return;

  buffer[rearIndex] = element;
  rearIndex = (rearIndex + 1) % capacity;
  currentSize += 1;
}

template <typename T>
void CircularQueue<T>::dequeue() {
  if (isEmpty()) return;

  buffer.erase(buffer.begin() + frontIndex);

  frontIndex = (frontIndex + 1) % capacity;
}

template <typename T>
T& CircularQueue<T>::front() {
  if (isEmpty()) return;

  return buffer[frontIndex];
}

template <typename T>
const T& CircularQueue<T>::front() const {
  if (isEmpty()) return;

  return buffer[frontIndex];
}
