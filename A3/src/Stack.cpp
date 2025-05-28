#include "../include/Stack.h"

/**
 * Initializes the stack.
 */
template<typename T>
Stack<T>::Stack() : buffer(), currentSize(0) {
}

/**
 * Returns whether the stack is empty.
 * @return whether the stack is empty
 */
template<typename T>
bool Stack<T>::isEmpty() const {
    return currentSize == 0;
}

/**
 * Returns the number of elements in the stack.
 * @return the number of elements in the stack
 */
template<typename T>
size_t Stack<T>::size() const {
    return currentSize;
}

/**
 * Pushes the given element to the top of the stack.
 * @param element the element to push to the top of the stack
 */
template<typename T>
void Stack<T>::push(const T &element) {
    buffer.push_back(element);

    currentSize += 1;
}

/**
 * Pops the element at the top of the stack.
 */
template<typename T>
void Stack<T>::pop() {
    buffer.pop_back();

    currentSize -= 1;
}

/**
 * Returns (peaks) at the element at the top of the stack without modifying it.
 * @return the element at the top of the stack
 */
template<typename T>
T &Stack<T>::top() {
    return buffer[currentSize - 1];
}

/**
 * Returns (peaks) at the element at the top of the stack without modifying it.
 * @return the element at the top of the stack
 */
template<typename T>
const T &Stack<T>::top() const {
    return buffer[currentSize - 1];
}
