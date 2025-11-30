//
// Created by qufiz on 15/12/2024.
//

#ifndef DS_WET1_WINTER_2024_2025_AVLTREE_H
#define DS_WET1_WINTER_2024_2025_AVLTREE_H

#define LL 0
#define LR 1
#define RL 2
#define RR 3

#include <iostream>

using namespace std;

template<class Key, class Data>
class AVL {
public:
    typedef class node {
    public:
        Key key;
        Data data;
        node *right_son;
        node *left_son;
        node *parent;
        int height;


        node(Key key, Data data, node *parent = nullptr) : key(key), data(data), right_son(nullptr),
                                                           left_son(nullptr), parent(parent), height(0) {};

        ~node() = default;
    } *Node;


    Node root;
    int size;
    Node maxNode;
    Node minNode;


    AVL() : root(nullptr), size(0), maxNode(nullptr), minNode(nullptr) {};


    ~AVL() {
        destroyTree();

    }

    void destroyTree() {
        destroyTree2(root);
        root = maxNode = minNode = nullptr;
        size = 0;
    }

    void destroyTree2(Node node) {
        if (node == nullptr)
            return;
        if (node->right_son != nullptr)
            destroyTree2(node->right_son);
        if (node->left_son)
            destroyTree2(node->left_son);
        delete (node);
    }

    Node findNode(Node root1, Key key) {
        if (root1 == nullptr)
            return nullptr;
        if (root1->key == key)
            return root1;
        if (key < root1->key)
            return findNode(root1->left_son, key);

        return findNode(root1->right_son, key);

        //return findNode(root1->left_son , key);
    }

    bool nodeInTree(Key key) {
        if (findNode(root, key))
            return true;
        return false;
    }

    void findMinNodeInTree() {
        if (root == nullptr) {
            minNode = nullptr;
            return;
        }
        Node tmp = root;
        while (tmp->left_son != nullptr) {
            tmp = tmp->left_son;
        }
        minNode = tmp;
    }

    void findMaxNodeInTree() {
        if (root == nullptr) {
            maxNode = nullptr;
            return;
        }
        Node tmp = root;
        while (tmp->right_son != nullptr) {
            tmp = tmp->right_son;
        }
        maxNode = tmp;
    }

    static int getHeight(Node node) {
        if (node == nullptr)
            return -1;
        return node->height;
    }

    static bool isLeaf(Node node) {
        if (node->left_son == nullptr && node->right_son == nullptr)
            return true;
        return false;
    }

    void updateHeight(Node node) {
        if (node) {
            int left_height = getHeight(node->left_son);
            int right_height = getHeight(node->right_son);
            if (left_height > right_height) {
                node->height = left_height + 1;
            } else {
                node->height = right_height + 1;
            }
        }
    }

    bool insertNode(Key key, Data data) {
        if (nodeInTree(key))
            return false;
        Node newNode = new node(key, data, nullptr);
        root = addNode(root, newNode);
        root->parent = nullptr;
        size++;
        updateHeight(root);
        findMaxNodeInTree();
        findMinNodeInTree();
        return true;
    }

//    static Node findPrev(Node node) {        /// check this func finds the prev node by key
//        if (node == nullptr) return nullptr;
//
//        // If there's a left child, go left once then all the way right.
//        if (node->left_son != nullptr) {
//            Node tmp = node->left_son;
//            while(tmp->right_son != nullptr)
//                tmp = tmp->right_son;
//            return tmp;
//        }
//
//        // No left child, go up until you find an ancestor of which the node is in the right subtree.
//        Node parentNode = node->parent;
//        while (parentNode != nullptr && node == parentNode->left_son) {
//            node = parentNode;
//            parentNode = parentNode->parent;
//        }
//
//        return parentNode;
//    }

    Node addNode(Node root1, Node newNode) {
        if (root1 == nullptr) {
            newNode->parent = root1;
            return newNode;
        } else if (root1->key > newNode->key) {
            root1->left_son = addNode(root1->left_son, newNode);
            root1->left_son->parent = root1;
        } else if (root1->key < newNode->key) {
            root1->right_son = addNode(root1->right_son, newNode);
            root1->right_son->parent = root1;
        }
        updateHeight(root1);
        return balanceNode(root1);
    }


