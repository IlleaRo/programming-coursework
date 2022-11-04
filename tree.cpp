//
// Created by Illea on 30.10.2022.
//

#include "tree.h"

tree::tree() {
    this->str = nullptr;
    this->right= nullptr;
    this->left = nullptr;
}
tree::tree(char * value) {
    unsigned long long sizeOfValue  = strlen(value)+1;
    this->str = new char[sizeOfValue];
    strcpy(this->str,value);
    this->right = nullptr;
    this->left = nullptr;
}

void tree::setValue(char * value) {
    delete[] (this->str);
    unsigned long long sizeOfValue  = strlen(value)+1;
    this->str = new char[sizeOfValue];
    strcpy(this->str,value);
}
