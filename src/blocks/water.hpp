#ifndef WATER_H
#define WATER_H

#include <iostream>
#include <raylib.h>
#include "Voxel.hpp"

class Water : public Voxel {
public:
    Water(int x, int y) : Voxel(x, y, BLUE) {
        id = 3;  // Set id for Water
        this->autoRotate();
    }

    ~Water() override {}

    void Draw() const override {
        Voxel::Draw();
    }

    void onTextureLoaded() override {
        // If you have a water texture, set it here
    }

    void onClick() override {}
    void onHover() override {}
};

#endif // WATER_H
