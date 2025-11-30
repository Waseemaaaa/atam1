//
// Created by reemd on 18/02/2024.
//
#include <iostream>
#include "AVLtree.h"

int main() {
    AVL<int, int> avlTree;

    // הוספת ערכים שיצורו תרחישים שונים
    std::cout << "Inserting values...\n";
    avlTree.insertNode(40, 40); // שורש
    avlTree.insertNode(30, 30); // בן שמאלי
    avlTree.insertNode(50, 50); // בן ימני
    avlTree.insertNode(20, 20); // בן שמאלי של 30
    avlTree.insertNode(45, 45); // בן ימני של 40
    avlTree.insertNode(60, 60); // בן ימני של 50
    avlTree.insertNode(55, 55); // בן שמאלי של 60

    std::cout << "Initial tree structure:\n";
    avlTree.printInOrder();

    // בדיקת גודל וגובה לפני המחיקות
    std::cout << "\nTree size: " << avlTree.size << std::endl;
    std::cout << "Tree height: " << avlTree.heightTree(avlTree.getRoot()) << std::endl;

    // 1. מחיקת צומת עם שני בנים
    std::cout << "\nRemoving node (50) with two children...\n";
    avlTree.removeNode(50);
    printInOrder(avlTree);

    // 2. מחיקת צומת עם בן ימני בלבד
    std::cout << "\nRemoving node (60) with right child only...\n";
    avlTree.remove(60);
    printInOrder(avlTree);

    // 3. מחיקת צומת עם בן שמאלי בלבד
    std::cout << "\nRe-inserting 60 and removing node (30) with left child only...\n";
    avlTree.insert(60, 60);
    avlTree.remove(30);
    printInOrder(avlTree);

    // 4. מחיקת צומת ללא ילדים
    std::cout << "\nRemoving node (20) with no children...\n";
    avlTree.remove(20);
    printInOrder(avlTree);

    // בדיקת הערך המינימלי והמקסימלי לאחר המחיקות
    std::cout << "\nMinimum value in tree: " << avlTree.getMin()->getKey() << std::endl;
    std::cout << "Maximum value in tree: " << avlTree.getMax()->getKey() << std::endl;


    // בדיקת גודל וגובה לאחר המחיקות
    std::cout << "\nTree size after deletions: " << avlTree.getSize() << std::endl;
    std::cout << "Tree height after deletions: " << avlTree.heightTree(avlTree.getRoot()) << std::endl;

    // בדיקת find, clear, isEmpty
    std::cout << "\nFinding 45...\n";
    if (avlTree.findNode(45) != nullptr) {
        std::cout << "Found node with key 45\n";
    } else {
        std::cout << "Node with key 45 not found\n";
    }

    std::cout << "\nClearing the tree...\n";
    avlTree.clearTree();
    std::cout << "Checking if tree is empty: " << (avlTree.isEmpty() ? "Empty" : "Not Empty") << std::endl;

    // נוסיף ערכים שיצרו תנאים לסיבובים שונים
    std::cout << "\nInserting values to force rotations...\n";
    avlTree.insert(10, 10);
    avlTree.insert(70, 70);
    printInOrder(avlTree);

    // בדיקת גודל וגובה לפני סיבובים
    std::cout << "\nTree size before rotations: " << avlTree.getSize() << std::endl;
    std::cout << "Tree height before rotations: " << avlTree.heightTree(avlTree.getRoot()) << std::endl;

    // הסרת ערך שיגרום לסיבוב LL או LR
    std::cout << "\nRemoving a node to cause LL or LR rotation...\n";
    avlTree.remove(45);
    printInOrder(avlTree);

    // הוספה שתגרום לסיבוב RR או RL
    std::cout << "\nInserting a node to cause RR or RL rotation...\n";
    avlTree.insert(75, 75);
    printInOrder(avlTree);

    // בדיקת הערך המינימלי והמקסימלי לאחר הסיבובים
    std::cout << "\nMinimum value in tree after rotations: " << avlTree.getMin()->getKey() << std::endl;
    std::cout << "Maximum value in tree after rotations: " << avlTree.getMax()->getKey() << std::endl;

    // בדיקת גודל וגובה לאחר הסיבובים
    std::cout << "\nTree size after rotations: " << avlTree.getSize() << std::endl;
    std::cout << "Tree height after rotations: " << avlTree.heightTree(avlTree.getRoot()) << std::endl;

    // נקיון העץ ובדיקה שהעץ ריק
    std::cout << "\nClearing the tree...\n";
    avlTree.clearTree();
    std::cout << "Checking if tree is empty: " << (avlTree.isEmpty() ? "Empty" : "Not Empty") << std::endl;

    return 0;
}
