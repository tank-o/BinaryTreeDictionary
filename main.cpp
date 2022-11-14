#include "BinaryTreeDict.h"
#include "keyitemgenerator.h"

//
// Created by Charlie Surman on 04/11/2022.
//
int main(){
    BinaryTreeDict dict = BinaryTreeDict();
    KeyItemGenerator gen = KeyItemGenerator();

    for (int i = 0;i < 25000;i++){
        dict.insert(i,gen.randomItem());
    }

    dict.lookup(1000);
}