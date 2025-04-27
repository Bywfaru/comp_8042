#include "../include/UnorderedSet.h"

template<typename Key>
UnorderedSet<Key>::UnorderedSet() : setSize(0) {
}

template<typename Key>
UnorderedSet<Key>::~UnorderedSet() {
    // TODO: Implement deconstructor. Need to reassign nodes
}

template<typename Key>
bool UnorderedSet<Key>::insert(const Key &key) {
    // Check if the key already exists
    if (search(key)) return false;

    Node<Key> *newNode(key);
    Node<Key> currentNode(root);

    if (currentNode == nullptr) {
        newNode->color = Color::BLACK;
        root = newNode;
    } else {
        while (currentNode != nullptr) {
            if (key == currentNode->key) return false;

            Node<Key> parent = currentNode;
            currentNode = key < currentNode.key ? currentNode.left : currentNode.right;

            if (currentNode == nullptr) {
                if (parent.color == Color::RED) newNode->color = Color::BLACK;

                if (key < parent->key) {
                    parent->left = newNode;
                } else {
                    parent->right = newNode;
                }
            }
        }

        // Handle violations
    }

    setSize += 1;

    return true;
}
