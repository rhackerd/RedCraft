#ifndef VOXELIUM_H
#define VOXELIUM_H

#include <raylib.h>
#include <vector>
#include <memory>
#include "../blocks/Voxel.hpp"

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
    void setBlock(int x, int y, int id);
    void setOffset(int x, int y);

private:
    int width;
    int height;
    int depth;
    int offsetY;
    int offsetX;
    std::vector<std::shared_ptr<Voxel>> blocks;
};

#endif // VOXELIUM_H
