#include "../include/HashTable.h"

template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable(unsigned int size, double threshold) : tableSize(size),
    loadFactorThreshold(threshold) {
}

