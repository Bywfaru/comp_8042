#include "../include/HashTable.h"

template<typename Key>
unsigned int hashKey(Key key, const unsigned int tableSize) {
    return std::hash<Key>{}(key) % tableSize;
}

/**
 * Constructor.
 *
 * @param size The size of the hash table
 * @param threshold The max load factor
 */
template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable(const unsigned int size, const double threshold) : tableSize(size),
    loadFactorThreshold(threshold), hashTable(size) {
}

/**
 * Returns the beginning of the hash table.
 *
 * @return The beginning of the hash table
 */
template<typename KeyType, typename ValueType>
typename HashTable<KeyType, ValueType>::Iterator HashTable<KeyType, ValueType>::begin() {
    auto it = hashTable.begin();
    // Skip to first occupied bucket if current one is not occupied
    while (it != hashTable.end() && !it->occupied) {
        ++it;
    }
    return Iterator(it, hashTable.end());
}


/**
 * Returns the end of the hash table.
 *
 * @return The end of the hash table.
 */
template<typename KeyType, typename ValueType>
typename HashTable<KeyType, ValueType>::Iterator HashTable<KeyType, ValueType>::end() {
    return Iterator(hashTable.end(), hashTable.end());
}


/**
 * Returns the value corresponding to the given key if it exists.
 *
 * @param key The key to retrieve the value of
 * @return The value corresponding to the given key if it exists
 */
template<typename KeyType, typename ValueType>
ValueType &HashTable<KeyType, ValueType>::operator[](const KeyType &key) {
    const int startingIndex = hashKey(key, tableSize);
    int currentHop = 0;

    while (currentHop < HOP_RANGE) {
        const int index = (startingIndex + currentHop) % tableSize;

        if (hashTable[index].key == key) return hashTable[index].value;

        currentHop += 1;
    }

    throw std::runtime_error("Key not found");
}

/**
 * Updates the value of the given key if it exists.
 *
 * @param key The key of the value to update
 * @param newValue The new value
 */
template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::updateValueForKey(const KeyType &key, ValueType newValue) {
    const int startingIndex = hashKey(key, tableSize);
    int currentHop = 0;

    while (currentHop < HOP_RANGE) {
        if (hashTable[(startingIndex + currentHop) % tableSize].key == key) {
            hashTable[(startingIndex + currentHop) % tableSize].value = newValue;

            return;
        }

        currentHop += 1;
    }
}

/**
 * Inserts a value for the given key if possible.
 *
 * @param key The key to insert the value for
 * @param value The value to insert
 */
template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::insert(const KeyType &key, const ValueType &value) {
    // If the load factor threshold is exceeded, do nothing
    if (loadFactor() > loadFactorThreshold) return;

    const int startingIndex = hashKey(key, tableSize);
    unsigned int currentHop = 0;

    while (currentHop < HOP_RANGE) {
        const int index = (startingIndex + currentHop) % tableSize;

        // If the key already exists in the hash table, do nothing
        if (hashTable[index].key == key) return;
        // If the bucket is not occupied, we can immediately insert then exit
        if (!hashTable[index].occupied) {
            hashTable[index].key = key;
            hashTable[index].value = value;
            hashTable[index].occupied = true;
            hashTable[index].hopInfo = currentHop;

            return;
        }

        currentHop += 1;
    }

    try {
        // If we reach this point, that means the key's home neighbourhood is full, and we should try to shift an empty
        // bucket into it if possible
        unsigned int emptyIndex = findFreeSlot(hashTable, startingIndex, currentHop);
        int index = emptyIndex == 0 ? tableSize - 1 : emptyIndex - 1;

        while (index != startingIndex) {
            // If the element at the current index can be shifted
            if (hashTable[index].occupied && hashTable[index].hopInfo < 4) {
                Bucket temp = hashTable[index];

                // Move the element at the current index to the empty bucket
                hashTable[emptyIndex].key = temp.key;
                hashTable[emptyIndex].value = temp.value;
                hashTable[emptyIndex].occupied = true;
                hashTable[emptyIndex].hopInfo = temp.hopInfo + 1;

                // Check if the current index is within the home neighbourhood
                if (
                    index == (startingIndex + 1) % tableSize ||
                    index == (startingIndex + 2) % tableSize ||
                    index == (startingIndex + 3) % tableSize
                ) {
                    // If it is, we can immediately insert the element at the current index then exit
                    hashTable[index].key = key;
                    hashTable[index].value = value;
                    hashTable[index].occupied = true;
                    hashTable[index].hopInfo = index - startingIndex;

                    return;
                }
                // Else, empty the current index's bucket
                else {
                    hashTable[index].occupied = false;
                    emptyIndex = index;
                }
            }

            index = index == 0 ? tableSize - 1 : index - 1;
        }

        // If index == startingIndex, it means the empty bucket could not be moved into the home neighbourhood, meaning
        // we must rehash and retry insertion
        rehash();
        insert(key, value);
    } catch (std::runtime_error &e) {
        // If we reach this point, that means the hash table is full
    }
}

