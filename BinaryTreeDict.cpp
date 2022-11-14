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

Node* BinaryTreeDict::lookupWorker(Node* current,int key){
    if (current == nullptr) {return nullptr;}
    if (current->key == key) {
        return current;
    } else if (key > current->key) {
        lookupWorker(current->bigger, key);
    } else {
        lookupWorker(current->smaller, key);
    }
    return nullptr;
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

Node* BinaryTreeDict::lookup(int key) {
    lookupWorker(this->head,key);
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
    Node* copiedNode = new Node(node->key,node->item);
    copiedNode->smaller = deepCopyWorker(node->smaller);
    copiedNode->bigger = deepCopyWorker(node->bigger);
    return copiedNode;
}

BinaryTreeDict::BinaryTreeDict(const BinaryTreeDict& originalDict) {
    this->head = deepCopyWorker(originalDict.head);;
}

BinaryTreeDict::~BinaryTreeDict() {
    deepDeleteWorker(this->head);
}

void BinaryTreeDict::rotateLeft(Node*& root) {
    Node* alpha= root->smaller;
    Node* b = root->bigger;
    Node* beta = b->smaller;
    Node* gamma = b->bigger;

    root->bigger = beta;
    b->smaller = root;
}

void BinaryTreeDict::testRotations() {
    Node* node = lookup(31);
    rotateLeft(node);
    std::cout << "Printing new order after rotations" << std::endl;
    displayKeyOrder();
}
