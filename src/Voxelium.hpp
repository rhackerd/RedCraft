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
    void drawVoxel();

private:
    int width;
    int height;
    int depth;
};

#endif
