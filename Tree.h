//
// Created by Illea on 12.11.2022.
//

#ifndef CURSEWORK_1_TREE_H
#define CURSEWORK_1_TREE_H

#include "FileNode.h"
#include "Root.h"

template <typename T>
class Tree
{
    T value;
    Tree<T>* left;
    Tree<T>* right;

    friend Tree<T>* getNode(long pos, FILE* fileName, int* sizeOfObj, Tree<T>* returnedTree)
    {
        if (pos == FNULL) return NULL;
        auto* tTree = new Tree<T>;
        FileNode<T> nFTree;
        fseek(fileName, pos, SEEK_SET);
        fread((char*)&nFTree, sizeof(nFTree), 1, fileName);
        fread((char*)&(tTree->value), *sizeOfObj, 1, fileName);
        tTree->left = getNode(nFTree.fp_left, fileName,sizeOfObj,returnedTree);
        tTree->right = getNode(nFTree.fp_right, fileName,sizeOfObj,returnedTree);
        return tTree;
    }

    friend long putNode(Tree<T>* tTree, FILE* fileName,const int* sizeOfObj)
    {
        if (!tTree) return FNULL;
        FileNode<T> nFTree; //������� ������� - ��������� ����������
        fseek(fileName, 0, SEEK_END); //�������� ������� - ������ �����
        long pos = ftell(fileName); //���������� ������� � �����

        //nFTree.sz = sizeof(tTree->value); //������ ���������� ����, ����������� ��� ������ ���
        fwrite((char*)&nFTree, sizeof(nFTree), 1, fileName); //���������� �����

        fwrite((char*)&(tTree->value), *sizeOfObj, 1, fileName); //��������� ������, ��������������� �����
        nFTree.fp_left = putNode(tTree->left, fileName,sizeOfObj); //����������� ���������� ��������
        nFTree.fp_right = putNode(tTree->right, fileName,sizeOfObj);

        fseek(fileName, pos, SEEK_SET); //�������� �������
        fwrite((char*)&nFTree, sizeof(nFTree), 1, fileName);
        return pos;
    }

public:
    Tree()
    {
        this->value = 0;
        this->right = nullptr;
        this->left = nullptr;
    }
    explicit Tree(T value)
    {
        this->value = value;
        this->right = nullptr;
        this->left = nullptr;
    }
    friend Tree<T>* appendValue(Tree<T>* root, T value)
    {
        if (!root)
        {
            root = new Tree<T>(value);
            return root;
        }
        if (root->value < value) root->right = appendValue(root->right, value);
        else root->left = appendValue(root->left, value);
        return root;
    }

    friend long putTree(Tree<T>* tTree, Root<T>* fileTree)
    {
        FILE* fileName;
        if ((fileName = fopen(fileTree->getFileName(),"wb"))==NULL) return FNULL;
        int tInt = fileTree->getTSZ();
        long rootPos = putNode(tTree,fileName,&tInt);
        fclose(fileName);
        return rootPos;

    }
    friend Tree<T>* getTree(Root<T>* root,Tree<T>* yourTree)
    {
        FILE* fileName;
        if ((fileName = fopen(root->getFileName(),"rb"))==NULL) return nullptr;
        int tInt = root->getTSZ();
        Tree<T>* returnedTree = getNode(0, fileName, &tInt, yourTree);
        fclose(fileName);
        return returnedTree;
    }

};


#endif //CURSEWORK_1_TREE_H
