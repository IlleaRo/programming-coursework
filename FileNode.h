#ifndef CURSEWORK_1_FILENODE_H
#define CURSEWORK_1_FILENODE_H

#define FNULL (-1L)
#define SOFFN sizeof(FileNode)


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

#endif //CURSEWORK_1_FILENODE_H

