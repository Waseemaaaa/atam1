//
// Created by reemd on 16/02/2024.
//
#include <iostream>
#include "AVL.h"


int main() {
    AVL<int, std::string> avl;

    // בדיקת מחיקה בעץ ריק
    std::cout << "Removing from an empty tree (expect no error):\n";
    avl.remove(1);

    // הכנסת ערכים לעץ
    for (int i = 1; i <= 15; i++) {
        avl.insert(i, "Value " + std::to_string(i));
    }

    // מחיקת עלה
    std::cout << "Removing a leaf (14):\n";
    avl.remove(14);

    // מחיקת צומת עם ילד אחד
    std::cout << "Removing a node with one child (13):\n";
    avl.remove(13);

    // מחיקת צומת עם שני ילדים
    std::cout << "Removing a node with two children (8):\n";
    avl.remove(8);

    // ניסיון מחיקת צומת שלא קיימת
    std::cout << "Trying to remove a non-existing node (20):\n";
    avl.remove(20);

    // מחיקת כל העץ צומת אחר צומת
    std::cout << "Removing all nodes:\n";
    for (int i = 1; i <= 15; i++) {
        if (i != 8 && i != 13 && i != 14) {
            std::cout << "Removing: " << i << "\n";
            avl.remove(i);
        }
    }

    // בדיקה אם העץ ריק לאחר מחיקת כל הצמתים
    if (avl.isEmpty()) {
        std::cout << "The tree is empty after removing all nodes.\n";
        if(avl.getSize()==0)
        {
            std::cout << avl.getSize();
        }
    } else {
        std::cout << "There was an error, the tree is not empty after removing all nodes.\n";
        if(avl.getSize()!=1)
        {
            std::cout << avl.getSize();
        }
    }
    printInOrder(avl);

    return 0;
}



