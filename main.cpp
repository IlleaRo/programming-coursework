#include <iostream>
#include "binTree.h"
#include "binTree.cpp"

int main() {
    int a = 0;
    binTree<int>* newTree = new binTree<int>(a);
    binTree<int>* a1 = addLeaf(newTree,5);
    binTree<int>* a2 = addLeaf(newTree,-5);
    binTree<int>* a3 = addLeaf(newTree,543);
    return 0;
}
