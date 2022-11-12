#pragma once

#include <fstream>
#include <cstring>

#define FNULL (-1L)


template <typename T>
class FileNode{
public:
    long fp_left;
    long fp_right;
    FileNode()
    {
        this->fp_right = FNULL;
        this->fp_left = FNULL;
    };

};

