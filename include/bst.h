// Copyright 2025 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
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
        return 1 + std::max(getDepth(node->left), getDepth(node->right));
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

    void inorderPrint(Node* node) const {
        if (node == nullptr) return;
        inorderPrint(node->left);
        std::cout << node->key << ": " << node->count << std::endl;
        inorderPrint(node->right);
    }

    void destroyTree(Node* node) {
        if (node == nullptr) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
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

    void print() const {
        inorderPrint(root);
    }
};

#endif  // INCLUDE_BST_H_
