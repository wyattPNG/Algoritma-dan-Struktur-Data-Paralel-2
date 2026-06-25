#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <cstddef>

class RedBlackTree {
  public:
    enum class Color { RED, BLACK };

    struct Node {
        int key;
        Color color;
        Node* left;
        Node* right;
        Node* parent;
        bool isNil;

        Node(int value, Color nodeColor, bool sentinel);
    };

  private:
    Node* rootNode;
    Node* nilNode;
    std::size_t nodeCount;

  private:
    void rotateLeft(Node* node);
    void rotateRight(Node* node);
    void fixInsert(Node* node);
    void destroy(Node* node);

  public:
    RedBlackTree();
    ~RedBlackTree();

    RedBlackTree(const RedBlackTree& other) = delete;
    RedBlackTree& operator=(const RedBlackTree& other) = delete;

    void insert(int key);
    bool contains(int key) const;

    bool lowerBound(int key, int& result) const;
    bool upperBound(int key, int& result) const;

    const Node* root() const;
    const Node* nil() const;

    bool empty() const;
    std::size_t size() const;

    void clear();
};

#endif
