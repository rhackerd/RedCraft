#ifndef GRASS_H
#define GRASS_H
#include <iostream>
#include "Voxel.hpp"

class Grass : public Voxel {
public:
    Grass(int x, int y) : Voxel(x, y, GREEN) {
        id = 1;  // Set id for Grass
    }

    ~Grass() override = default;

    void Draw() const override {
        Voxel::Draw();
    }

    void onClick() override {
        
    }

    void onHover() override {
        
    }
};

#endif // GRASS_H
