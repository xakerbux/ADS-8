// Copyright 2025 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <vector>
#include <utility>
#include <algorithm>

template<typename T>
class BST {
 private:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;
        Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, const T& key) {
        if (node == nullptr) {
            node = new Node(key);
        } else if (key < node->key) {
            insert(node->left, key);
        } else if (key > node->key) {
            insert(node->right, key);
        } else {
            node->count++;
        }
    }

    int getDepth(Node* node) const {
        if (node == nullptr) return 0;
        int left = getDepth(node->left);
        int right = getDepth(node->right);
        return 1 + (left > right ? left : right);
    }

    void toVector(Node* node, std::vector<std::pair<T, int>>& vec) const {
        if (node == nullptr) return;
        toVector(node->left, vec);
        vec.push_back({node->key, node->count});
        toVector(node->right, vec);
    }

    void clear(Node* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

 public:
    BST() : root(nullptr) {}

    ~BST() {
        clear(root);
    }

    void insert(const T& key) {
        insert(root, key);
    }

    int depth() const {
        return getDepth(root);
    }

    void inorder(std::vector<std::pair<T, int>>& vec) const {
        toVector(root, vec);
    }
};

#endif  // INCLUDE_BST_H_
