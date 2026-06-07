// Copyright 2025 NNTU-CS
#include <string>
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>
#include <iostream>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) return;

    std::string word;
    char c;

    while (file.get(c)) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            if (c >= 'A' && c <= 'Z') {
                c = c + 32;
            }
            word += c;
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
    if (!out) return;

    std::vector<std::pair<std::string, int>> words;
    tree.inorder(words);

    for (size_t i = 0; i < words.size(); i++) {
        for (size_t j = i + 1; j < words.size(); j++) {
            if (words[i].second < words[j].second) {
                std::swap(words[i], words[j]);
            }
        }
    }

    for (size_t i = 0; i < words.size(); i++) {
        out << words[i].first << ": " << words[i].second << std::endl;
        std::cout << words[i].first << ": " << words[i].second << std::endl;
    }

    out.close();
}
