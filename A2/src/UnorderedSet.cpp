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

    // Node<Key> newNode(key);
    auto *newNode = new Node<Key>(key);
    Node<Key> *currentNode = root;
    Node<Key> *parent = currentNode;

    setSize += 1;

    if (currentNode == nullptr) {
        newNode->color = Color::BLACK;
        root = newNode;

        return true;
    }

    while (currentNode != nullptr) {
        if (key == currentNode->key) return false;

        currentNode = key < currentNode->key ? currentNode->left : currentNode->right;

        if (currentNode == nullptr) {
            if (parent->color == Color::RED) newNode->color = Color::BLACK;

            if (key < parent->key) {
                parent->left = newNode;
            } else {
                parent->right = newNode;
            }
        }
    }

    if (currentNode->color == Color::RED && parent->color == Color::RED) fixRedRedViolation(currentNode);

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
    parent->left = &grandparent;
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
    parent->right = &grandparent;
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
    if (node->color != Color::RED || node->color != parent->color) return;

    Node<Key> *uncle = parent->key < node->key ? &parent->right : &parent->left;
    Node<Key> *grandparent = &parent.parent;

    // If uncle is red
    if (uncle->color == Color::RED) {
        // 1. Recolour the parent and uncle as black
        // 2. Recolour the grandparent as red
        // 3. Repeat the process for the grandparent

        parent->color = Color::BLACK;
        uncle->color = Color::BLACK;
        grandparent->color = Color::RED;

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
        if (grandparent->left->key == parent->key) {
            // If LL case
            if (parent->left->key == node->key) {
                // 1. Rotation
                rotateRight(&parent);

                // 2. Recolour
                grandparent->color = grandparent->color == Color::RED ? Color::BLACK : Color::RED;
                parent->color = Color::BLACK;
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
            if (parent->right->key == node->key) {
                // 1. Rotation
                rotateLeft(&parent);

                // 2. Recolour
                grandparent->color = grandparent->color == Color::RED ? Color::BLACK : Color::RED;
                parent->color = Color::BLACK;
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
Node<Key> *findSuccessor(Node<Key> *node) {
    if (node->right != nullptr) {
        node = node->right;
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    Node<Key> *parent = node->parent;
    while (parent != nullptr && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

/**
 * Searches for the key in the set.
 *
 * @param key The key to search for in the set
 * @return Whether the key exists in the set
 */
template<typename Key>
bool UnorderedSet<Key>::search(const Key &key) const {
    Node<Key> *current = root;

    while (current != nullptr) {
        if (key == current->key) return true;

        current = key < current->key ? current->left : current->right;
    }

    return false;
}

template<typename Key>
size_t UnorderedSet<Key>::size() const {
    return getSize(root);
}


/**
 * Recursively calculates the size of the subtree rooted at the given node.
 *
 * @param node The root node of the subtree to calculate the size of
 * @return The size of the subtree rooted at the given node
 */
template<typename Key>
size_t UnorderedSet<Key>::getSize(Node<Key> *node) const {
    if (node == nullptr) return 0;

    size_t size = 1;

    size += getSize(node->left);
    size += getSize(node->right);

    return size;
}

/**
 * Fixes the Red-Black Tree properties after a node deletion.
 *
 * @param node The node to be deleted
 */
template<typename Key>
void UnorderedSet<Key>::deleteFix(Node<Key> *node) {
    // If the node to be deleted is red, there is nothing to fix
    if (node->color == Color::RED) return;

    // When we delete a black leaf node, its child, which is NULL and is considered black, replaces it. The leaf node's
    // colour turns into an undefined blue colour. This blue node must be dealt with to restore the Red-Black property
    // of the tree.
    node->color = Color::BLUE;

    Node<Key> *parent = node->parent;
    Node<Key> *sibling = node->key < parent->key ? parent->right : parent->left;
    Node<Key> *innerNephew = node->key < parent->key ? sibling->left : sibling->right;
    Node<Key> *outerNephew = node->key < parent->key ? sibling->right : sibling->left;

    // Case 2: If the blue node is the root, recolour it to black and exit.
    if (node->parent == nullptr) {
        node->color = Color::BLACK;
    }
    // Case 3: If the blue node's sibling is black and both of its nephews are also black:
    // 1. Recolour the node to black and its sibling to red
    // 2. If its parent is red, recolour it to black. Otherwise, set the parent as a blue node and re-apply the suitable
    // case for the parent.
    else if (
        // Blue node's sibling is black
        (sibling == nullptr || sibling->color == Color::BLACK) &&
        // and both of its nephews are also black
        (sibling->left == nullptr || sibling->left->color == Color::BLACK) &&
        (sibling->right == nullptr || sibling->right->color == Color::BLACK)
    ) {
        // 1. Recolour the node to black
        node->color = Color::BLACK;
        // and its sibling to red
        sibling->color = Color::RED;

        // 2. If its parent is red
        if (parent->color == Color::RED) {
            // recolour it to black
            parent->color = Color::BLACK;
        }
        // Otherwise, set the parent as a blue node and re-apply the suitable case for the parent
        else {
            deleteFix(parent);
        }
    }
    // Case 4: If the blue node's sibling is red:
    // 1. Swap the colour of the blue node's sibling and parent
    // 2. Rotate the parent in the direction of the blue node
    // 3. Re-apply the suitable case for the blue node
    else if (sibling->color == Color::RED) {
        // 1. Swap the colour of the blue node's sibling and parent
        sibling->color = Color::BLACK;
        parent->color = Color::RED;

        // 2. Rotate the parent in the direction of the blue node
        if (node->key < parent->key) {
            rotateLeft(parent);
        } else {
            rotateRight(parent);
        }

        // 3. Re-apply the suitable case for the blue node
        deleteFix(node);
    }
    // Case 5: If the blue node's sibling is black, the outer nephew is black, and the inner nephew is red:
    // 1. Swap the colours of the blue node's siblings and inner nephew
    // 2. Rotate the blue node's sibling in the opposite direction of the blue node
    // 3. Apply case 6
    else if (
        // Blue node's sibling is black
        (sibling == nullptr || sibling->color == Color::BLACK) &&
        // the outer nephew is black
        (outerNephew == nullptr || outerNephew->color == Color::BLACK) &&
        // the inner nephew is red
        innerNephew->color == Color::RED
    ) {
        // 1. Swap the colours of the blue node's sibling and inner nephew
        sibling->color = Color::RED;
        innerNephew->color = Color::BLACK;

        // 2. Rotate the blue node's sibling in the opposite direction of the blue node
        if (node->key < parent->key) {
            rotateRight(sibling);
        } else {
            rotateLeft(sibling);
        }

        // 3. Apply case 6
        deleteFix(node);
    }
    // Case 6: If the blue node's sibling is black and the outer nephew is red
    // 1. Swap the colours of the blue node's parent and sibling
    // 2. Rotate the blue node's parent in the blue node's direction
    // 3. Recolour the red nephew to black
    // 4. Recolour the blue node to black and exit
    else if (
        // Blue node's sibling is black
        (sibling == nullptr || sibling->color == Color::BLACK) &&
        // the outer nephew is red
        outerNephew->color == Color::RED
    ) {
        // 1. Swap the colours of the blue node's parent and sibling
        sibling->color = parent->color;
        parent->color = Color::BLACK;

        // 2. Rotate the blue node's parent in the blue node's direction
        if (node->key < parent->key) {
            rotateLeft(parent);
        } else {
            rotateRight(parent);
        }

        // 3. Recolour the red nephew to black
        outerNephew->color = Color::BLACK;

        // 4. Recolour the blue node to black and exit
        node->color = Color::BLACK;
    }
}

template<typename Key>
void UnorderedSet<Key>::deleteOneChild(Node<Key> *node) {
    // If the node does not exist, do nothing
    if (!search(node->key)) return;

    const Color color = node->color;

    // Perform BST deletion
    // - If the node is a leaf, it can be deleted immediately
    // - If the node has one child, the node can be deleted after its parent adjusts a link to bypass the node
    // - If the node has two children, swap it with its successor and delete the original successor node
    // If the node has two children
    if (node->left != nullptr && node->right != nullptr) {
        // Find the successor of the node
        Node<Key> *successor = findSuccessor(node);
        // Replace the data of the node with the data of the successor node
        node->key = successor->key;

        // Delete the successor node, which has at most one child
        return deleteOneChild(successor);
    }

    // If the node is a leaf
    if (node->left == nullptr && node->right == nullptr) {
        if (node->parent != nullptr) {
            if (node->key < node->parent->key) {
                node->parent->left = nullptr;
            } else {
                node->parent->right = nullptr;
            }
        } else {
            root = nullptr;
        }
    }
    // If the node has one child
    else {
        Node<Key> *child = node->left != nullptr ? node->left : node->right;

        if (node->parent != nullptr) {
            child->parent = node->parent;

            if (node->key < node->parent->key) {
                node->parent->left = child;
            } else {
                node->parent->right = child;
            }
        } else {
            child->color = Color::BLACK;
            root = child;
        }
    }

    deleteFix(node);

    setSize -= 1;

    delete node;
}

/**
 * Recursively updates the size of the subtree rooted at the given node.
 */
template<typename Key>
void UnorderedSet<Key>::updateSize() {
}

/**
 * Recursively clears the Red-Black Tree starting from the given node.
 *
 * @param node The node to start clearing the Red-Black Tree from
 */
template<typename Key>
void UnorderedSet<Key>::clearRecursive(Node<Key> *node) {
    if (node == nullptr) return;

    clearRecursive(node->left);
    node->left = nullptr;

    clearRecursive(node->right);
    node->right = nullptr;

    delete node;
}

template<typename Key>
bool UnorderedSet<Key>::erase(const Key &key) {
}

template<typename Key>
void UnorderedSet<Key>::clear() {
}

template<typename Key>
Iterator UnorderedSet<Key>::begin() {
}
