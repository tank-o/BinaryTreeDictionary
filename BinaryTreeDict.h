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
    Node* lookup(int);
    void insert(int,std::string);
    void displayKeyOrder();
    void testRotations();
    ~BinaryTreeDict();
private:
    Node* head;
    void displayEntriesWorker(Node*);
    Node* lookupWorker(Node*,int);
    void rotateLeft(Node*&);
    void insertWorker(Node*&,int,std::string);
    void deepDeleteWorker(Node*); // recursive worker performing deep delete
    Node* deepCopyWorker(Node*);
};


#endif //BINARYTREEDICT_BINARYTREEDICT_H
