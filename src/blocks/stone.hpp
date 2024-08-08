#ifndef STONE_H
#define STONE_H

#include <iostream>
#include <raylib.h>
#include "Voxel.hpp"

class Cobblestone : public Voxel {
public:
    Cobblestone(int x, int y) : Voxel(x, y, GRAY) {
        id = 2;  // Set id for Stone
        texture = LoadTexture("assets/stone1.png");
        this->autoRotate();
    }

    ~Cobblestone() override {
        Voxel::~Voxel();
    };

    void Draw() const override {
        Voxel::Draw();
    }

    void onClick() override {}
    void onHover() override {}
};

#endif // STONE_H
