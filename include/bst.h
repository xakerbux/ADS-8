// Copyright 2025 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

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
        Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

 private:
    Node* root;

    void add(Node*& node, const T& key) {
        if (!node) {
            node = new Node(key);
        } else if (key < node->key) {
            add(node->left, key);
        } else if (key > node->key) {
            add(node->right, key);
        } else {
            node->count++;
        }
    }

    int getDepth(Node* node) {
        if (!node) return 0;
        int l = getDepth(node->left);
        int r = getDepth(node->right);
        return (l > r ? l : r) + 1;
    }

    int findCount(Node* node, const T& key) {
        if (!node) return 0;
        if (key == node->key) return node->count;
        if (key < node->key) return findCount(node->left, key);
        return findCount(node->right, key);
    }

    void collect(Node* node, std::vector<std::pair<T, int>>& v) {
        if (!node) return;
        collect(node->left, v);
        v.push_back({node->key, node->count});
        collect(node->right, v);
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

 public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void insert(const T& key) { add(root, key); }
    int depth() { return getDepth(root); }
    int search(const T& key) { return findCount(root, key); }
    
    void inorder(std::vector<std::pair<T, int>>& v) {
        collect(root, v);
    }
};

#endif  // INCLUDE_BST_H_
