//
// Created by Illea on 12.11.2022.
//

#ifndef CURSEWORK_1_ROOT_H
#define CURSEWORK_1_ROOT_H

#include "FileNode.h"

template <typename T>
class Root
{
    char* fileName;
    int TSZ;
    FileNode<T>* root;
    long appendValueToFtree(T nValue,FILE* workFile) //Запись нового значения, новой вершины, в файл
    {
        long pos; //инициируем новую позицию в файле
        FileNode<T> newNode; //инициируем новую вершину для переданного значения
        newNode.fp_right = newNode.fp_left = FNULL; //Новая вершина дерева - лист
        fseek(workFile,0L,SEEK_END); //Передвигаемся в конец файла
        pos = ftell(workFile); //Запоминаем адрес по которому размещается новая вершина
        fwrite((char*)&newNode,sizeof(newNode),1,workFile); //Записываем вершину
        fwrite((char*)&nValue,TSZ,1,workFile); //Записываем данные вершины
        return pos; //Возвращаем адрес новой вершины
    }
    long appendTree(long pos, T nValue, FILE* fileName)
    {
        FileNode<T> nNode; T valueFromFtree;
        fseek(fileName,pos,SEEK_SET); //Переходим к началу очередного узла
        fread((char*)&nNode,sizeof(nNode),1,fileName); //Считываем очередную вершину
        fread((char*)&valueFromFtree,TSZ,1,fileName); //Считываем значение дерева
        if (nValue>valueFromFtree)
        {
            if (nNode.fp_right!=FNULL) return appendTree(nNode.fp_right,nValue,fileName);

            nNode.fp_right = appendValueToFtree(nValue,fileName);
            fseek(fileName,pos,SEEK_SET); //Обновить текущую вершину дерева
            fwrite((char*)&nNode,sizeof(nNode),1,fileName); //Перепечатываем указатели на ветви
            return nNode.fp_right;
        }
        if (nNode.fp_left!=FNULL) return appendTree(nNode.fp_left,nValue,fileName);

        nNode.fp_left = appendValueToFtree(nValue,fileName);
        fseek(fileName,pos,SEEK_SET); //Обновить текущую вершину дерева
        fwrite((char*)&nNode,sizeof(nNode),1,fileName); //Перепечатываем указатели на ветви
        return nNode.fp_left;
    }
public:
    Root(char* file, int szOfT)
    {
        FILE* workFile = fopen(file,"wb");
        ftell(workFile);
        fclose(workFile);
        this->fileName = new char[sizeof(file)+1];
        strcpy(this->fileName,file);
        this->TSZ=szOfT;
        this->root = new FileNode<T>;
    }
    long addValue(T nValue)
    {
        FILE* workFile;
        workFile = fopen(fileName, "r+b");
        long returned = this->appendTree(0,nValue,workFile);
        fclose(workFile);
        return returned;
    }
    char* getFileName() { return fileName; }
    int getTSZ() { return TSZ; };
};

#endif //CURSEWORK_1_ROOT_H
