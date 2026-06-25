#include "RedBlackTree.h"

RedBlackTree::Node::Node(int value, Color nodeColor, bool sentinel)
    : key(value),
      color(nodeColor),
      left(nullptr),
      right(nullptr),
      parent(nullptr),
      isNil(sentinel) {}

RedBlackTree::RedBlackTree()
    : rootNode(nullptr),
      nilNode(nullptr),
      nodeCount(0) {
    nilNode = new Node(0, Color::BLACK, true);
    nilNode->left = nilNode;
    nilNode->right = nilNode;
    nilNode->parent = nilNode;

    rootNode = nilNode;
}

RedBlackTree::~RedBlackTree() {
    clear();
    delete nilNode;
}

void RedBlackTree::rotateLeft(Node* node) {
    Node* child = node->right;

    node->right = child->left;
    if (!child->left->isNil) {
        child->left->parent = node;
    }

    child->parent = node->parent;

    if (node->parent->isNil) {
        rootNode = child;
    } else if (node == node->parent->left) {
        node->parent->left = child;
    } else {
        node->parent->right = child;
    }

    child->left = node;
    node->parent = child;
}

void RedBlackTree::rotateRight(Node* node) {
    Node* child = node->left;

    node->left = child->right;
    if (!child->right->isNil) {
        child->right->parent = node;
    }

    child->parent = node->parent;

    if (node->parent->isNil) {
        rootNode = child;
    } else if (node == node->parent->right) {
        node->parent->right = child;
    } else {
        node->parent->left = child;
    }

    child->right = node;
    node->parent = child;
}

void RedBlackTree::fixInsert(Node* node) {
    while (node->parent->color == Color::RED) {
        Node* parent = node->parent;
        Node* grandparent = parent->parent;

        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;

            if (uncle->color == Color::RED) {
                parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                grandparent->color = Color::RED;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    node = parent;
                    rotateLeft(node);
                }

                node->parent->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                rotateRight(node->parent->parent);
            }
        } else {
            Node* uncle = grandparent->left;

            if (uncle->color == Color::RED) {
                parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                grandparent->color = Color::RED;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    node = parent;
                    rotateRight(node);
                }

                node->parent->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                rotateLeft(node->parent->parent);
            }
        }
    }

    rootNode->color = Color::BLACK;
}

void RedBlackTree::insert(int key) {
    Node* newNode = new Node(key, Color::RED, false);
    newNode->left = nilNode;
    newNode->right = nilNode;
    newNode->parent = nilNode;

    Node* parent = nilNode;
    Node* current = rootNode;

    while (!current->isNil) {
        parent = current;

        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    newNode->parent = parent;

    if (parent->isNil) {
        rootNode = newNode;
    } else if (key < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    nodeCount++;
    fixInsert(newNode);
}

bool RedBlackTree::contains(int key) const {
    Node* current = rootNode;

    while (!current->isNil) {
        if (key == current->key) {
            return true;
        }

        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return false;
}

bool RedBlackTree::lowerBound(int key, int& result) const {
    Node* current = rootNode;
    Node* answer = nilNode;

    while (!current->isNil) {
        if (current->key >= key) {
            answer = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (answer->isNil) {
        return false;
    }

    result = answer->key;
    return true;
}

bool RedBlackTree::upperBound(int key, int& result) const {
    Node* current = rootNode;
    Node* answer = nilNode;

    while (!current->isNil) {
        if (current->key > key) {
            answer = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (answer->isNil) {
        return false;
    }

    result = answer->key;
    return true;
}

const RedBlackTree::Node* RedBlackTree::root() const {
    return rootNode;
}

const RedBlackTree::Node* RedBlackTree::nil() const {
    return nilNode;
}

bool RedBlackTree::empty() const {
    return nodeCount == 0;
}

std::size_t RedBlackTree::size() const {
    return nodeCount;
}

void RedBlackTree::destroy(Node* node) {
    if (node->isNil) {
        return;
    }

    destroy(node->left);
    destroy(node->right);
    delete node;
}

void RedBlackTree::clear() {
    destroy(rootNode);
    rootNode = nilNode;
    nodeCount = 0;
}
