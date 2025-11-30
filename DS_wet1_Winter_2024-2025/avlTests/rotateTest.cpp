//
// Created by reemd on 16/02/2024.
//
#include "AVL.h"

int main() {
    AVL<int, int> avl;

    // LL Rotation
    std::cout << "Testing LL Rotation" << std::endl;
    avl.insert(30, 30);
    avl.insert(20, 20);
    avl.insert(10, 10);
    printInOrder(avl);
    avl.clearTree();

    // RR Rotation
    std::cout << "Testing RR Rotation" << std::endl;
    avl.insert(10, 10);
    avl.insert(20, 20);
    avl.insert(30, 30);
    printInOrder(avl);
    avl.clearTree();

    // LR Rotation
    std::cout << "Testing LR Rotation" << std::endl;
    avl.insert(30, 30);
    avl.insert(10, 10);
    avl.insert(20, 20);
    printInOrder(avl);
    avl.clearTree();

    // RL Rotation
    std::cout << "Testing RL Rotation" << std::endl;
    avl.insert(10, 10);
    avl.insert(30, 30);
    avl.insert(20, 20);
    printInOrder(avl);
    avl.clearTree();

    std::cout << "Starting mixed rotations test" << std::endl;

    // Insertions that lead to LL and RR rotations
    std::cout << "Inserting elements to cause LL and RR rotations" << std::endl;
    avl.insert(30, 30);
    avl.insert(20, 20);
    avl.insert(10, 10);
    avl.insert(40, 40);
    avl.insert(50, 50);
    printInOrder(avl);

    // Insertions that lead to LR and RL rotations
    std::cout << "Inserting elements to cause LR and RL rotations" << std::endl;
    avl.insert(25, 25);
    avl.insert(22, 22);
    avl.insert(45, 45);
    avl.insert(47, 47);
    printInOrder(avl);

    // More insertions to create complex scenarios
    std::cout << "Creating complex scenarios with more insertions" << std::endl;
    avl.insert(15, 15);
    avl.insert(35, 35);
    printInOrder(avl);

    // Deletions that might cause rotations
    std::cout << "Deleting elements that might cause rotations" << std::endl;
    avl.remove(50);
    avl.remove(20);
    printInOrder(avl);

    return 0;
}


