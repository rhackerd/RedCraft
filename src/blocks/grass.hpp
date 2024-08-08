#ifndef GRASS_H
#define GRASS_H

#include <iostream>
#include <raylib.h>
#include "Voxel.hpp"

class Grass : public Voxel {
public:
    Grass(int x, int y) : Voxel(x, y, GREEN) {
        id = 1;  // Set id for Grass
        texture = LoadTexture("assets/grass.png");
        this->autoRotate();
    }

    ~Grass() override {}

    void Draw() const override {
        Voxel::Draw();
    }

    void onClick() override {}
    void onHover() override {}
};

#endif // GRASS_H
