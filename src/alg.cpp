// Copyright 2025 NNTU-CS
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <vector>
#include <iostream>
#include "bst.h"

struct WordFreq {
    std::string word;
    int count;
};

void getSortedFreq(BST<std::string>& tree,
                   std::vector<WordFreq>& freq,
                   BST<std::string>::Node* node) {
    if (node == nullptr) return;
    getSortedFreq(tree, freq, node->left);
    freq.push_back({node->key, node->count});
    getSortedFreq(tree, freq, node->right);
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return;
    }

    std::string word;
    char ch;

    while (file.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            word += std::tolower(static_cast<unsigned char>(ch));
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }

    if (!word.empty()) {
        tree.insert(word);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
    std::ofstream out("result/freq.txt");
    if (!out.is_open()) {
        return;
    }

    std::vector<WordFreq> freq;
    getSortedFreq(tree, freq, tree.getRoot());

    std::sort(freq.begin(), freq.end(),
              [](const WordFreq& a, const WordFreq& b) {
                  return a.count > b.count;
              });

    for (const auto& item : freq) {
        out << item.word << ": " << item.count << std::endl;
        std::cout << item.word << ": " << item.count << std::endl;
    }

    out.close();
}
