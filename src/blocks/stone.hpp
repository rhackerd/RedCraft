#ifndef STONE_H
#define STONE_H

#include <iostream>
#include <raylib.h>
#include "Voxel.hpp"
#include "../resources/textures.hpp"

class Cobblestone : public Voxel {
public:
    Cobblestone(int x, int y) : Voxel(x, y, GRAY) {
        id = 2;  // Set id for Cobblestone
        this->autoRotate();
    }

    ~Cobblestone() override {
        UnloadTexture(stoneTexture);
    };

    void Draw() const override {
        Voxel::Draw();
    }

    void onTextureLoaded() {
        this->texture = stoneTexture;
    }

    void onClick() override {}
    void onHover() override {}
};

#endif // STONE_H
