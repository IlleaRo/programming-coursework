//
// Created by Illea on 29.10.2022.
//

#ifndef CURSEWORK_1_BINTREE_H
#define CURSEWORK_1_BINTREE_H
#include <fstream>
#include <iostream>

template<typename T>
class binTree: private std::fstream {
public:
    explicit binTree<T>(T value);


    template<typename V>
    friend binTree<V>* addLeaf(binTree<V>* root,V value);

private:
    T value;
    binTree<T>* left;
    binTree<T>* right;
};


#endif //CURSEWORK_1_BINTREE_H
