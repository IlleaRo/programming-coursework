
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

long putTree(tree* tTree, FILE *fileName) //функция записи возвращает адрес размещенной вершины в файле
{
    if (!tTree) return FNULL;
    ftree nFTree; //Текущая вершина - локальная переменная
    fseek(fileName, 0, SEEK_END); //Записать вершину - занять место
    long pos = ftell(fileName); //Запоминаем позицию в файле

    nFTree.sz= strlen(tTree->str) + 1; //Узнаем количество байт, необходимое для записи ЗПД
    fwrite((char*)&nFTree, TSZ, 1, fileName); //Записываем ветвь

    fwrite(tTree->str, nFTree.sz, 1, fileName); //Сохраняем строку, соответствующую ветви
    nFTree.fp_left = putTree(tTree->left, fileName); //Рекурсивное сохранение потомков
    nFTree.fp_right = putTree(tTree->right, fileName);
    fseek(fileName, pos, SEEK_SET); //Обновить вершину
    // стоит проверить необходимость данного пункта
    fwrite((char*)&nFTree, TSZ, 1, fileName);
    //выше
    return pos;
}
tree* getTree(long pos, FILE *fileName){  // Вход - адрес вершины в файле
    if (pos == FNULL) return NULL;  // Результат - указатель на вершину поддерева в памяти

    tree *tTree = new tree;
    ftree nFTree;                                     // Текущая вершина из файла -
    fseek(fileName, pos, SEEK_SET);           // в локальной переменной
    fread((char*)&nFTree, sizeof(ftree), 1, fileName);
    tTree->str=new char[nFTree.sz]; //Выделяем память под строку ЗПД
    fread(tTree->str, nFTree.sz, 1, fileName); //Читаем строку ЗПД
    tTree->left = getTree(nFTree.fp_left,fileName);                          // Рекурсивная загрузка потомков
    tTree->right = getTree(nFTree.fp_right,fileName);        // и сохранение указателей
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
