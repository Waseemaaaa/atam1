//
// Created by reemd on 18/02/2024.
//
#include <iostream>
#include "AVL.h"

int main() {

    //////עץ ראשון//
    AVL<int, std::string> avlTree;

    std::cout << "Inserting keys to demonstrate multiple rotations:" << std::endl;

    // הכנסות שתגרמו לסיבוב RR ואז ל-LL
    avlTree.insert(10, "A");
    avlTree.insert(20, "B");
    avlTree.insert(30, "C");
    avlTree.insert(15, "D");
    avlTree.insert(5, "E");

    // הכנסות שתגרמו לסיבוב LR
    avlTree.insert(25, "F");
    avlTree.insert(23, "G");

    // הכנסות שתגרמו לסיבוב RL
    avlTree.insert(40, "H");
    avlTree.insert(35, "I");

    std::cout << "Final tree after multiple rotations:" << std::endl;
    printInOrder(avlTree);
    AVL<int, std::string> avlTree2;

    //////עץ שניייי//
    // הכנסת 20 מפתחות שונים לעץ
    int keys[20] = {50, 40, 60, 30, 45, 55, 70, 20, 35, 48, 53, 58, 65, 80, 10, 25, 38, 47, 54, 75};

    std::cout << "Inserting 20 different keys to the AVL tree:" << std::endl;

    for (int i = 0; i < 20; ++i) {
        avlTree2.insert(keys[i], "Value" + std::to_string(i));
    }

    std::cout << "AVL tree after inserting 20 keys:" << std::endl;
    printInOrder(avlTree2);

    return 0;
}
