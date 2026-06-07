// Copyright 2025 NNTU-CS
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>
#include "bst.h"

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

    std::vector<std::pair<std::string, int>> nodes;
    tree.inorder(nodes);

    std::sort(nodes.begin(), nodes.end(),
              [](const std::pair<std::string, int>& a,
                 const std::pair<std::string, int>& b) {
                  return a.second > b.second;
              });

    for (const auto& item : nodes) {
        out << item.first << ": " << item.second << std::endl;
        std::cout << item.first << ": " << item.second << std::endl;
    }

    out.close();
}
