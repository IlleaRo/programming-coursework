//
// Created by Illea on 29.10.2022.
//

#include <memory>
#include <vector>
#include "binTree.h"
#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <tuple>
#include <stdexcept>
#include <memory>


/*template<typename T>
int binTree<T>::writeTree()
{
    if (!(this->is_open())) throw "You need open file!";

    this->write((char*)this,sizeof(binTree<T>));

    return 0;
}*/


template<typename T>
binTree<T>::binTree(T value)
    {
        this->value = value;
        this->right = nullptr;
        this->left = nullptr;
    }


template<typename T>
binTree<T>* addLeaf(binTree<T>* root,T value)
{
    if (!root)
    {
        root = new binTree<T>(value);
        return root;
    }
    if (root->value >= value)
        root->left = addLeaf(root->left,value);
    else
        root->right = addLeaf(root->right,value);
    return root;
}


