//
// Created by Illea on 12.11.2022.
//

#ifndef CURSEWORK_1_ROOT_H
#define CURSEWORK_1_ROOT_H

#include <iostream>
#include "FileNode.h"
#include <list>
//#include "Tree.h"

template <typename T>
class Root
{
    char* fileName;
    int TSZ;
    //FileNode* root;

    long appendValueToFTree(T nValue, FILE* workFile) //Запись нового значения, новой вершины, в файл
    {
        long pos; //инициируем новую позицию в файле
        FileNode newNode; //инициируем новую вершину для переданного значения
        newNode.fp_right = newNode.fp_left = FNULL; //Новая вершина дерева - лист
        fseek(workFile,0L,SEEK_END); //Передвигаемся в конец файла
        pos = ftell(workFile); //Запоминаем адрес по которому размещается новая вершина
        fwrite((char*)&newNode,SOFFN,1,workFile); //Записываем вершину
        fwrite((char*)&nValue,TSZ,1,workFile); //Записываем данные вершины
        return pos; //Возвращаем адрес новой вершины
    }
    long appendTree(long pos, T& nValue, FILE* fileName)
    {
        FileNode nNode; T valueFromFTree;
        fseek(fileName,pos,SEEK_SET); //Переходим к началу очередного узла
        fread((char*)&nNode,SOFFN,1,fileName); //Считываем очередную вершину
        fread((char*)&valueFromFTree, TSZ, 1, fileName); //Считываем значение дерева
        if (nValue > valueFromFTree)
        {
            if (nNode.fp_right!=FNULL) return appendTree(nNode.fp_right,nValue,fileName);

            nNode.fp_right = appendValueToFTree(nValue, fileName);
            fseek(fileName,pos,SEEK_SET); //Обновить текущую вершину дерева
            fwrite((char*)&nNode,SOFFN,1,fileName); //Перепечатываем указатели на ветви
            return nNode.fp_right;
        }
        if (nNode.fp_left!=FNULL) return appendTree(nNode.fp_left,nValue,fileName);

        nNode.fp_left = appendValueToFTree(nValue, fileName);
        fseek(fileName,pos,SEEK_SET); //Обновить текущую вершину дерева
        fwrite((char*)&nNode,SOFFN,1,fileName); //Перепечатываем указатели на ветви
        return nNode.fp_left;
    }

    long searchInNode(long pos,T& desValue,FILE* readFile)
    {
        if (pos == FNULL) return FNULL;
        fseek(readFile, pos, SEEK_SET);

        FileNode nFTree; T curVal;
        fread((char*)&nFTree, SOFFN, 1, readFile);
        fread((char*)&curVal, TSZ, 1, readFile);
        if (desValue==curVal) return pos;
        if (desValue<curVal) return searchInNode(nFTree.fp_left, desValue, readFile);
        return searchInNode(nFTree.fp_right, desValue, readFile);
    }
    void leftestFromRightIsLeaf(long pos, FILE* workFIle)
    {
        FileNode Node1,Node2; T obj;
        fseek(workFIle,pos,SEEK_SET);
        fread((char*)&Node1,SOFFN,1,workFIle);
        fread((char*)&obj,TSZ,1,workFIle);
        fseek(workFIle,Node1.fp_right,SEEK_SET);
        long t_pos=ftell(workFIle);
        fread((char*)&Node2,SOFFN,1,workFIle);
        if (Node2.fp_left==FNULL)
        {
            fread((char*)&obj,TSZ,1,workFIle);
            Node1.fp_right=Node2.fp_right;
            fseek(workFIle,pos,SEEK_SET);
            fwrite((char*)&Node1,SOFFN,1,workFIle);
            fwrite((char*)&obj,TSZ,1,workFIle);
            return;
        }
        //fseek(workFIle,Node2.fp_left,SEEK_SET);

        int sizeOfObj = SOFFN;
        while (true)
        {
            fseek(workFIle,Node2.fp_left,SEEK_SET);
            fread((char*)&Node1,SOFFN,1,workFIle);
            if (Node1.fp_left==FNULL) break;
            Node2=Node1;
            fseek(workFIle,-sizeOfObj,SEEK_CUR);
            t_pos= ftell(workFIle);
            fseek(workFIle,sizeOfObj,SEEK_CUR);
        }
        if (Node1.fp_right==FNULL)
        {
            Node2.fp_left=FNULL;
            fread((char*)&obj,TSZ,1,workFIle);
            fseek(workFIle,t_pos,SEEK_SET);
            fwrite((char*)&Node2,SOFFN,1,workFIle);
            fseek(workFIle,pos+sizeOfObj,SEEK_SET);
            fwrite((char*)&obj,TSZ,1,workFIle);
            return;
        }
        Node2.fp_left=Node1.fp_right;
        fread((char*)&obj,TSZ,1,workFIle);
        fseek(workFIle,t_pos,SEEK_SET);
        fwrite((char*)&Node2,SOFFN,1,workFIle);
        fseek(workFIle,pos+sizeOfObj,SEEK_SET);
        fwrite((char*)&obj,TSZ,1,workFIle);

    }