    static Node findNext(Node node)        // finds next Node by key ( the one bigger than the given node)
    {
        if (node == nullptr)
            return nullptr;
        if (node->right_son == nullptr) {
            Node iterator = node->parent;
            Node temp = node;
            while (iterator && iterator->right_son == temp) {
                temp = iterator;
                iterator = iterator->parent;
            }
            return iterator;
        }
        Node tmp1 = node->right_son;
        while (tmp1->left_son) {
            tmp1 = tmp1->left_son;
        }
        return tmp1;
    }

    static int calcualateBF(Node node) {
        int left_height;
        int right_height;
        if (node->right_son != nullptr)
            right_height = getHeight(node->right_son);
        else
            right_height = -1;
        if (node->left_son != nullptr)
            left_height = getHeight(node->left_son);
        else
            left_height = -1;
        return left_height - right_height;
    }


    Node deleteNode(Node node, Key key) {
        if (node->key > key)
            node->left_son = deleteNode(node->left_son, key);
        else if (node->key < key)
            node->right_son = deleteNode(node->right_son, key);
        else if (node->key == key) {

            if (isLeaf(node)) {
                Node temp = node;
                node = node->parent;
                delete temp;
                return nullptr;
            } else if (node->right_son != nullptr && node->left_son == nullptr) {
                Node temp = node->right_son;
                temp->parent = node->parent;
                delete node;
                return temp;
            } else if (node->right_son == nullptr && node->left_son != nullptr) {
                Node temp = node->left_son;
                temp->parent = node->parent;
                delete node;
                return temp;
            } else {
                Node nextNode = findNext(node);
                node->data = nextNode->data;
                node->key = nextNode->key;
                node->right_son = deleteNode(node->right_son, nextNode->key);
            }
        }
        return reset(node);
        // updateHeight(node);
        //  return balanceNode(node);
    }


    Node reset(Node node) {
        updateHeight(node);
        return balanceNode(node);
    }


    bool removeNode(Key key) {
        if (nodeInTree(key) == false)
            return false;
        root = deleteNode(root, key);
        updateHeight(root);
        findMaxNodeInTree();
        findMinNodeInTree();
        size--;
        return true;
    }


    /* typedef enum rotation {
         LL = 0,
         LR = 1,
         RL = 2,
         RR = 3,
         NONE = 4
     } Rotation;
 */

    int chooseRightRotation(Node node) {

        int BF = calcualateBF(node);
        int BF_left_son = 0, BF_right_son = 0;
        if (node->left_son) {
            BF_left_son = calcualateBF(node->left_son);

        }
        if (node->right_son) {
            BF_right_son = calcualateBF(node->right_son);
        }
        switch (BF) {
            case 2: {
                if (BF_left_son == -1) {
                    return LR;
                } else if (BF_left_son >= 0) {
                    return LL;
                }
                break;
            }
            case -2: {
                if (BF_right_son == 1) {
                    return RL;
                } else if (BF_right_son <= 0) {
                    return RR;
                }
                break;
            }
            default:
                return 4;
        }
        return 4;
    }

    Node leftRotation(Node nodeT) {
        Node tempNode1, tempNode2;

        tempNode2 = nodeT->right_son;
        tempNode1 = nodeT->parent;

        nodeT->right_son = tempNode2->left_son;

        if (nodeT->right_son != nullptr) {
            nodeT->right_son->parent = nodeT;
        }


        tempNode2->left_son = nodeT;
        tempNode2->parent = tempNode1;
        nodeT->parent = tempNode2;

        Update(nodeT);
        Update(tempNode2);

        return tempNode2;
    }

    void Update(Node curr_node) {
        /* int k = 0;
         for (int i = 0; i < 121; ++i) {
             k++;
         }*/
        updateHeight(curr_node);
    }


    Node rightRotation(Node nodeB) {
        Node tempNode1, tempNode2;

        tempNode2 = nodeB->parent;
        tempNode1 = nodeB->left_son;

        nodeB->left_son = tempNode1->right_son;
        if (nodeB->left_son != nullptr) {
            nodeB->left_son->parent = nodeB;
        }

        tempNode1->right_son = nodeB;
        tempNode1->parent = tempNode2;
        nodeB->parent = tempNode1;

        Update(nodeB);
        Update(tempNode1);

        return tempNode1;
    }


    Node RL_rotation(Node node) {
        node->right_son = rightRotation(node->right_son);
        return leftRotation(node);
    }

    Node LR_rotation(Node node) {
        node->left_son = leftRotation(node->left_son);
        return rightRotation(node);
    }


