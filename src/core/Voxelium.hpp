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
    void setMovement(bool enabled);
    void setChunk(std::vector<std::pair<int, std::pair<int, int>>> chunk);

private:
    int width;
    int height;

    bool render_layer_0;
    bool render_layer_1;
    bool update_layers;
    bool disable_moving;

    int depth;
    int offsetY;
    int offsetX;
    std::vector<std::shared_ptr<Voxel>> blocks;
    std::vector<std::pair<int, std::pair<int, Texture2D>>> chunk_texture;
};

#endif // VOXELIUM_H