/**
 * Returns the value of the key if it exists.
 *
 * @param key The key to search for
 * @return The value of the key if it exists
 */
template<typename KeyType, typename ValueType>
ValueType *HashTable<KeyType, ValueType>::search(const KeyType &key) {
    const int startingIndex = hashKey(key, tableSize);
    int currentHop = 0;

    while (currentHop < HOP_RANGE) {
        const int index = (startingIndex + currentHop) % tableSize;

        if (hashTable[index].key == key) return &hashTable[index].value;

        currentHop += 1;
    }

    return nullptr;
}

/**
 * Removes the key from the hash table if it exists.
 *
 * @param key The key to remove
 * @return Whether the removal was successful
 */
template<typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::remove(const KeyType &key) {
    const int startingIndex = hashKey(key, tableSize);
    int currentHop = 0;

    while (currentHop < HOP_RANGE) {
        const int index = (startingIndex + currentHop) % tableSize;

        if (hashTable[index].key == key) {
            hashTable[index].occupied = false;

            return true;
        }

        currentHop += 1;
    }

    return false;
}

/**
 * Clears the hash table of all keys and values.
 */
template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::clear() {
    for (unsigned int i = 0; i < tableSize; ++i) {
        hashTable[i].occupied = false;
    }
}

/**
 * Returns the number of items in the hash table.
 *
 * @return The number of items in the hash table.
 */
template<typename KeyType, typename ValueType>
unsigned int HashTable<KeyType, ValueType>::size() const {
    unsigned int count = 0;

    for (unsigned int i = 0; i < tableSize; ++i) {
        if (hashTable[i].occupied) count += 1;
    }

    return count;
}

template<typename KeyType, typename ValueType>
double HashTable<KeyType, ValueType>::loadFactor() const {
    return tableSize / size();
}

/**
 * Finds the first free slot in the given hash table.
 *
 * @param cTable The hash table to find a free slot in
 * @param startIndex The starting index to start the search from
 * @param currentHop The current hop (offeset)
 * @return The index of the empty slot
 */
template<typename KeyType, typename ValueType>
unsigned int HashTable<KeyType, ValueType>::findFreeSlot(std::vector<Bucket> &cTable, unsigned int startIndex,
                                                         unsigned int &currentHop) {
    unsigned int currentIndex = (startIndex + currentHop) % tableSize;

    while (currentIndex != startIndex) {
        if (!cTable[currentIndex].occupied) return currentIndex;

        currentIndex = (currentIndex + 1) % tableSize;
    }

    throw std::runtime_error("No free slot found");
}

/**
 * Rehashes by:
 * 1. Building another table that is twice as big
 * 2. Scanning down the entire original hash table
 * 3. For each (non-deleted) item, computing the new hash value and inserting it in the new table
 */
template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::rehash() {
    const int oldTableSize = tableSize;
    const int newTableSize = tableSize * 2;
    // 1. Build another table that is twice as big
    std::vector<Bucket> newTable(newTableSize);

    // 2. Scan down the entire original hash table
    std::vector<Bucket> oldTable(oldTableSize);

    for (unsigned int i = 0; i < oldTableSize; ++i) {
        oldTable[i] = hashTable[i];
    }

    // 3. For each (non-deleted) item, compute the new hash value and insert it in the new table
    tableSize = newTableSize;

    for (unsigned int i = 0; i < oldTableSize; ++i) {
        if (oldTable[i].occupied) insert(oldTable[i].key, oldTable[i].value);
    }

    // Update the hash table to the new one
    hashTable = newTable;
}
