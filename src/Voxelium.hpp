#ifndef VOXELIUM_H
#define VOXELIUM_H

#include <raylib.h>


class Voxelium
{
public:
    Voxelium();
    ~Voxelium();
    void init();
    void update();
    void draw();
    void genChunk(int x, int y);
    void delBlock(int x, int y);
    void changeBlock(int x, int y);
    void setBlock(int x, int y);
    

private:
    int width;
    int height;
    int depth;
};

#endif
