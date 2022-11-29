//
// Created by Charlie Surman on 06/10/2022.
//

#include <iostream>
#include "BinaryTreeDict.h"

void BinaryTreeDict::displayKeyOrder() {
    displayEntriesWorker(this->head);
}

void BinaryTreeDict::displayEntriesWorker(Node* currentNode) {
    if (currentNode == nullptr) return;
    displayEntriesWorker(currentNode->smaller);
    displayEntriesWorker(currentNode->bigger);
    std::cout << currentNode->key << "+" << currentNode->item << std::endl;
}

std::string* BinaryTreeDict::lookupWorker(Node* current,int key){
    if (current == nullptr) {
        return nullptr;
    }
    if (current->key == key) {
        return &current->item;
    } else if (key > current->key) {
        lookupWorker(current->bigger, key);
    } else {
        lookupWorker(current->smaller, key);
    }

}

void BinaryTreeDict::insertWorker(Node* &current,int key,std::string item){
    if (current == nullptr){
        current = new Node(key,item);
        return;
    }
    if (current->key == key) {
        current->item = item;
        return;
    } else if (key > current->key){
        insertWorker(current->bigger,key,item);
    } else {
        insertWorker(current->smaller,key,item);
    }
}

std::string* BinaryTreeDict::lookup(int key) {
    Node* root = this->head;
    while (root != NULL) {
        if (root->key == key)
            return &root->item;
        if (root->key < key)
            root = root->bigger;
        else
            root = root->smaller;
    }
    return nullptr;
}

BinaryTreeDict::BinaryTreeDict() {
    this->head = nullptr;
}

void BinaryTreeDict::insert(int key, std::string item) {
    insertWorker(this->head,key,item);
}

void BinaryTreeDict::deepDeleteWorker(Node* node) {
    if (node == nullptr) return;
    deepDeleteWorker(node->bigger);
    deepDeleteWorker(node->smaller);
    delete node;
}

Node* BinaryTreeDict::deepCopyWorker(Node* node){
    if (node == nullptr) return nullptr;
    insert(node->key,node->item);
    deepCopyWorker(node->smaller);
    deepCopyWorker(node->bigger);
    return this->head;
}

BinaryTreeDict::BinaryTreeDict(const BinaryTreeDict& originalDict) {
    this->head = deepCopyWorker(originalDict.head);;
}

BinaryTreeDict::BinaryTreeDict(BinaryTreeDict&& originalDict)  noexcept {
    if (&originalDict == this)
        return;
    this->head = originalDict.head;
    originalDict.head = nullptr;
}

BinaryTreeDict::~BinaryTreeDict() {
    deepDeleteWorker(this->head);
}

void BinaryTreeDict::rotateLeft(Node*& root) {
    Node* b = root->bigger;
    Node* beta = b->smaller;

    root->bigger = beta;
    b->smaller = root;
    root = b;
}

BinaryTreeDict &BinaryTreeDict::operator=(const BinaryTreeDict& source) {
    if (this == &source)
        return *this;
    this->head = deepCopyWorker(source.head);
    return *this;
}

BinaryTreeDict &BinaryTreeDict::operator=(BinaryTreeDict&& source) noexcept {
    if (&source == this)
        return *this;
    deepDeleteWorker(this->head);
    this->head = source.head;
    source.head = nullptr;
    return *this;
}

Node* minValueNode(Node* node){
    Node* current = node;
    /* loop down to find the leftmost leaf */
    while (current && current->smaller != NULL)
        current = current->smaller;

    return current;
}

void BinaryTreeDict::remove(int key) {
    //find node to be deleted
    Node *nodeToRemove = this->head;
    Node *parent = nullptr;
    while (nodeToRemove != nullptr && nodeToRemove->key != key) {
        parent = nodeToRemove;
        if (key < nodeToRemove->key)
            nodeToRemove = nodeToRemove->smaller;
        else
            nodeToRemove = nodeToRemove->bigger;
    }
    if (nodeToRemove == nullptr) return;
    if (nodeToRemove->smaller == nullptr and nodeToRemove->bigger == nullptr){
        //is root node
        if (parent == nullptr){
            this->head = nullptr;
            delete nodeToRemove;
            return;
        }
        if (parent->smaller == nodeToRemove){
            parent->smaller = nullptr;
        } else {
            parent->bigger = nullptr;
        }
        delete nodeToRemove;
        return;
    }  else if ((nodeToRemove->smaller == nullptr) or (nodeToRemove->bigger == nullptr)) {
        //node has one child
        Node *child = nodeToRemove->smaller ? nodeToRemove->smaller : nodeToRemove->bigger;
        if (parent == nullptr){
            this->head = child;
            delete nodeToRemove;
            return;
        }
        if (nodeToRemove->smaller == child) {
            parent->smaller = child;
        } else {
            parent->bigger = child;
        }
        free(nodeToRemove);
        return;
    }
    //node has two children
    Node* successor = minValueNode(nodeToRemove->bigger);
    remove(successor->key);
    nodeToRemove->key = successor->key;
    nodeToRemove->item = successor->item;
}
