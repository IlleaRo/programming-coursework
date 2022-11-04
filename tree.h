//
// Created by Illea on 30.10.2022.
//

#ifndef CURSEWORK_1_TREE_H
#define CURSEWORK_1_TREE_H

#include <cstdio>
#include <cstring>

class tree {
private:
    char* str;
    tree* left;
    tree* right;
public:
    friend tree* myLoad(long,FILE*);
    void setValue(char*);
    friend short isBigger(char* A,char* B);
    friend long putTree(tree*, FILE*);
    friend tree* getTree(long,FILE*);
    tree();
    explicit tree(char*);
    friend tree* appendValue(tree* root,char* value);
};


#endif //CURSEWORK_1_TREE_H
