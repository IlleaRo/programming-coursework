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
    long appendValueToFtree(T nValue,FILE* workFile) //������ ������ ��������, ����� �������, � ����
    {
        long pos; //���������� ����� ������� � �����
        FileNode<T> newNode; //���������� ����� ������� ��� ����������� ��������
        newNode.fp_right = newNode.fp_left = FNULL; //����� ������� ������ - ����
        fseek(workFile,0L,SEEK_END); //������������� � ����� �����
        pos = ftell(workFile); //���������� ����� �� �������� ����������� ����� �������
        fwrite((char*)&newNode,sizeof(newNode),1,workFile); //���������� �������
        fwrite((char*)&nValue,TSZ,1,workFile); //���������� ������ �������
        return pos; //���������� ����� ����� �������
    }
    long appendTree(long pos, T nValue, FILE* fileName)
    {
        FileNode<T> nNode; T valueFromFtree;
        fseek(fileName,pos,SEEK_SET); //��������� � ������ ���������� ����
        fread((char*)&nNode,sizeof(nNode),1,fileName); //��������� ��������� �������
        fread((char*)&valueFromFtree,TSZ,1,fileName); //��������� �������� ������
        if (nValue>valueFromFtree)
        {
            if (nNode.fp_right!=FNULL) return appendTree(nNode.fp_right,nValue,fileName);

            nNode.fp_right = appendValueToFtree(nValue,fileName);
            fseek(fileName,pos,SEEK_SET); //�������� ������� ������� ������
            fwrite((char*)&nNode,sizeof(nNode),1,fileName); //�������������� ��������� �� �����
            return nNode.fp_right;
        }
        if (nNode.fp_left!=FNULL) return appendTree(nNode.fp_left,nValue,fileName);

        nNode.fp_left = appendValueToFtree(nValue,fileName);
        fseek(fileName,pos,SEEK_SET); //�������� ������� ������� ������
        fwrite((char*)&nNode,sizeof(nNode),1,fileName); //�������������� ��������� �� �����
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
