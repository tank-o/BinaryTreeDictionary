//
// Created by Charlie Surman on 26/11/2022.
//

#include "BinaryTreeDict.h"

int main(int argc, char* argv[]){
    // Create a new dictionary
    BinaryTreeDict* dict = new BinaryTreeDict();
    // Insert some entries
    dict->insert(1,"one");
    dict->insert(2,"two");
    dict->insert(3,"three");
    dict->insert(4,"four");
    dict->insert(5,"five");

    //delete dict
    delete dict;
}