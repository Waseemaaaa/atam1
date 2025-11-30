//
// Created by reemd on 16/02/2024.
//

#include <iostream>
#include "AVL.h"
int main() {
    AVL<int, std::string> avl;


    avl.insert(5, "Value 5");
    avl.insert(3, "Value 3");
    avl.insert(7, "Value 7");
    avl.insert(2, "Value 2");
    avl.insert(4, "Value 4");
    avl.insert(6, "Value 6");
    avl.insert(8, "Value 8");

    // check in order
    std::cout << "In-Order Traversal of AVL Tree: ";
    printInOrder(avl);

    return 0;
}