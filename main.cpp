#include "trees.h"
#include <iostream>

int main()
{
    auto* newTree = new Tree<int>(19);
    appendValue(newTree, 32);
    appendValue(newTree, 35);
    appendValue(newTree, 312);
    appendValue(newTree, -23);

    FILE* file;

    if ((file = fopen("treeInFile.bin", "wb")) == NULL) std::cout << "File doesn't exist" << std::ends;

    putTree(newTree, file);
    fclose(file);

    if ((file = fopen("treeInFile.bin", "r+b")) == NULL) std::cout << "File doesn't exist" << std::ends;
    newTree->appendTree(0,-2345,file);
    fclose(file);



    auto* treeFF = new Tree<int>();

    if ((file = fopen("treeInFile.bin", "rb")) == NULL) std::cout << "File doesn't exist" << std::ends;

    treeFF = getTree(0, file,treeFF);

    fclose(file);
    return 0;
}