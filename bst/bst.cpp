#include "BST.h"
#include <iostream>

using Node = BinarySearchTree::Node;
using Iterator = BinarySearchTree::Iterator;

void makeRootCopy(BinarySearchTree::Node* source, BinarySearchTree::Node* target)
{
    delete target->left;
    delete target->right;
    target->left = nullptr;
    target->right = nullptr;
    if (source->left != nullptr)
    {
        target->left = new Node(source->left->keyValuePair.first, source->left->keyValuePair.second);
        target->left->parent = target;
        makeRootCopy(source->left, target->left);
    }
    if (source->right != nullptr)
    {
        target->right = new Node(source->right->keyValuePair.first, source->right->keyValuePair.second);
        target->right->parent = target;
        makeRootCopy(source->right, target->right);
    }
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& other) {
    if (other._root == nullptr)
        return;
    /* дописать конструктор*/
    this->_root = new Node(other._root->keyValuePair.first, other._root->keyValuePair.second);
    makeRootCopy(other._root, this->_root);
    this->_size = other._size;
}

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other) {
    delete this->_root;
    if (other._root == nullptr)
    {
        this->_root = nullptr;
        return *this;
    }
    this->_root = new Node(other._root->keyValuePair.first, other._root->keyValuePair.second);
    makeRootCopy(other._root, this->_root);
    this->_size = other._size;
    return *this;
}

BinarySearchTree::BinarySearchTree(BinarySearchTree&& other) noexcept {
    delete this->_root;
    if (other._root == nullptr)
    {
        this->_root = nullptr;
        return;
    }
    this->_root = new Node(other._root->keyValuePair.first, other._root->keyValuePair.second);
    makeRootCopy(other._root, this->_root);
    this->_size = other._size;
    delete other._root;
    other._root = nullptr;
    other._size = 0;
}
    
BinarySearchTree& BinarySearchTree::operator=(BinarySearchTree&& other) noexcept {
    delete this->_root;
    if (other._root == nullptr)
    {
        this->_root = nullptr;
        return *this;
    }
    this->_root = new Node(other._root->keyValuePair.first, other._root->keyValuePair.second);
    makeRootCopy(other._root, this->_root);
    this->_size = other._size;
    delete other._root;
    other._root = nullptr;
    other._size = 0;
    return *this;
}

BinarySearchTree::~BinarySearchTree() {
    delete this->_root;
}

void BinarySearchTree::insert(const Key& key, const Value& value) {
    if (_root == nullptr) {         // пустое дерево
        _root = new Node(key, value);
        _size++;
    }
    else {                          // не пустое дерево
        insert(key, value, _root);
    }
}

void BinarySearchTree::insert(const Key& key, const Value& value, Node* node) {
    if (key >= node->keyValuePair.first) {
        if (node->right)                                // есть правое поддерево
            insert(key, value, node->right);            // рекурсивно добавили в правое поддерево

        else if (node->right == nullptr) {              // нет правого поддерева
            Node* newNode = new Node(key, value);       // создали новый узел
            newNode->parent = node;                     // родитель нового узла = root
            node->right = newNode;                      // определили правое поддерево
            _size++;
        }
    }
    else {
        if (node->left)                                 // есть левое поддерево
            insert(key, value, node->left);             // рекурсивно добавили в левое поддерево

        else if (node->left == nullptr) {               // нет левого поддерева
            Node* newNode = new Node(key, value);       // создали новый узел
            newNode->parent = node;                     // родитель нового узла = root
            node->left = newNode;                       // определили правое поддерево
            _size++;
        }
    }
}

void BinarySearchTree::print() {
    if (this->_root == nullptr)
    {
        std::cout << "Empty tree " << std::endl;
        return;
    }
    print(_root);
    std::cout << std::endl;
}

void BinarySearchTree::print(Node* node) {
    // напечатали левое поддерево
    if (_root == nullptr)
        std::cout << "Empty tree " << std::endl;
    
    if (node->left == nullptr) {        // дошли до листа 
        // ничего  не делаем
    }
    else {                              // печатаем левое поддерево 
        print(node->left);
    }
    

    // напечатали себя
    std::cout << node->keyValuePair.first << " --- ";
    
    // напечатали правое поддерево
    if (node->right == nullptr) {       // дошли до листа 
        // ничего  не делаем
    }
    else {                              // печатаем левое поддерево 
        print(node->right);
    }
}


