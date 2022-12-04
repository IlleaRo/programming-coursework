#include "Root.h"
#include "Tree.h"
#include <iostream>

int testWithInt(char*);
int testWithClass(char*)
{
    return 0;
}


int main()
{
    std::cout<<"Please specify the name of the file tree\n---> "<<std::ends;
    char filename[10];
    std::cin>>filename;
    std::cout<<"Select the type of object in file tree "<<filename<<"\n1) int\n2) Products\n---> "<<std::ends;
    short decision;
    while (true)
    {
        std::cin>>decision;
        switch(decision)
        {
            case(1):
            {
                return testWithInt(filename);
            }
            case(2):
            {
                return testWithClass(filename);
            }
            default: std::cout<<"Please enter the correct number!";
        }
    }
}


int testWithInt(char* wf)
{
    Root<int> TreeInt(wf);
    short decision;
    while (true)
    {
        std::cout<<"What will we do?\n-1) Clean tree\n1) Print tree\n2) Add new object\n"
                   "3) Search object with name\n4) Delete object with name\n"
                   "5) Balancing tree\n6) EXIT\n---> "<<std::ends;
        std::cin>>decision;
        switch (decision) {
            case(-1):
            {
                TreeInt.clearFTree();
                break;
            }
            case(1):
            {
                Tree<int>* tTree = getTree(&TreeInt,tTree);
                if (tTree) std::cout<<*tTree;
                clear(tTree);
                break;
            }
            case(2):
            {
                int newObj;
                std::cout<<"Object---> "<<std::ends;
                std::cin>>newObj;
                TreeInt.addValue(newObj);
                break;
            }
            case(3):
            {
                int desiredObj;
                std::cout<<"Object---> "<<std::ends;
                std::cin>>desiredObj;
                std::cout<<"Node has this position in file: "<<TreeInt.search(desiredObj)<<std::endl;
                break;
            }
            case(4):
            {
                int desiredObj;
                std::cout<<"Object---> "<<std::ends;
                std::cin>>desiredObj;
                if (TreeInt.deleteVal(desiredObj)) std::cout<<"Object "<<desiredObj<<" has been deleted"<<std::endl;
                else std::cout<<"Incorrect name of object!"<<std::endl;
                break;
            }
            case(5):
            {
                TreeInt.balance();
                break;
            }
            case(6): return 0;
            default: std::cout<<"Please enter the correct number!";
        }
    }
}




/*
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
}*/
