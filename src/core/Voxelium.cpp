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
    std::cout << "Voxelium initialized" << std::endl;
}

// Update blocks
void Voxelium::update() {
    for (const auto& block : blocks) {
        if (stoneTexture.id != 0 && grassTexture.id != 0 && block->texture.id == 0) {
        block->onTextureLoaded();
        }
        block->SetOffset(offsetX, offsetY);
    }
    if (this->disable_moving == false) {
        this->offsetX += (IsKeyDown(KEY_A)*2) - (IsKeyDown(KEY_D)*2);
        this->offsetY += (IsKeyDown(KEY_W)*2) - (IsKeyDown(KEY_S)*2);
    }
}

// Draw blocks
void Voxelium::draw() {
    for (const auto& chunk : chunk_texture) {
        Rectangle source = { 0, 0, chunk.second.second.width, -chunk.second.second.height }; // Flip vertically
        Rectangle dest = { chunk.first, chunk.second.first, chunk.second.second.width, chunk.second.second.height };
        Vector2 origin = { 0-offsetX, 0-offsetY };

        DrawTexturePro(chunk.second.second, source, dest, origin, 0.0f, WHITE);
    }
    const int blockRadius = 3; // Number of blocks around the cursor
    const int blockSize = 50;  // Size of each block in pixels
    const int maxDistance = blockRadius * blockSize; // Maximum distance to consider
    
    Vector2 mousePos = GetMousePosition();
    int cursorX = static_cast<int>(mousePos.x);
    int cursorY = static_cast<int>(mousePos.y);

    for (const auto& block : blocks) {
        auto [blockX, blockY] = block->getPosition();
        int blockCenterX = blockX + blockSize / 2;
        int blockCenterY = blockY + blockSize / 2;

        int deltaX = std::abs(blockCenterX - cursorX);
        int deltaY = std::abs(blockCenterY - cursorY);
        
        if (deltaX <= maxDistance && deltaY <= maxDistance) {
            block->Draw();
            block->Update();
        }
    }
}


void Voxelium::setMovement(bool enabled) {
    this->disable_moving = enabled;
}

void Voxelium::setChunk(std::vector<std::pair<int, std::pair<int, int>>> chunk) {
    int first_block_x = 0;
    int first_block_y = 0;
    int x = 0;

    // Set blocks in the chunk
    RenderTexture2D texture = LoadRenderTexture(16 * 50, 16 * 50);


    BeginTextureMode(texture);
    ClearBackground(BLANK); // Clear the texture with transparency
    for (const auto& block : chunk) {
        int block_id = block.first;
        int block_x = block.second.first;
        int block_y = block.second.second;
        //setBlock(block_x, block_y, block_id); // Assign block to some data structure
            switch (block_id) {
        case 0:
            DrawTexture(grassTexture, block_x*50, block_y*50, WHITE);
            break;
        case 1:
            DrawRectangle(block_x*50, block_y*50, 50, 50, BLUE);
            break;
        case 2:
            DrawTexture(stoneTexture, block_x*50, block_y*50, WHITE);
            break;
        }
        if (x == 0) { // Record the position of the first block
            first_block_x = block_x;
            first_block_y = block_y;
        }
        x++;
    }
    EndTextureMode();
    std::cout << "first_block_x: " << first_block_x << " first_block_y: " << first_block_y << std::endl;

    // Store the chunk data
    std::pair<int, std::pair<int, Texture2D>> chunk_texture;
    chunk_texture.first = first_block_x;
    chunk_texture.second.first = first_block_y;
    chunk_texture.second.second = texture.texture; // Save the texture

    this->chunk_texture.push_back(chunk_texture);

    // Clean up RenderTexture2D (optional, if no longer needed elsewhere)
    // UnloadRenderTexture(texture); // Uncomment if you don't need the RenderTexture2D after this
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