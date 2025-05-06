#include "../include/UnorderedSet.h"

/**
 * Constructor
 */
template<typename Key>
UnorderedSet<Key>::UnorderedSet() : root(nullptr), setSize(0) {
}

/**
 * Destructor
 */
template<typename Key>
UnorderedSet<Key>::~UnorderedSet() = default;

/**
 * Inserts the provided key into the unordered set. Insertion fails if the key already exists.
 *
 * @param key The key to insert
 * @return Whether the insertion was successful
 */
template<typename Key>
bool UnorderedSet<Key>::insert(const Key &key) {
    // Check if the key already exists
    if (search(key)) return false;

    Node<Key> *newNode(key);
    Node<Key> currentNode(root);
    Node<Key> parent = currentNode;

    setSize += 1;

    if (currentNode == nullptr) {
        newNode->color = Color::BLACK;
        root = newNode;

        return true;
    }

    while (currentNode != nullptr) {
        if (key == currentNode->key) return false;

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

    // Detect and handle violations
    if (currentNode.color != Color::RED || currentNode.color != parent.color) return true;

    Node<Key> uncle = parent.key < currentNode.key ? parent.right : parent.left;

    if (uncle.color == Color::RED) {
        // If uncle is red, recolour all nodes except the new node in the subtree
    } else {
        // If uncle is black or null, rotate
    }

    return true;
}

/**
 * Performs a left rotation around the given node.
 *
 * @param node The node to rotate around
 */
template<typename Key>
void UnorderedSet<Key>::rotateLeft(Node<Key> *node) {
    Node<Key> *parent = &node;
    Node<Key> *grandparent = &node->parent;
    Node<Key> *greatGrandparent = &grandparent.parent;

    parent.parent = &greatGrandparent;
    grandparent.parent = &parent;

    // Update the great-grandparent if it exists
    if (greatGrandparent != nullptr) {
        if (greatGrandparent->left == grandparent) {
            greatGrandparent->left = node;
        } else {
            greatGrandparent->right = node;
        }
    }

    grandparent->right = &parent->left;
    parent.left = &grandparent;
}

/**
 * Performs a right rotation around the given node.
 *
 * @param node The node to rotate around
 */
template<typename Key>
void UnorderedSet<Key>::rotateRight(Node<Key> *node) {
    Node<Key> *parent = &node;
    Node<Key> *grandparent = &node->parent;
    Node<Key> *greatGrandparent = &grandparent.parent;

    parent.parent = &greatGrandparent;
    grandparent.parent = &parent;

    // Update the great-grandparent if it exists
    if (greatGrandparent != nullptr) {
        if (greatGrandparent->left == grandparent) {
            greatGrandparent->left = node;
        } else {
            greatGrandparent->right = node;
        }
    }

    grandparent->left = &parent->left;
    parent.right = &grandparent;
}

/**
 * Fix red-red violations at the child.
 *
 * @param node The node where the violation occurs
 */
template<typename Key>
void UnorderedSet<Key>::fixRedRedViolation(Node<Key> *node) {
    Node<Key> *parent = &node->parent;

    // If the node is not red nor is its parent red, there is no red-red violation
    if (node->color != Color::RED || node->color != parent.color) return;

    Node<Key> *uncle = parent.key < node.key ? &parent.right : &parent.left;
    Node<Key> *grandparent = &parent.parent;

    // If uncle is red
    if (uncle.color == Color::RED) {
        // 1. Recolour the parent and uncle as black
        // 2. Recolour the grandparent as red
        // 3. Repeat the process for the grandparent

        parent.color = Color::BLACK;
        uncle.color = Color::BLACK;
        grandparent.color = Color::RED;

        fixRedRedViolation(grandparent);
    }
    // If uncle is black or null:
    else {
        // - LL and RR cases:
        //   1. Rotate
        //   2. Swap colours of grandparent and parent
        // - LR and RL case:
        //   - Rotate
        //   - Swap colours of grandparent and the inserted node

        // If L case
        if (grandparent.left->key == parent.key) {
            // If LL case
            if (parent.left->key == node->key) {
                // 1. Rotation
                rotateRight(&parent);

                // 2. Recolour
                grandparent.color = Color::RED ? Color::BLACK : Color::RED;
                parent.color = Color::BLACK;
            }
            // If LR case
            else {
                rotateLeft(&parent);
                rotateRight(&node);
            }
        }
        // If R case
        else {
            // If RR case
            if (parent.right->key == node->key) {
                // 1. Rotation
                rotateLeft(&parent);

                // 2. Recolour
                grandparent.color = Color::RED ? Color::BLACK : Color::RED;
                parent.color = Color::BLACK;
            }
            // If RL case
            else {
                rotateRight(&parent);
                rotateLeft(&node);
            }
        }
    }
}

template<typename Key>
Node<Key> findMin(Node<Key> node) {
    Node<Key> *minNode = node;

    while (minNode->left != nullptr) {
        minNode = minNode->left;
    }

    return minNode;
}

/**
 * Deletes the node with the specified key if it has at most one child.
 *
 * @param node The node with the key to delete
 */
template<typename Key>
void UnorderedSet<Key>::deleteOneChild(Node<Key> *node) {
    // If the node does not exist, do nothing
    if (!search(node->key)) return;

    // If the node is a leaf node
    if (node->left == nullptr && node->right == nullptr) {
    }
    // If the node has 2 children
    else if (node->left != nullptr && node->right != nullptr) {
    }
    // If the node has 1 child
    else {
    }

    setSize -= 1;

    delete node;
}

