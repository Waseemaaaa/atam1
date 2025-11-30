//
// Created by reemd on 16/02/2024.
//
#include "AVL.h"

int main() {
    AVL<int, int> avlTree;

    std::cout << "Initial tree empty? " << (avlTree.isEmpty() ? "Yes" : "No") << std::endl;

    // Inserting elements
    std::cout << "Inserting elements..." << std::endl;
    avlTree.insert(10, 100);
    avlTree.insert(20, 200);
    avlTree.insert(30, 300);
    avlTree.insert(5, 50);
    avlTree.insert(1, 10);
    avlTree.insert(15, 150);
    avlTree.insert(25, 250);
    avlTree.insert(40, 400);
    avlTree.insert(50, 500);
    avlTree.insert(60, 600);

    // Printing in order to see tree structure
    std::cout << "Tree elements in order: ";
    printInOrder(avlTree);
    std::cout << std::endl;

    // Checking if specific elements exist
    std::cout << "Does 30 exist? " << (avlTree.containNode(30) ? "Yes" : "No") << std::endl;
    std::cout << "Does 100 exist? " << (avlTree.containNode(100) ? "Yes" : "No") << std::endl;

    // Deleting elements
    std::cout << "Deleting elements 30 and 1..." << std::endl;
    avlTree.remove(30);
    avlTree.remove(1);

    std::cout << "Tree elements in order after deletion: ";
    printInOrder(avlTree);
    std::cout << std::endl;

    // Checking tree properties after deletion
    std::cout << "Tree size after deletion: " << avlTree.getSize() << std::endl;
    std::cout << "Min and Max after deletion: " << avlTree.getMin()->getKey() << ", " << avlTree.getMax()->getKey() << std::endl;

    // Testing tree clearing
    std::cout << "Clearing tree..." << std::endl;
    avlTree.clearTree();
    std::cout << "Tree empty after clearing? " << (avlTree.isEmpty() ? "Yes" : "No") << std::endl;

    return 0;
}
