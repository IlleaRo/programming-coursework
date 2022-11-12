#pragma once

#include <fstream>
#include <cstring>

#define TSZ sizeof(Ftree)
#define FNULL (-1L)

template <class T>
class Tree;

class Ftree{
public:
    long fp_left;
    long fp_right;
    int sz;
    Ftree()
    {
        this->sz=0;
        this->fp_right = FNULL;
        this->fp_left = FNULL;
    };
};


template <typename T>
class Tree
{
    T value;
    Tree<T>* left;
    Tree<T>* right;
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
    long appendValueToFtree(T nValue,FILE* fileName) //Запись нового значения, новой вершины, в файл
    {
        long pos; //инициируем новую позицию в файле
        Ftree newNode; //инициируем новую вершину для переданного значения
        newNode.fp_right = newNode.fp_left = FNULL; //Новая вершина дерева - лист
        newNode.sz = sizeof(T); //Узнаем необходимое количество байт для записи объекта
        fseek(fileName,0L,SEEK_END); //Передвигаемся в конец файла
        pos = ftell(fileName); //Запоминаем адрес по которому размещается новая вершина
        fwrite((char*)&newNode,TSZ,1,fileName); //Записываем вершину
        fwrite((char*)&nValue,newNode.sz,1,fileName); //Записываем данные вершины
        return pos; //Возвращаем адрес новой вершины
    }
    void appendTree(long pos, T nValue, FILE* fileName)
    {
        Ftree nNode; T valueFromFtree;
        fseek(fileName,pos,SEEK_SET); //Переходим к началу очередного узла
        fread((char*)&nNode,sizeof(nNode),1,fileName); //Считываем очередную вершину
        fread((char*)&valueFromFtree,nNode.sz,1,fileName); //Считываем значение дерева
        if (nValue>valueFromFtree)
        {
            if (nNode.fp_right!=FNULL)
            {
                appendTree(nNode.fp_right,nValue,fileName);
                return;
            }
            else nNode.fp_right = appendValueToFtree(nValue,fileName);
        }
        else
        {
            if (nNode.fp_left!=FNULL)
            {
                appendTree(nNode.fp_left,nValue,fileName);
                return;
            }
            else nNode.fp_left = appendValueToFtree(nValue,fileName);
        }
        fseek(fileName,pos,SEEK_SET); //Обновить текущую вершину дерева
        fwrite((char*)&nNode,TSZ,1,fileName); //Перепечатываем указатели на ветви
    }

    friend long putTree(Tree<T>* tTree, FILE* fileName)
    {
        if (!tTree) return FNULL;
        Ftree nFTree; //Текущая вершина - локальная переменная
        fseek(fileName, 0, SEEK_END); //Записать вершину - занять место
        long pos = ftell(fileName); //Запоминаем позицию в файле

        nFTree.sz = sizeof(tTree->value); //Узнаем количество байт, необходимое для записи ЗПД
        fwrite((char*)&nFTree, TSZ, 1, fileName); //Записываем ветвь

        fwrite((char*)&(tTree->value), nFTree.sz, 1, fileName); //Сохраняем строку, соответствующую ветви
        nFTree.fp_left = putTree(tTree->left, fileName); //Рекурсивное сохранение потомков
        nFTree.fp_right = putTree(tTree->right, fileName);
        fseek(fileName, pos, SEEK_SET); //Обновить вершину
        fwrite((char*)&nFTree, TSZ, 1, fileName);
        return pos;
    }
    friend Tree<T>* getTree(long pos, FILE* fileName, Tree<T>* flyTree)
    {
        if (pos == FNULL) return NULL;
        auto* tTree = new Tree<T>;
        Ftree nFTree;
        fseek(fileName, pos, SEEK_SET);
        fread((char*)&nFTree, TSZ, 1, fileName);
        fread((char*)&(tTree->value), nFTree.sz, 1, fileName);
        tTree->left = getTree(nFTree.fp_left, fileName, flyTree);
        tTree->right = getTree(nFTree.fp_right, fileName, flyTree);
        return tTree;
    }
};