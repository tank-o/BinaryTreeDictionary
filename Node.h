//
// Created by Charlie Surman on 06/10/2022.
//

#ifndef BINARYTREEDICT_NODE_H
#define BINARYTREEDICT_NODE_H
#include <string>

class Node {
public:
    int key;
    std::string item;
    Node* smaller;
    Node* bigger;
    Node(int,std::string);
};


#endif //BINARYTREEDICT_NODE_H
