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
void

/**
 * Deletes the node with the specified key if it has at most one child.
 *
 * @param node The node with the key to delete
 */




template<typename Key>
void UnorderedSet<Key>::deleteOneChild(Node<Key> *node) {
    // If the node does not exist, do nothing
    if (!search(node->key)) return;

    // Check the colour of the node to be deleted
    // If the node to be deleted is red
    if (node->color == Color::RED) {
        // Delete using BST deletion strategy
        // If the node is a leaf, it can be deleted immediately
        if (node->left == nullptr && node->right == nullptr) {
            if (node->parent != nullptr) {
                if (node->parent->left == node) {
                    node->parent->left = nullptr;
                } else {
                    node->parent->right = nullptr;
                }
            } else {
                root = nullptr;
            }

            setSize -= 1;

            delete node;
        }
        // Else, if the node to be deleted has two children
        else if (node->left != nullptr && node->right != nullptr) {
            // Do immediate deletion
            // Find the successor of the node to be deleted
            Node<Key> *successor = successor(node);

            // Replace the data of the node to be deleted with the data of the successor node
            node->key = successor->key;

            // Recursively delete the successor node
            deleteOneChild(successor);
        }
        // Else, if the node has one child
        else {
            // The node can be deleted after its parent adjusts a link to bypass it
            if (node->parent) {
                if (node->parent->left == node) {
                    node->parent->left = node->left;
                    node->left->parent = node->parent;
                } else {
                    node->parent->right = node->right;
                    node->right->parent = node->parent;
                }
            }

            setSize -= 1;

            delete node;
        }
    }
    // Else, if the node to be deleted is black
    else {
        // If the node to be deleted is a leaf node
        if (node->left == nullptr && node->right == nullptr) {
            Node<Key> *blueNode = node;
            blueNode->color = Color::BLUE;

            while (blueNode->color == Color::BLUE) {
                // Case 2: If the blue node is root, recolour it to black and exit
                if (node->parent == nullptr) {
                    blueNode->color = Color::BLACK;
                    root = nullptr;
                } else {
                    if (blueNode->parent->left == blueNode) {
                        // Case 3: If the blue node's sibling is black, and both of its nephews are also black:
                        // 1. Recolour the node to black and its sibling to red
                        // 2. If the parent is red, recolour it to black. Otherwise, set the parent as a blue node and re-apply the suitable case for the parent
                        if (
                            // If the blue node's sibling is black
                            (blueNode->parent->right->color == Color::BLACK || blueNode->parent->right == nullptr) &&
                            // and both of its nephews are also black
                            (blueNode->parent->right->left == Color::BLACK || blueNode->parent->right->left == nullptr)
                            &&
                            (blueNode->parent->right->right == Color::BLACK || blueNode->parent->right->right ==
                             nullptr)
                        ) {
                            // 1. Recolour the node to black and its sibling to red
                            blueNode->color = Color::BLACK;

                            if (blueNode->parent->right != nullptr) blueNode->parent->right->color = Color::RED;

                            // 2. If the parent is red, recolour it to black
                            if (blueNode->parent->color == Color::RED) {
                                blueNode->parent->color = Color::BLACK;
                            }
                            // Otherwise, set the parent as a blue node and re-apply the suitable case for the parent
                            else {
                                blueNode = blueNode->parent;
                                blueNode->color = Color::BLUE;
                            }
                        }
                        // Case 4: If the blue node's sibling is red:
                        // 1. Swap the colour of the blue node's sibling and parent
                        // 2. Rotate the parent in the direction of the blue node
                        // 3. Re-apply the suitable case for the blue node
                        else if (blueNode->parent->right->color == Color::RED) {
                            // 1. Swap the colour of the blue node's sibling and parent
                            if (blueNode->parent->right)
                                blueNode->parent->right->color = Color::BLACK;

                            blueNode->parent->color = blueNode->parent->color == Color::RED ? Color::BLACK : Color::RED;

                            // 2. Rotate the parent in the direction of the blue node
                            rotateLeft(blueNode->parent);
                        }
                        // Case 5: If the blue node's sibling is black, the outer nephew is black, and the inner nephew is red:
                        // 1. Swap the colours of the blue node's siblings and inner nephew
                        // 2. Rotate the blue node's sibling in the opposite direction of the blue node
                        // 3. Apply case 6
                        else if (
                            // If the blue node's sibling is black
                            (blueNode->parent->right->color == Color::BLACK || blueNode->parent->right == nullptr) &&
                            // and the outer nephew is black
                            (blueNode->parent->right->right == Color::BLACK || blueNode->parent->right->right ==
                             nullptr) &&
                            // and the inner nephew is red
                            blueNode->parent->right->left->color == Color::RED
                        ) {
                            // 1. Swap the colours of the blue node's sibling and inner nephew
                            if (blueNode->parent->right != nullptr) blueNode->parent->right->color = Color::RED;

                            blueNode->parent->right->left->color = Color::BLACK;

                            // 2. Rotate the blue node's sibling in the opposite direction of the blue node
                            rotateRight(blueNode->parent->right);

                            // 3. Apply case 6
                            // TODO: Apply case 6
                        }
                        // Case 6: If the blue node's sibling is black, and the outer nephew is red:
                        // 1. Swap the colours of the blue node's parent and sibling
                        // 2. Rotate the blue node's parent in the blue node's direction
                        // 3. Recolour the red nephew to black
                        // 4. Recolour the blue node to black and exit
                        else if (
                            // If the blue node's sibling is black
                            (blueNode->parent->right->color == Color::BLACK || blueNode->parent->right == nullptr) &&
                            // and the outer nephew is red
                            blueNode->parent->right->right->color == Color::RED
                        ) {
                            // 1. Swap the colours of the blue node's parent and sibling
                            if (blueNode->parent->right != nullptr) blueNode->parent->right->color = Color::RED;

                            blueNode->parent->color = blueNode->parent->color == Color::RED ? Color::BLACK : Color::RED;

                            // 2. Rotate the blue node's parent in the blue node's direction
                            rotateLeft(blueNode->parent);

                            // 3. Recolour the red nephew to black
                            blueNode->parent->right->right->color = Color::BLACK;

                            // 4. Recolour the blue node to black and exit
                            blueNode->color = Color::BLACK;
                        }
                    } else {
                        // Case 3: If the blue node's sibling is black, and both of its nephews are also black:
                        // 1. Recolour the node to black and its sibling to red
                        // 2. If the parent is red, recolour it to black. Otherwise, set the parent as a blue node and re-apply the suitable case for the parent
                        if (
                            // If the blue node's sibling is black
                            (blueNode->parent->left->color == Color::BLACK || blueNode->parent->left == nullptr) &&
                            // and both of its nephews are also black
                            (blueNode->parent->left->left == Color::BLACK || blueNode->parent->left->left == nullptr)
                            &&
                            (blueNode->parent->left->right == Color::BLACK || blueNode->parent->left->right ==
                             nullptr)
                        ) {
                            // 1. Recolour the node to black and its sibling to red
                            blueNode->color = Color::BLACK;

                            if (blueNode->parent->right != nullptr) blueNode->parent->right->color = Color::RED;

                            // 2. If the parent is red, recolour it to black
                            if (blueNode->parent->color == Color::RED) {
                                blueNode->parent->color = Color::BLACK;
                            }
                            // Otherwise, set the parent as a blue node and re-apply the suitable case for the parent
                            else {
                                blueNode = blueNode->parent;
                                blueNode->color = Color::BLUE;
                            }
                        }
                        // Case 4: If the blue node's sibling is red:
                        // 1. Swap the colour of the blue node's sibling and parent
                        // 2. Rotate the parent in the direction of the blue node
                        // 3. Re-apply the suitable case for the blue node
                        else if (blueNode->parent->left->color == Color::RED) {
                            // 1. Swap the colour of the blue node's sibling and parent
                            if (blueNode->parent->left) blueNode->parent->left->color = Color::BLACK;

                            blueNode->parent->color = blueNode->parent->color == Color::RED ? Color::BLACK : Color::RED;

                            // 2. Rotate the parent in the direction of the blue node
                            rotateRight(blueNode->parent);
                        }
                        // Case 5: If the blue node's sibling is black, the outer nephew is black, and the inner nephew is red:
                        // 1. Swap the colours of the blue node's siblings and inner nephew
                        // 2. Rotate the blue node's sibling in the opposite direction of the blue node
                        // 3. Apply case 6
                        else if (
                            // If the blue node's sibling is black
                            (blueNode->parent->left->color == Color::BLACK || blueNode->parent->left == nullptr) &&
                            // and the outer nephew is black
                            (blueNode->parent->left->left == Color::BLACK || blueNode->parent->left->left == nullptr) &&
                            // and the inner nephew is red
                            blueNode->parent->left->right->color == Color::RED
                        ) {
                            // 1. Swap the colours of the blue node's sibling and inner nephew
                            if (blueNode->parent->left != nullptr) blueNode->parent->left->color = Color::RED;

                            blueNode->parent->left->right->color = Color::BLACK;

                            // 2. Rotate the blue node's sibling in the opposite direction of the blue node
                            rotateLeft(blueNode->parent->left);

                            // 3. Apply case 6
                            // TODO: Apply case 6
                        }
                        // Case 6: If the blue node's sibling is black, and the outer nephew is red:
                        // 1. Swap the colours of the blue node's parent and sibling
                        // 2. Rotate the blue node's parent in the blue node's direction
                        // 3. Recolour the red nephew to black
                        // 4. Recolour the blue node to black and exit
                        else if (
                            // If the blue node's sibling is black
                            (blueNode->parent->left->color == Color::BLACK || blueNode->parent->left == nullptr) &&
                            // and the outer nephew is red
                            blueNode->parent->left->left->color == Color::RED
                        ) {
                            // 1. Swap the colours of the blue node's parent and sibling
                            if (blueNode->parent->left != nullptr) blueNode->parent->left->color = Color::RED;

                            blueNode->parent->color = blueNode->parent->color == Color::RED ? Color::BLACK : Color::RED;

                            // 2. Rotate the blue node's parent in the blue node's direction
                            rotateRight(blueNode->parent);

                            // 3. Recolour the red nephew to black
                            blueNode->parent->left->left->color = Color::BLACK;

                            // 4. Recolour the blue node to black and exit
                            blueNode->color = Color::BLACK;
                        }
                    }
                }
            }
        }
    }
}

