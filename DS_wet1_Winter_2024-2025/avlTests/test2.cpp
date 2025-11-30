//
// Created by reemd on 16/02/2024.
//
#include <iostream>
#include "AVL.h"

void insertAndPrint(AVL<int, std::string>& avl, int key, const std::string& value) {
    std::cout << "Inserting " << key << ": " << value << "\n";
    avl.insert(key, value);
}

void removeAndPrint(AVL<int, std::string>& avl, int key) {
    std::cout << "Removing " << key << "\n";
    avl.remove(key);
}

void searchAndPrint(AVL<int, std::string>& avl, int key) {
    if (avl.containNode(key)) {
        std::cout << "Found " << key << "\n";
    } else {
        std::cout << "Did not find " << key << "\n";
    }
}

int main() {
    AVL<int, std::string> avl;

    // בדיקות הוספה
    for (int i = 1; i <= 10; ++i) {
        insertAndPrint(avl, i, "Value " + std::to_string(i));
    }

    // בדיקת חיפוש
    searchAndPrint(avl, 5);
    searchAndPrint(avl, 11);

    // בדיקת הסרה
    removeAndPrint(avl, 5);
    searchAndPrint(avl, 5);


    for (int i = 0; i < 3; ++i) {
        insertAndPrint(avl, 20, "Repeated");
        removeAndPrint(avl, 20);
    }

    // נקה את העץ ובדוק שהוא ריק
    avl.clearTree();
    if (avl.isEmpty()) {
        std::cout << "Tree is empty after clearing.\n";
    } else {
        std::cout << "Error: Tree is not empty after clearing.\n";
    }

    return 0;
}

