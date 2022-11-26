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
    Node* alpha= root->smaller;
    Node* b = root->bigger;
    Node* beta = b->smaller;
    Node* gamma = b->bigger;

    root->bigger = beta;
    b->smaller = root;
}

BinaryTreeDict &BinaryTreeDict::operator=(const BinaryTreeDict& source) {
    if (this == &source)
        return *this;
    deepCopyWorker(source.head);
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

void BinaryTreeDict::remove(int keyToRemove) {
    Node* nodeToRemove = this->head;
    Node* parent = nullptr;
    //find the node to remove
    while (nodeToRemove != nullptr) {
        if (nodeToRemove->key == keyToRemove) break;
        parent = nodeToRemove;
        if (nodeToRemove->key < keyToRemove)
            nodeToRemove = nodeToRemove->bigger;
        else
            nodeToRemove = nodeToRemove->smaller;
    }

    //if the node to remove has no children
    if (nodeToRemove->smaller == nullptr && nodeToRemove->bigger == nullptr) {
        if (parent == nullptr) {
            this->head = nullptr;
        } else if (parent->smaller == nodeToRemove) {
            parent->smaller = nullptr;
        } else {
            parent->bigger = nullptr;
        }
        delete nodeToRemove;
        return;
    }

    //if the node to remove has one child
    if (nodeToRemove->smaller == nullptr || nodeToRemove->bigger == nullptr) {
        Node* childOfRemoval = nodeToRemove->smaller == nullptr ? nodeToRemove->bigger : nodeToRemove->smaller;
        if (parent == nullptr) {
            this->head = childOfRemoval;
        } else if (parent->smaller == nodeToRemove) {
            parent->smaller = childOfRemoval;
        } else {
            parent->bigger = childOfRemoval;
        }
        delete nodeToRemove;
        return;
    }

    //if the node to remove has two children

}