    bool reTree(long pos, T& delValue, FILE* readFile) //Функция нахождения узла ДО удаляемого
    {
        fseek(readFile, pos, SEEK_SET); //Чтение очередной вершины
        FileNode fTree; T curVal;
        fread((char*)&fTree, SOFFN, 1, readFile);
        fread((char*)&curVal, TSZ, 1, readFile);

        if (delValue==curVal && pos==0)
        {
            if (fTree.fp_right==FNULL && fTree.fp_left==FNULL)
                return true;
            if (fTree.fp_right==FNULL && fTree.fp_left!=FNULL)
            {
                FileNode newRoot; T rootValue;
                fseek(readFile, fTree.fp_left, SEEK_SET);
                fread((char *) &newRoot, SOFFN, 1, readFile);
                fread((char *) &rootValue, TSZ, 1, readFile);
                fseek(readFile, 0, SEEK_SET);
                fwrite((char *) &newRoot, SOFFN, 1, readFile);
                fwrite((char *) &rootValue, TSZ, 1, readFile);
                return false;
            }
            if (fTree.fp_right!=FNULL && fTree.fp_left==FNULL)
            {
                FileNode newRoot; T rootValue;
                fseek(readFile, fTree.fp_right, SEEK_SET);
                fread((char *) &newRoot, SOFFN, 1, readFile);
                fread((char *) &rootValue, TSZ, 1, readFile);
                fseek(readFile, 0, SEEK_SET);
                fwrite((char *) &newRoot, SOFFN, 1, readFile);
                fwrite((char *) &rootValue, TSZ, 1, readFile);
                return false;
            }
                leftestFromRightIsLeaf(0, readFile);
                /*FileNode newRoot; T rootValue;
                fseek(readFile, fTree.fp_right, SEEK_SET);
                fread((char *) &newRoot, SOFFN, 1, readFile);
                fread((char *) &rootValue, TSZ, 1, readFile);
                if (newRoot.fp_left==FNULL)
                {
                    newRoot.fp_left=fTree.fp_left;
                    fseek(readFile, 0, SEEK_SET);
                    fwrite((char *) &newRoot, SOFFN, 1, readFile);
                    fwrite((char *) &rootValue, TSZ, 1, readFile);
                    return false;
                }
                fseek(readFile, newRoot.fp_left, SEEK_SET);
                FileNode leftestFromRight;
                fread((char *) &leftestFromRight, SOFFN, 1, readFile);
                bool completed = false;
                while (!completed) {
                    if (leftestFromRight.fp_left == FNULL) {
                        leftestFromRight.fp_left = fTree.fp_left;
                        fseek(readFile, -SOFFN, SEEK_CUR);
                        fwrite((char *) &leftestFromRight, SOFFN, 1, readFile);
                        completed = true;
                    } else {
                        fseek(readFile, leftestFromRight.fp_left, SEEK_SET);
                        fread((char *) &leftestFromRight, SOFFN, 1, readFile);
                    }
                }
                fseek(readFile, 0, SEEK_SET);
                fwrite((char *) &newRoot, SOFFN, 1, readFile);
                fwrite((char *) &rootValue, TSZ, 1, readFile);*/
                return false;
        }

        if (delValue<curVal) //Если удаляемое значение меньше текущего, то идем влево
        {
            if (fTree.fp_left==FNULL) return false;
            T lVal;
            fseek(readFile, fTree.fp_left, SEEK_SET);
            fseek(readFile, SOFFN, SEEK_CUR);
            fread((char*)&lVal, TSZ, 1, readFile);
            //if (delValue>lVal) return false;
            if (delValue!=lVal) return reTree(fTree.fp_left, delValue, readFile);

            fseek(readFile,fTree.fp_left,SEEK_SET);

            FileNode lTree;
            fread((char*)&lTree,SOFFN,1,readFile);
            if (lTree.fp_left==FNULL && lTree.fp_right==FNULL) //Удаление листа
            {
                fTree.fp_left=FNULL;
                fseek(readFile, pos, SEEK_SET);
                fwrite((char*)&fTree,SOFFN,1,readFile);
                return false;
            }
            if (lTree.fp_left==FNULL && lTree.fp_right!=FNULL) //Не лист, но одна ветвь
            {
                fTree.fp_left=lTree.fp_right;
                fseek(readFile, pos, SEEK_SET);
                fwrite((char*)&fTree,SOFFN,1,readFile);
                return false;
            }
            if (lTree.fp_left!=FNULL && lTree.fp_right==FNULL) //Не лист, но одна ветвь
            {
                fTree.fp_left=lTree.fp_left;
                fseek(readFile, pos, SEEK_SET);
                fwrite((char*)&fTree,SOFFN,1,readFile);
                return false;
            }
            leftestFromRightIsLeaf(fTree.fp_left, readFile);
        }
        else //Иначе - вправо
        {
            if (fTree.fp_right==FNULL) return false;
            T lVal;
            fseek(readFile, fTree.fp_right, SEEK_SET);
            fseek(readFile, SOFFN, SEEK_CUR);
            fread((char*)&lVal, TSZ, 1, readFile);
            //if (delValue<lVal) return false;
            if (delValue!=lVal) return reTree(fTree.fp_right, delValue, readFile);

            fseek(readFile,fTree.fp_right,SEEK_SET);

            FileNode lTree;
            fread((char*)&lTree,SOFFN,1,readFile);
            if (lTree.fp_left==FNULL && lTree.fp_right==FNULL) //Удаление листа
            {
                fTree.fp_right=FNULL;
                fseek(readFile, pos, SEEK_SET);
                fwrite((char*)&fTree,SOFFN,1,readFile);
                return false;
            }
            if (lTree.fp_left==FNULL && lTree.fp_right!=FNULL) //Не лист, но одна ветвь
            {
                fTree.fp_right=lTree.fp_right;
                fseek(readFile, pos, SEEK_SET);
                fwrite((char*)&fTree,SOFFN,1,readFile);
                return false;
            }
            if (lTree.fp_left!=FNULL && lTree.fp_right==FNULL) //Не лист, но одна ветвь
            {
                fTree.fp_right=lTree.fp_left;
                fseek(readFile, pos, SEEK_SET);
                fwrite((char*)&fTree,SOFFN,1,readFile);
                return false;
            }
            leftestFromRightIsLeaf(fTree.fp_right, readFile);
        }
        return false;
    }
    void getValue(std::list<T>* List, FILE* workFile, long pos) //Функция обхода дерева и поиска суммы
    {
        fseek(workFile,pos,SEEK_SET);
        FileNode fNode; T obj;
        fread((char*)&fNode,SOFFN,1,workFile);
        fread((char*)&obj,TSZ,1,workFile);
        if (fNode.fp_left!=FNULL) getValue(List,workFile,fNode.fp_left);
        List->push_back(obj);
        if (fNode.fp_right!=FNULL) getValue(List,workFile,fNode.fp_right);
    }

