
#include "ftree.h"
#include "tree.h"
#include <iostream>

short isBigger(char* A,char* B)
{
    int i=0;
    while (A[i]!='\0' && B[i]!='\0')
    {
        if (A[i]>B[i]) return 1;
        if (A[i]<B[i]) return 0;
        ++i;
    }
    return -1;
}

tree* appendValue(tree* root,char* value) {
    if (!root)
    {
        root = new tree(value);
        return root;
    }
    if (!(root->str))
    {
        unsigned long long sizeOfValue  = strlen(value)+1;
        root->str = new char[sizeOfValue];
        strcpy(root->str,value);
        return root;
    }
    if (isBigger(root->str,value)==0) root->right = appendValue(root->right,value);
    else root->left = appendValue(root->left,value);
    return root;
}

long putTree(tree* tTree, FILE *fileName) //������� ������ ���������� ����� ����������� ������� � �����
{
    if (!tTree) return FNULL;
    ftree nFTree; //������� ������� - ��������� ����������
    fseek(fileName, 0, SEEK_END); //�������� ������� - ������ �����
    long pos = ftell(fileName); //���������� ������� � �����

    nFTree.sz= strlen(tTree->str) + 1; //������ ���������� ����, ����������� ��� ������ ���
    fwrite((char*)&nFTree, TSZ, 1, fileName); //���������� �����

    fwrite(tTree->str, nFTree.sz, 1, fileName); //��������� ������, ��������������� �����
    nFTree.fp_left = putTree(tTree->left, fileName); //����������� ���������� ��������
    nFTree.fp_right = putTree(tTree->right, fileName);
    fseek(fileName, pos, SEEK_SET); //�������� �������
    // ����� ��������� ������������� ������� ������
    fwrite((char*)&nFTree, TSZ, 1, fileName);
    //����
    return pos;
}
tree* getTree(long pos, FILE *fileName){  // ���� - ����� ������� � �����
    if (pos == FNULL) return NULL;  // ��������� - ��������� �� ������� ��������� � ������

    tree *tTree = new tree;
    ftree nFTree;                                     // ������� ������� �� ����� -
    fseek(fileName, pos, SEEK_SET);           // � ��������� ����������
    fread((char*)&nFTree, sizeof(ftree), 1, fileName);
    tTree->str=new char[nFTree.sz]; //�������� ������ ��� ������ ���
    fread(tTree->str, nFTree.sz, 1, fileName); //������ ������ ���
    tTree->left = getTree(nFTree.fp_left,fileName);                          // ����������� �������� ��������
    tTree->right = getTree(nFTree.fp_right,fileName);        // � ���������� ����������
    return tTree;
}


tree *loadTree(const char *fileName) {
    FILE *file; long generalHead;
    if ((file = fopen(fileName, "rb")) == NULL) return NULL;
    fread((char*)&generalHead, sizeof(long), 1, file);
    return getTree(generalHead, file);
}

tree* myLoad(long pos, FILE *fileName)
{
    if (pos==FNULL) return NULL;
    tree* tTree = new tree;
    ftree nFTree;
    fseek(fileName,pos,SEEK_SET);
    fread((char*)&nFTree,TSZ,1,fileName);
    tTree->str=new char[nFTree.sz];
    fread(tTree->str,nFTree.sz,1,fileName);
    tTree->left = myLoad(nFTree.fp_left,fileName);
    tTree->right= myLoad(nFTree.fp_right,fileName);
    return tTree;
}


int main()
{
    tree* newTree = new tree("Hello");
    appendValue(newTree,"my dear friend!!!!");
    //appendValue(newTree,"C");
    FILE* file;
    if ((file = fopen("treeInFile.bin", "wb")) == NULL) std::cout<<"File doesn't exist"<<std::ends;
    putTree(newTree,file);
    fclose(file);

    tree* fromFile = new tree();
    if ((file = fopen("treeInFile.bin", "rb")) == NULL) std::cout<<"File doesn't exist"<<std::ends;
    fromFile = myLoad(0,file);

/*

    tree* fromFile = new tree();
    fromFile = loadTree("treeInFile.bin");
*/

    return 0;
}