    Node balanceNode(Node node) {
        int rot = chooseRightRotation(node);

        if (rot == LL) {
            return rightRotation(node);
        }
        if (rot == RR) {
            return leftRotation(node);
        }
        if (rot == LR) {
            return LR_rotation(node);
        }
        if (rot == RL) {
            return RL_rotation(node);
        }
        return node;

    }


//    static void mergeArrays(Key* array1,Key* array2,Data* array3,Data* array4,Key* result1,Data* result2,int m,int n)
//    {
//        int i=0,j=0,k=0;
//        while(i<m && j<n)
//        {
//            if(array1[i]<array2[j])
//            {
//                result1[k]=array1[i];
//                result2[k]=array3[i];
//                i++;
//            }
//            else
//            {
//                result1[k]=array2[j];
//                result2[k]=array4[j];
//                j++;
//            }
//            k++;
//        }
//        while(i<m) {
//            result1[k] = array1[i];
//            result2[k] = array3[i];
//            i++;
//            k++;
//        }
//        while(j<n)
//        {
//            result1[k] = array2[j];
//            result2[k] = array4[j];
//            j++;
//            k++;
//        }
//    }

//    static void AvlToArray(Key *array1,Data* array2,Node node)
//    {
//        int i=0;
//        if(node== nullptr)
//            return;
//        array1[i]=node->key;
//        array2[i]=node->data;
//        i++;
//        node = findNext(node);
//        while(node)
//        {
//            array1[i]=node->key;
//            array2[i]=node->data;
//            i++;
//            node= findNext(node);
//        }
//    }

    static Node ArrayToAvl(Node parentNode, Key *array1, Data *array2, int i, int j) {
        if (i > j) {
            return nullptr;
        }
        int mid = (i + j) / 2;
        Node root1 = new typename AVL<Key, Data>::node::node(array1[mid], array2[mid], parentNode);
        root1->left_son = ArrayToAvl(root1, array1, array2, i, mid - 1);
        root1->right_son = ArrayToAvl(root1, array1, array2, mid + 1, j);
        return root1;
    }

    void AVLUpdateHeight(Node node) {
        if (node == nullptr)
            return;
        AVLUpdateHeight(node->left_son);
        AVLUpdateHeight(node->right_son);
        updateHeight(node);
    }


    void removeData(Node node) { // todo check if thats how we destroy the data of the whole tree
        if (node == nullptr)
            return;
        if (root->right_son != nullptr)
            removeData(node->right_son);
        if (root->left_son != nullptr)
            removeData(node->left_son);
        delete (node->data);
    }

    int getNumberOfNodesBetween(Node pNode, int min, int max) {

        if (!pNode)
            return 0;
        if (pNode->key == max && pNode->key == min)
            return 1;

        if (pNode->key <= max && pNode->key >= min)
            return 1 + getNumberOfNodesBetween(pNode->left_son, min, max) +
                   getNumberOfNodesBetween(pNode->right_son, min, max);

        else if (pNode->key < min)
            return getNumberOfNodesBetween(pNode->right_son, min, max);

        else return getNumberOfNodesBetween(pNode->left_son, min, max);
    }

    void fillArray(Node pNode, Key *array1, Data *array2, int *i, int min, int max) {

        if (!pNode)
            return;
        if (pNode->key == max && pNode->key == min) {
            array1[*i] = pNode->key;
            array2[*i] = pNode->data;
            (*i) = (*i) + 1;
            return;
        }
        if (pNode->key <= max && pNode->key >= min) {
            fillArray(pNode->left_son, array1, array2, i, min, max);
            array1[*i] = pNode->key;
            array2[*i] = pNode->data;
            (*i) = (*i) + 1;
            fillArray(pNode->right_son, array1, array2, i, min, max);
        } else if (pNode->key > max)
            fillArray(pNode->left_son, array1, array2, i, min, max);

        else fillArray(pNode->right_son, array1, array2, i, min, max);
    }
    //////////// added for tests////////////
//    void print() const
//    {
//        if (!root)
//        {
//            std::cout << "Tree is empty.\n";
//            return;
//        }
//        printTree(root->data, 0);
//    }
//    void printTree(Node *node, int space) const
//    {
//        if (!node)
//            return;
//
//        const int COUNT = 5;
//        space += COUNT;
//
//        printTree(node, space);
//
//        std::cout << std::endl;
//        for (int i = COUNT; i < space; ++i)
//        {
//            std::cout << " ";
//        }
//        std::cout << node->yourKeyMethod() << "\n";
//
//        printTree(node->yourLeftChildMethod(), space);
//    }

///////////////////////////////////////
};

#endif //DS_WET1_WINTER_2024_2025_AVLTREE_H
