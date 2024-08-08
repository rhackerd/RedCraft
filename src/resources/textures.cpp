#include "textures.hpp"

// Define the textures
Texture2D grassTexture = {0};
Texture2D stoneTexture = {0};

// Load all textures
void LoadAllTextures() {
    if (grassTexture.id == 0) {
        grassTexture = LoadTexture("assets/grass.png");
    }
    if (stoneTexture.id == 0) {
        stoneTexture = LoadTexture("assets/stone1.png");
    }
}