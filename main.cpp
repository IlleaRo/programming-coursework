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
    std::cout<<fileTree->deleteVal(50)<<std::endl;
    Tree<int>* treeFromFIle2 = getTree(fileTree,treeFromFIle2);

/*
    fileTree->addValue(43);
    fileTree->addValue(-235);

    Tree<int>* t2 = getTree(fileTree,t2);
    delete fileTree;

    auto* fileTree2 = new Root<int>("test21.bin");

    Tree<int>* t3 = getTree(fileTree2,t3);
    //fileTree2->clearFTree();
    fileTree2->addValue(23);
    Tree<int>* t4 = getTree(fileTree2,t4);
    fileTree2->addValue(2324453);
    Tree<int>* t5 = getTree(fileTree2,t5);*/


    return 0;
}