#include "Root.h"
#include "Tree.h"
#include <iostream>
int main()
{


   auto* newTree = new Tree<int>(19);
    appendValue(newTree, 50);

    appendValue(newTree, 55);
    appendValue(newTree, 52);
    appendValue(newTree, 51);
    appendValue(newTree, 54);
    appendValue(newTree, 40);
    appendValue(newTree, 30);
    appendValue(newTree, 45);
    appendValue(newTree, 67);
    appendValue(newTree, -35);
    auto* fileTree = new Root<int>("test.bin");
    putTree(newTree, fileTree);

    Tree<int>* treeFromFIle1 = getTree(fileTree,treeFromFIle1);
    std::cout<<*treeFromFIle1<<std::endl;
    fileTree->balance();

    Tree<int>* treeFromFIle2 = getTree(fileTree,treeFromFIle2);
    std::cout<<*treeFromFIle2;
    return 0;
}