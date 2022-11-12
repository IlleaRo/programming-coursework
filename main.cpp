#include "FileNode.h"
#include "Root.h"
#include "Tree.h"
#include <iostream>

int main()
{
    auto* newTree = new Tree<int>(19);
    appendValue(newTree, 32);
    appendValue(newTree, -35);

    auto* fileTree = new Root<int>("test.bin",sizeof(int));


    putTree(newTree, fileTree);
    Tree<int>* treeFromFIle1 = getTree(fileTree,treeFromFIle1);

    fileTree->addValue(43);
    fileTree->addValue(-235);

    Tree<int>* t2 = getTree(fileTree,t2);
    return 0;
}