//
// Created by Charlie Surman on 06/10/2022.
//

#ifndef BINARYTREEDICT_BINARYTREEDICT_H
#define BINARYTREEDICT_BINARYTREEDICT_H

#include <string>
#include "Node.h"

class BinaryTreeDict {
public:
    BinaryTreeDict();
    BinaryTreeDict(const BinaryTreeDict &);
    BinaryTreeDict(BinaryTreeDict &&) noexcept ;
    std::string* lookup(int);
    void insert(int,std::string);
    void displayKeyOrder();
    void testRotations();
    BinaryTreeDict & operator=(const BinaryTreeDict &);
    ~BinaryTreeDict();
    BinaryTreeDict & operator=(BinaryTreeDict &&) noexcept ;
    void remove(int);
private:
    Node* head;
    void displayEntriesWorker(Node*);
    std::string* lookupWorker(Node*,int);
    void rotateLeft(Node*&);
    void insertWorker(Node*&,int,std::string);
    void deepDeleteWorker(Node*); // recursive worker performing deep delete
    Node* deepCopyWorker(Node*);
};


#endif //BINARYTREEDICT_BINARYTREEDICT_H
