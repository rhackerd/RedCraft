#include "Voxelium.hpp"
#include <memory>
#include <raylib.h>
#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include "logging.hpp"

Voxelium::Voxelium() {
    width = 10;
    height = 10;
    depth = 10;
}

Voxelium::~Voxelium() {}

void Voxelium::init() {
    //InitWindow(width, height, "Voxelium");
    //SetTargetFPS(60);
    blocks.emplace_back(std::make_shared<Grass>(10,10));

}

void Voxelium::update() {
    //UpdateWindow();
    for (const auto& block : blocks) {
        block->Update();
        block->SetOffset(10,10);
    }
}

void Voxelium::draw() {
    for (const auto& block : blocks) {
        block->Draw();
    }
}

