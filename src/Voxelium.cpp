#include "Voxelium.hpp"


Voxelium::Voxelium() {
    width = 10;
    height = 10;
    depth = 10;
}

Voxelium::~Voxelium() {}

void Voxelium::init() {
    //InitWindow(width, height, "Voxelium");
    //SetTargetFPS(60);
}

void Voxelium::update() {
    //UpdateWindow();
}

void Voxelium::draw() {
    DrawText("Hello World", 190, 190, 20, WHITE);
}

