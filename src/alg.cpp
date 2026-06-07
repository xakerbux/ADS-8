// Copyright 2025 NNTU-CS
#include <string>
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) return;

    std::string word;
    char ch;

    while (file.get(ch)) {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            if (ch >= 'A' && ch <= 'Z') ch = ch - 'A' + 'a';
            word += ch;
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }
    
    if (!word.empty()) tree.insert(word);
    file.close();
}

void printFreq(BST<std::string>& tree) {
    std::ofstream out("result/freq.txt");
    if (!out) return;

    std::vector<std::pair<std::string, int>> v;
    tree.inorder(v);

    for (size_t i = 0; i < v.size(); i++) {
        for (size_t j = i + 1; j < v.size(); j++) {
            if (v[i].second < v[j].second) {
                std::swap(v[i], v[j]);
            }
        }
    }

    for (size_t i = 0; i < v.size(); i++) {
        out << v[i].first << ": " << v[i].second << std::endl;
    }

    out.close();
}
