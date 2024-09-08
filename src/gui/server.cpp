#include "../gui/server.hpp"
#include <raylib.h>
#include <iostream>


Server::Server() {

}

void Server::Draw(int y_offset) const {
    DrawRectangleRounded(
        {10.0f, 10.0f + y_offset, static_cast<float>(GetScreenWidth() - 20), static_cast<float>(100)}, 
        0.2f, 1, 
        {0, 0, 0, 255}
    );
}

void Server::Update() const{
    Events();
}

void Server::Events() const {

}

