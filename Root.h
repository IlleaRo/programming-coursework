#ifndef CURSEWORK_1_ROOT_H
#define CURSEWORK_1_ROOT_H

#include "FileNode.h"

#include <iostream>
#include <cstring>
#include <list>

template <typename T>
class Root
{
    char* fileName; //Название файла, содержащего узлы дерева
    int TSZ; //Размер объекта в байтах, содержащегося в узле
    int counter; //Количество объектов
    long appendValueToFTree(T nValue, FILE* workFile) //Запись нового значения - новой вершины - в файл
    {
        ++counter;
        long pos; //инициируем новую позицию в файле
        FileNode newNode; //инициируем новую вершину для переданного значения
        newNode.fp_right = newNode.fp_left = FNULL; //Новая вершина дерева - лист
        fseek(workFile,0L,SEEK_END); //Передвигаемся в конец файла
        pos = ftell(workFile); //Запоминаем адрес по которому размещается новая вершина
        fwrite((char*)&newNode,SOFFN,1,workFile); //Записываем вершину
        fwrite((char*)&nValue,TSZ,1,workFile); //Записываем данные вершины
        return pos; //Возвращаем адрес новой вершины
    }
    long appendTree(long pos, T& nValue, FILE* fileName) //Добавление узла в файл с новым значением
    {
        FileNode nNode; T valueFromFTree;
        fseek(fileName,pos,SEEK_SET); //Переходим к началу очередного узла
        fread((char*)&nNode,SOFFN,1,fileName); //Считываем очередную вершину
        fread((char*)&valueFromFTree, TSZ, 1, fileName); //Считываем значение дерева
        if (nValue == valueFromFTree) return pos;
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

    long searchInNode(long pos,T& desValue,FILE* readFile) //Рекурсивный поиск элемента в дереве
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
    void replaceDelNode(long pos, FILE* workFIle) //Замещение удаляемого узла
    {
        FileNode Node1,Node2; T obj;
        fseek(workFIle,pos,SEEK_SET);
        fread((char*)&Node1,SOFFN,1,workFIle);
        fread((char*)&obj,TSZ,1,workFIle);

        fseek(workFIle,Node1.fp_right,SEEK_SET); //Идем вправо
        long t_pos=ftell(workFIle); //Запоминаем позицию правого
        fread((char*)&Node2,SOFFN,1,workFIle); //Считываем правое поддерево
        if (Node2.fp_left==FNULL)
        {
            fread((char*)&obj,TSZ,1,workFIle);
            Node1.fp_right=Node2.fp_right;
            fseek(workFIle,pos,SEEK_SET);
            fwrite((char*)&Node1,SOFFN,1,workFIle);
            fwrite((char*)&obj,TSZ,1,workFIle);
            return;
        }
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

    short reTree(long pos, T& delValue, FILE* workFile, char* fileName) //Функция нахождения узла ДО удаляемого
    {
        fseek(workFile, pos, SEEK_SET); //Чтение очередной вершины
        FileNode fTree; T curVal;
        fread((char*)&fTree, SOFFN, 1, workFile);
        fread((char*)&curVal, TSZ, 1, workFile);

        if (delValue==curVal && pos==0)
        {
            if (fTree.fp_right==FNULL && fTree.fp_left==FNULL) return 2;
            if (fTree.fp_right==FNULL && fTree.fp_left!=FNULL)
            {
                FileNode newRoot; T rootValue;
                fseek(workFile, fTree.fp_left, SEEK_SET);
                fread((char *) &newRoot, SOFFN, 1, workFile);
                fread((char *) &rootValue, TSZ, 1, workFile);
                fseek(workFile, 0, SEEK_SET);
                fwrite((char *) &newRoot, SOFFN, 1, workFile);
                fwrite((char *) &rootValue, TSZ, 1, workFile);
                return 1;
            }
            if (fTree.fp_right!=FNULL && fTree.fp_left==FNULL)
            {
                FileNode newRoot; T rootValue;
                fseek(workFile, fTree.fp_right, SEEK_SET);
                fread((char *) &newRoot, SOFFN, 1, workFile);
                fread((char *) &rootValue, TSZ, 1, workFile);
                fseek(workFile, 0, SEEK_SET);
                fwrite((char *) &newRoot, SOFFN, 1, workFile);
                fwrite((char *) &rootValue, TSZ, 1, workFile);
                return 1;
            }
            replaceDelNode(0, workFile);
            return 1;
        }

        if (delValue<curVal) //Если удаляемое значение меньше текущего, то идем влево
        {
            if (fTree.fp_left==FNULL) return 0;
            T lVal;
            fseek(workFile, fTree.fp_left, SEEK_SET);
            fseek(workFile, SOFFN, SEEK_CUR);
            fread((char*)&lVal, TSZ, 1, workFile);
            if (delValue!=lVal) return reTree(fTree.fp_left, delValue, workFile,fileName);

            fseek(workFile, fTree.fp_left, SEEK_SET);

            FileNode lTree;
            fread((char*)&lTree, SOFFN, 1, workFile);
            if (lTree.fp_left==FNULL && lTree.fp_right==FNULL) //Удаление листа
            {
                fTree.fp_left=FNULL;
                fseek(workFile, pos, SEEK_SET);
                fwrite((char*)&fTree, SOFFN, 1, workFile);
                return 1;
            }
            if (lTree.fp_left==FNULL && lTree.fp_right!=FNULL) //Не лист, но одна ветвь
            {
                fTree.fp_left=lTree.fp_right;
                fseek(workFile, pos, SEEK_SET);
                fwrite((char*)&fTree, SOFFN, 1, workFile);
                return 1;
            }
            if (lTree.fp_left!=FNULL && lTree.fp_right==FNULL) //Не лист, но одна ветвь
            {
                fTree.fp_left=lTree.fp_left;
                fseek(workFile, pos, SEEK_SET);
                fwrite((char*)&fTree, SOFFN, 1, workFile);
                return 1;
            }
            replaceDelNode(fTree.fp_left, workFile);
            return 1;
        }
        else //Иначе - вправо
        {
            if (fTree.fp_right==FNULL) return 0;
            T lVal;
            fseek(workFile, fTree.fp_right, SEEK_SET);
            fseek(workFile, SOFFN, SEEK_CUR);
            fread((char*)&lVal, TSZ, 1, workFile);
            if (delValue!=lVal) return reTree(fTree.fp_right, delValue, workFile,fileName);
            fseek(workFile, fTree.fp_right, SEEK_SET);
            FileNode lTree;
            fread((char*)&lTree, SOFFN, 1, workFile);
            if (lTree.fp_left==FNULL && lTree.fp_right==FNULL) //Удаление листа
            {
                fTree.fp_right=FNULL;
                fseek(workFile, pos, SEEK_SET);
                fwrite((char*)&fTree, SOFFN, 1, workFile);
                return 1;
            }
            if (lTree.fp_left==FNULL && lTree.fp_right!=FNULL) //Не лист, но одна ветвь
            {
                fTree.fp_right=lTree.fp_right;
                fseek(workFile, pos, SEEK_SET);
                fwrite((char*)&fTree, SOFFN, 1, workFile);
                return 1;
            }
            if (lTree.fp_left!=FNULL && lTree.fp_right==FNULL) //Не лист, но одна ветвь
            {
                fTree.fp_right=lTree.fp_left;
                fseek(workFile, pos, SEEK_SET);
                fwrite((char*)&fTree, SOFFN, 1, workFile);
                return 1;
            }
            replaceDelNode(fTree.fp_right, workFile);
            return 1;
        }
    }
    void getValue(std::list<T>* List, FILE* workFile, long pos) //Функция обхода дерева и поиска суммы (утилита балансировки)
    {
        fseek(workFile,pos,SEEK_SET);
        FileNode fNode; T obj;
        fread((char*)&fNode,SOFFN,1,workFile);
        fread((char*)&obj,TSZ,1,workFile);
        if (fNode.fp_left!=FNULL) getValue(List,workFile,fNode.fp_left);
        List->push_back(obj);
        if (fNode.fp_right!=FNULL) getValue(List,workFile,fNode.fp_right);
    }

    void doBalance(std::list<T>* List) //Утилита балансировки
    {
        int sizeL = List->size();
        if (sizeL==0) return;
        if (sizeL==1)
        {
            this->addValue(List->front());
            return;
        }
        int median;
        if (sizeL % 2!=0) median = sizeL / 2;
        else median = sizeL / 2-1;
        typename std::list<T>::iterator iter = List->begin();
        std::advance(iter,median);
        this->addValue(*iter);
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
        doBalance(listLeft);
        delete listLeft;
        doBalance(listRight);
        delete listRight;
    }
    void printBT(std::ostream& os,const std::string& prefix, long pos, bool isRight, FILE* workFile, int& sizeO) //Утилита перегрузки вывода
    {
        FileNode node; T Obj;
        fseek(workFile,pos,SEEK_SET);
        fread((char*)&node,SOFFN,1,workFile);
        fread((char*)&Obj,sizeO,1,workFile);
        os << prefix;
        os << (isRight ? "R---" : "L---" );
        os << Obj << std::endl; //Вывод значения узла
        if (node.fp_right!=FNULL) printBT(os, prefix + (isRight ? "|   " : "    "), node.fp_right, true,workFile,sizeO); //Выводим левое поддерево
        if (node.fp_left!=FNULL) printBT(os, prefix + (isRight ? "|   " : "    "), node.fp_left, false, workFile,sizeO); //Выводим правое поддерево
    }
    int countObj(long pos,FILE* readFile)
    {
        if (pos==FNULL) return 0;
        FileNode node;
        fseek(readFile,pos,SEEK_SET);
        fread((char*)&node,SOFFN,1,readFile);
        return 1 + countObj(node.fp_left,readFile) + countObj(node.fp_right,readFile);
    }
public:

    explicit Root(char* file)
    {
        int szName = strlen(file);
        fileName = new char[szName+1];
        strcpy(this->fileName,file);
        strcpy(&this->fileName[szName],".bin\0");
        FILE* workFile;
        TSZ=sizeof(T);
        if ((workFile = fopen(this->fileName,"rb"))==nullptr)
        {
            std::cout<<"New tree has been created!"<<std::endl;
            counter=0;
            return;
        }
        counter = countObj(0,workFile);
        std::cout<<"The file is already exists"<<std::endl;
        fclose(workFile);
    } // Конструктор дерева
    long addValue(T& nValue)
    {
        FILE* workFile; long returned = 0;
        if ((workFile = fopen(fileName,"r+b")) != nullptr) //Проверка существования файла - дерева
        {
            returned = this->appendTree(0,nValue,workFile);
            fclose(workFile);
            return returned;
        }
        counter=1;
        //fclose(workFile);
        workFile = fopen(fileName,"wb");
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
        delete[] this->fileName; //памяти, выделенную под динамическую переменную
    } //Деструктор класса

    void clearFTree() //Очистка дерева - удаление файла
    {
        counter = 0;
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
        FILE* workFile;
        if ((workFile = fopen(fileName, "r+b")) == nullptr) return false;
        short res =  reTree(0, valToDel, workFile, this->fileName);
        fclose(workFile);
        //delete workFile;
        int a;
        if (res==2) std::remove(this->fileName);
        if (res!=0) --counter;
        return res;
    } //Метод удаления элемента
    int getCount() {return counter;}; //Получение количества объектов
    void balance()
    {
        auto* List = new std::list<T>;
        FILE* workFile;
        if ((workFile = fopen(fileName, "rb")) == nullptr) return;
        getValue(List,workFile,0);
        fclose(workFile);
        remove(fileName);
        List->sort();
        doBalance(List);
        delete (List);
    } //Функция балансировки
    friend std::ostream& operator<<(std::ostream& os, Root<T>& root) //Перегрузка оператора вывода дерева
    {
        FILE* workFile; FileNode rRoot; T rObj;
        if ((workFile = fopen(root.fileName, "rb")) == nullptr) return os;
        fread((char*)&rRoot,SOFFN,1,workFile);
        fread((char*)&rObj,root.TSZ,1,workFile);
        os<<"ROOT->"<<rObj<<std::endl;
        if (rRoot.fp_right!=FNULL) root.printBT(os,"      ",rRoot.fp_right,true,workFile,root.TSZ);
        if (rRoot.fp_left!=FNULL) root.printBT(os,"      ",rRoot.fp_left,false,workFile,root.TSZ);
        fclose(workFile);
        return os;
    }
};

#endif //CURSEWORK_1_ROOT_H