    void toBalance(std::list<T>* List)
    {
        int sizeL = List->size();
        if (sizeL==0) return;
        if (sizeL==1)
        {
            this->addValue(List->front());
            return;
        }
       /* if (sizeL==2)
        {
            this->addValue(List->front());
            this->addValue(List->back());
            return;
        }*/

        int median;
        if (sizeL % 2!=0) median = sizeL / 2;
        else median = sizeL / 2-1;
        typename std::list<T>::iterator iter = List->begin();
        std::advance(iter,median);
        //while(median > **iter) ++iter;
        this->addValue(*iter);
        //Что тут делать?
        //List->erase(iter);

        typename std::list<T>::iterator iterLeft = List->begin();
        typename std::list<T>::iterator iterRight = --(List->end());
        std::list<T>* listLeft = new std::list<T>;
        std::list<T>* listRight = new std::list<T>;
        bool leftDone = false, rightDone = false;
        while (true)
        {
            if (iterLeft!=iter)
            {
                listLeft->push_back(*iterLeft);
                ++iterLeft;
            } else leftDone = true;
            if (iterRight!=iter)
            {
                listRight->push_front(*iterRight);
                --iterRight;
            } else rightDone = true;
            if (leftDone && rightDone) break;
        }
        toBalance(listLeft);
        delete listLeft;
        toBalance(listRight);
        delete listRight;
    }

public:

