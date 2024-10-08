#include "Voxelium.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include "../utils/stb_perlin.h"
#include <raylib.h>
#include "../blocks/grass.hpp"
#include "../blocks/stone.hpp"
#include "../blocks/water.hpp"
#include "../resources/textures.hpp"

// Constructor
Voxelium::Voxelium() : width(10), height(10), depth(10), offsetY(0), offsetX(0) {}

// Destructor
Voxelium::~Voxelium() {

}

// Function to generate 2D Perlin noise
std::vector<float> generate2DPerlinNoise(int width, int height, float scale) {
    std::vector<float> noise(width * height);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Generate Perlin noise value for (x, y)
            float nx = x * scale / width;
            float ny = y * scale / height;
            noise[y * width + x] = stb_perlin_noise3(nx, ny, 0.0f, 0, 0, 0);

            // Normalize value to [0, 1]
            noise[y * width + x] = (noise[y * width + x] + 1.0f) / 2.0f;
        }
    }
    return noise;
}

// Initialization
void Voxelium::init() {
    
}

// Update blocks
void Voxelium::update() {
    for (const auto& block : blocks) {
        if (stoneTexture.id != 0 && grassTexture.id != 0 && block->texture.id == 0) {
        block->onTextureLoaded();
        }
        block->Update();
        block->SetOffset(offsetX, offsetY);
    }
    if (this->disableMoving == false) {
        this->offsetX += (IsKeyDown(KEY_A)*2) - (IsKeyDown(KEY_D)*2);
        this->offsetY += (IsKeyDown(KEY_W)*2) - (IsKeyDown(KEY_S)*2);
    }
}

// Draw blocks
void Voxelium::draw() {


    for (const auto& block : blocks) {
        block->Draw();
    }
}

void Voxelium::setMovement(bool enabled) {
    this->disableMoving = enabled;
}

// Placeholder functions for block management
void Voxelium::genChunk(int x, int y) {
    // Implementation needed
}

void Voxelium::delBlock(int x, int y) {
    // Implementation needed
}

void Voxelium::changeBlock(int x, int y) {
    // Implementation needed
}

// grass - 0
// water - 1

void Voxelium::setBlock(int x, int y, int id) {
    switch (id) {
        case 0:
            blocks.push_back(std::make_shared<Grass>(x, y));
            break;
        case 1:
            blocks.push_back(std::make_shared<Water>(x, y));
            break;
        case 2:
            blocks.push_back(std::make_shared<Cobblestone>(x, y));
            break;
    }
}

void Voxelium::setOffset(int x, int y) {
    this->offsetX = x;
    this->offsetY = y;
}