void BinarySearchTree::printWithValues() {
    printWithValues(_root);
    std::cout << std::endl;
}

void BinarySearchTree::printWithValues(Node* node) {
    // напечатали левое поддерево
    if (_root == nullptr)
        std::cout << "Empty tree " << std::endl;
    
    if (node->left == nullptr) {        // дошли до листа 
    }
    else {                              // печатаем левое поддерево 
        printWithValues(node->left);
    }
    

    // напечатали себя
    std::cout << node->keyValuePair.first << " (" << node->keyValuePair.second  << ") " << " --- ";
    
    // напечатали правое поддерево
    if (node->right == nullptr) {       // дошли до листа 
        // ничего  не делаем
    }
    else {                              // печатаем левое поддерево 
        printWithValues(node->right);
    }// напечатали левое поддерево
    if (_root == nullptr)
        std::cout << "Empty tree " << std::endl;
    
    if (node->left == nullptr) {        // дошли до листа 
    }
    else {                              // печатаем левое поддерево 
        printWithValues(node->left);
    }
    

    // напечатали себя
    std::cout << node->keyValuePair.first << " --- ";
    
    // напечатали правое поддерево
    if (node->right == nullptr) {       // дошли до листа 
    }
    else {                              // печатаем левое поддерево 
        printWithValues(node->right);
    }
}


void BinarySearchTree::erase(const Key& key) {
    if (_root == nullptr)
        return;

    Node* node = findKey(key);
    erase(key, node);
}

void BinarySearchTree::erase(const Key& key, Node* node) {
    // 1 случай: обоих детей нет
    if (node->left == nullptr && node->right == nullptr) {
        Node* parent = node->parent;
        // находим, в какой ветке родителя находимся
        node->parent->left == node ? node->parent->left = nullptr : node->parent->right = nullptr;
        
        node->left = nullptr;
        node->right = nullptr;
        delete node;
        _size--;
    }

    // 2 случай: если одного из детей нет
    else if (node->left == nullptr || node->right == nullptr) {
        Node* parent = node->parent;
        Node* child = nullptr;
        if (node->left != nullptr)
            child = node->left;
        else
            child = node->right;

        child->parent = parent;
        
        // находим, в какой ветке родителя находимся
        node->parent->left == node ? node->parent->left = child : node->parent->right = child;
        
        node->left = nullptr;
        node->right = nullptr;
        delete node;
        _size--;
    }

    // 3 случай: если оба ребёнка присутствуют
    else {
        // 3.1: если левый узел правого поддерева отсутствует
        if (node->right->left == nullptr) {
            // копируем ключ из правого потомка
            node->keyValuePair.first = node->right->keyValuePair.first;

            // запоминаем ссылку на правое поддерево правого дочернего узла
            Node* tmp = node->right->right;

            // удаляем правый дочерний узел
            delete node->right;
            _size--;

            // переписываем ссылку на правое поддерево правого дочернего узла (который только что удалили)
            node->right = tmp;
        }
        else {  // есть левый узел правого поддерева
            // самый левый узел правого поддерева
            Node* tmp = node->right->left;
            while (tmp->left != nullptr) {
                tmp = tmp->left;
            }
            node->keyValuePair.first = tmp->keyValuePair.first;
            erase(key, tmp);
            return;
        }
    }
}

BinarySearchTree::Iterator BinarySearchTree::find(const Key& key) {
    Node* tmp = findKey(key);
    return Iterator(tmp);
}

BinarySearchTree::Node* BinarySearchTree::findKey(const Key& key) const{
    if (_root == nullptr)
        return nullptr;
    
    return find(key, _root);
}

Node* BinarySearchTree::find(Key key, Node* node) const{
    if (node == nullptr)
        return nullptr;
    
    if (key == node->keyValuePair.first)  // нашли узел
        return node;

    key >= node->keyValuePair.first ? find(key, node->right) : find(key, node->left);
}