    explicit Root(char* file)
    {
//        FILE* workFile;
//        auto* nFTree = new FileNode;
//        if ((workFile = fopen(file,"rb")) !=NULL) fread((char*)nFTree, SOFFN, 1, workFile);
//        this->root = nFTree;
//        fclose(workFile);
        int szName = strlen(file);
        fileName = new char[szName+1];
        strcpy(this->fileName,file);
        strcpy(&this->fileName[szName],".bin\0");
        FILE* workFile;
        if ((workFile = fopen(this->fileName,"rb"))==nullptr)
            std::cout<<"New tree has been created!"<<std::endl;
        else std::cout<<"The file is already exists"<<std::endl;
        fclose(workFile);
        TSZ=sizeof(T);
    } //инициализация дерева
    long addValue(T& nValue)
    {
        FILE* workFile; long returned = 0;
        if ((workFile = fopen(fileName,"r+b")) !=NULL)
        {
            returned = this->appendTree(0,nValue,workFile);
            fclose(workFile);
            return returned;
        }
        fclose(workFile);
        workFile= fopen(fileName,"wb");
        FileNode newRoot;
        fwrite((char*)& newRoot,SOFFN,1,workFile);
        fwrite((char*)& nValue,TSZ,1,workFile);
        fclose(workFile);
        return returned;
    } //Добавление значения в дерево
    char* getFileName() { return fileName; } //Получение имени файла, в котором хранится дерево
    int getTSZ() { return TSZ; }; //Получение размера объекта, хранимого в дереве в байтах
    ~Root()
    {
        delete[] this->fileName;
        //delete this->root;
    } //Деструктор памяти, выделенную под динамическую переменную

    void clearFTree() //Очистка дерева - удаление файла
    {
        remove(this->fileName);
    }

    long search(T& desiredValue) //Возвращает позицию узла дерева в файле или FNULL
    {
        FILE* workFile;
        if ((workFile = fopen(fileName,"rb"))==nullptr) return FNULL;
        long returned = searchInNode(0,desiredValue,workFile);
        fclose(workFile);
        return returned;
    }
    bool deleteVal(T& valToDel)
    {
        FILE* readFile;
        if ((readFile = fopen(fileName, "r+b")) == nullptr) return false;
        long pos = search(valToDel);
        if (pos==FNULL) return false;
        bool isNeedToDel = reTree(0, valToDel, readFile);
        fclose(readFile);
        if (isNeedToDel) remove(this->fileName);
        return true;
    }

    void balance()
    {
        auto* List = new std::list<T>;
        FILE* workFile;
        if ((workFile = fopen(fileName, "rb")) == nullptr) return;
        getValue(List,workFile,0);
        fclose(workFile);
        remove(fileName);
        List->sort();
        toBalance(List);
        delete (List);
    }
};

#endif //CURSEWORK_1_ROOT_H
