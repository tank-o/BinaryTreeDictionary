//
// Created by Charlie Surman on 06/10/2022.
//

#include "Node.h"

Node::Node(int key,std::string item){
    this->key = key;
    this->item = item;
    this->smaller = nullptr;
    this->bigger = nullptr;
};
