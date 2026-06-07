// Copyright 2025 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

template<typename T>
class BST {
 public:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;
        explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

 private:
    Node* root;

    void addNode(Node*& node, const T& key) {
        if (node == nullptr) {
            node = new Node(key);
        } else if (key < node->key) {
            addNode(node->left, key);
        } else if (key > node->key) {
            addNode(node->right, key);
        } else {
            node->count++;
        }
    }

    int getDepth(Node* node) const {
        if (node == nullptr) return 0;
        int leftDepth = getDepth(node->left);
        int rightDepth = getDepth(node->right);
        return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
    }

    Node* searchNode(Node* node, const T& key) const {
        if (node == nullptr || node->key == key) {
            return node;
        }
        if (key < node->key) {
            return searchNode(node->left, key);
        } else {
            return searchNode(node->right, key);
        }
    }

    void destroyTree(Node* node) {
        if (node == nullptr) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

    void inorderCollect(Node* node, std::vector<std::pair<T, int>>& vec) const {
        if (node == nullptr) return;
        inorderCollect(node->left, vec);
        vec.push_back(std::make_pair(node->key, node->count));
        inorderCollect(node->right, vec);
    }

 public:
    BST() : root(nullptr) {}

    ~BST() {
        destroyTree(root);
    }

    void insert(const T& key) {
        addNode(root, key);
    }

    int depth() const {
        return getDepth(root);
    }

    bool search(const T& key) const {
        return searchNode(root, key) != nullptr;
    }

    int getCount(const T& key) const {
        Node* node = searchNode(root, key);
        return node ? node->count : 0;
    }

    Node* getRoot() const {
        return root;
    }

    void inorder(std::vector<std::pair<T, int>>& vec) const {
        inorderCollect(root, vec);
    }
};

#endif  // INCLUDE_BST_H_