std::pair<BinarySearchTree::Iterator, BinarySearchTree::Iterator> BinarySearchTree::equalRange(const Key& key) {
    Node* firstKey = findKey(key);
    return std::pair<BinarySearchTree::Iterator, BinarySearchTree::Iterator> (Iterator(_root), Iterator(_root));
}

BinarySearchTree::Iterator BinarySearchTree::min(const Key& key) const {
    Node* tmp = findKey(key);   // наши поддерево
    while (tmp->left != nullptr) {
        tmp = tmp->left;
    }
    return Iterator(tmp);
}

BinarySearchTree::Iterator BinarySearchTree::max(const Key& key) const {
    Node* tmp = findKey(key);   // наши поддерево
    while (tmp->right != nullptr) {
        tmp = tmp->right;
    }
    return Iterator(tmp);
}

BinarySearchTree::Iterator BinarySearchTree::begin() {
    Node* tmp = _root;
    while (tmp->left!= nullptr) {
        tmp = tmp->left;
    }
    return Iterator(tmp);
}

BinarySearchTree::Iterator BinarySearchTree::end() {
    Node* tmp = _root;
    while (tmp->right != nullptr) {
        tmp = tmp->right;
    }
    return Iterator(tmp);
}

size_t BinarySearchTree::size() const {
    return _size;
}

BinarySearchTree::Iterator::Iterator(Node* node) : _node(node){
}

std::pair<Key, Value>& BinarySearchTree::Iterator::operator*() {
    return _node->keyValuePair;
}

const std::pair<Key, Value>& BinarySearchTree::Iterator::operator*() const {
    return _node->keyValuePair;
}

std::pair<Key, Value>* BinarySearchTree::Iterator::operator->() {
    return &_node->keyValuePair;
}


const std::pair<Key, Value>* BinarySearchTree::Iterator::operator->() const {
    return &_node->keyValuePair;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++() {
    Node* tmp = nullptr;
    if (_node->right) {
        tmp = _node->right;
        while(tmp->left) {
            tmp = tmp->left;
        }
        _node = tmp;
        return *this;
    }
    else {
        tmp = _node;
        while(tmp->parent) {
            tmp = tmp->parent;
            if (tmp->keyValuePair.first > _node->keyValuePair.first) {
                _node = tmp;
                return *this;
            }
        }
        return *this;
    }
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++(int count) {
    Node* tmp = nullptr;
    if (_node->right) {
        tmp = _node->right;
        while(tmp->left) {
            tmp = tmp->left;
        }
        _node = tmp;
        return *this;
    }
    else {
        tmp = _node;
        while(tmp->parent) {
            tmp = tmp->parent;
            if (tmp->keyValuePair.first > _node->keyValuePair.first) {
                _node = tmp;
                return *this;
            }
        }
        return *this;
    }
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--() {
    Node* tmp = nullptr;
    if (_node->left) {
        tmp = _node->left;
        while(tmp->right) {
            tmp = tmp->right;
        }
        _node = tmp;
        return *this;
    }
    else {
        tmp = _node;
        while (tmp->parent)
        {
            tmp = tmp->parent;
            if (tmp->keyValuePair.first < _node->keyValuePair.first) {
                _node = tmp;
                return *this;
            }
        }
    }
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--(int count) {
    Node* tmp = nullptr;
    if (_node->left) {
        tmp = _node->left;
        while(tmp->right) {
            tmp = tmp->right;
        }
        _node = tmp;
        return *this;
    }
    else {
        tmp = _node;
        while (tmp->parent)
        {
            tmp = tmp->parent;
            if (tmp->keyValuePair.first < _node->keyValuePair.first) {
                _node = tmp;
                return *this;
            }
        }
    }
}

bool BinarySearchTree::Iterator::operator==(const Iterator& other) const {
    return _node == other._node;
}

bool BinarySearchTree::Iterator::operator!=(const Iterator& other) const {
    return _node != other._node;
}

// BinarySearchTree::Iterator BinarySearchTree::treeSuccessor(Node* node) {
//     // if (node->right != nullptr) {
//     //     Iterator right(node->right);
//     //     return min(right->first);
//     // } 
// }

BinarySearchTree::Node::Node(Key key, Value value,  Node* parent, 
                            Node* left, Node* right) : parent(parent), left(left), right(right) {
    
    keyValuePair = std::pair<Key, Value>(key, value);
}