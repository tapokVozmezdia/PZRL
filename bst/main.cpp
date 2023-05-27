#include "BST.h"
#include <iostream>

int main () {
    BinarySearchTree bst;
    bst.insert(6, 10.0);
    bst.insert(3, 20.0);
    bst.insert(8, 30.0);
    bst.insert(18, 40.0);
    bst.insert(9, 50.0);
    bst.insert(10, 60.0);
    bst.insert(9, 70.0);
    bst.insert(7, 80.0);
    bst.print();
    BinarySearchTree bst2(bst);
    bst2.print();
    std::cout << bst.size() <<" "<< bst2.size() << std::endl;
    bst.erase(9);
    bst.print();
    bst2.print();
    std::cout << bst.size() <<" "<< bst2.size() << std::endl;
    bst2 = std::move(bst);
    bst.print();
    bst2.print();
    std::cout << bst.size() <<" "<< bst2.size() << std::endl;

    BinarySearchTree::Iterator tmp = bst.begin();
    ++tmp;
    ++tmp;
    ++tmp;
    ++tmp;
    ++tmp;
    //std::cout << "iterator " << tmp->second << std::endl;

    // проверка функции find
    // Node* node = bst.find(15);
    // if (node != nullptr)
    //     std::cout << node->_key << std::endl;
    // else 
    //     std::cout << "!!!!!!" << std::endl;

    bst.erase(9);
    //bst.print();

    bst.erase(9);
    //bst.print();

    // bst.erase(2);
    // bst.print();

    // bst.erase(7);
    // bst.print();
}
