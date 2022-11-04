//
// Created by Illea on 30.10.2022.
//

#ifndef CURSEWORK_1_FTREE_H
#define CURSEWORK_1_FTREE_H

#include <fstream>
#include <cstring>
#include "tree.h"

#define TSZ sizeof(ftree)
#define FNULL -1L

class ftree{
private:
    long fp_left;
    long fp_right;
    int sz;
public:
    ftree();
    friend tree* myLoad(long,FILE*);
    friend long putTree(tree*, FILE*);
    friend tree* loadTree(const char *filename);
    friend tree* getTree(long pos,FILE *fileName);
};


#endif //CURSEWORK_1_FTREE_H
