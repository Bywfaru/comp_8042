#include "../include/HashTable.h"

template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable(unsigned int size, double threshold) : tableSize(size),
    loadFactorThreshold(threshold) {
}

template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::Iterator HashTable<KeyType, ValueType>::begin() {
}

template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::Iterator HashTable<KeyType, ValueType>::end() {
}

template<typename KeyType, typename ValueType>
ValueType &HashTable<KeyType, ValueType>::operator[](const KeyType &key) {
}

template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::updateValueForKey(const KeyType &key, ValueType newValue) {
}

template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::insert(const KeyType &key, const ValueType &value) {
}

template<typename KeyType, typename ValueType>
ValueType *HashTable<KeyType, ValueType>::search(const KeyType &key) {
}

template<typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::remove(const KeyType &key) {
}

template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::clear() {
}

template<typename KeyType, typename ValueType>
unsigned int HashTable<KeyType, ValueType>::size() const {
}

template<typename KeyType, typename ValueType>
double HashTable<KeyType, ValueType>::loadFactor() const {
}

template<typename KeyType, typename ValueType>
unsigned int HashTable<KeyType, ValueType>::findFreeSlot(std::vector<Bucket> &cTable, unsigned int startIndex,
                                                         unsigned int &currentHop) {
}

template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::rehash() {
}
