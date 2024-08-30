#include "loading.hpp"
#include <string>
#include <raylib.h>


Loading::Loading() {
    progress = 100;
}

Loading::~Loading() {}

void Loading::draw() {
    ClearBackground(BLACK);
    DrawText("RedCraft", (GetScreenWidth()-MeasureText("RedCraft", 40))/2, 50, 40, WHITE);
    DrawText("Loading...", 10, GetScreenHeight() - 60, 20, WHITE);
    DrawRectangle(0, GetScreenHeight() - 30, GetScreenWidth(), 30, GRAY);
    DrawRectangle(0, GetScreenHeight() - 30, GetScreenWidth() * progress / 100, 30, RED);
    std::string progressStr = std::to_string(progress) + "%"; 
    int out = (GetScreenWidth() * progress / 100)-MeasureText(progressStr.c_str(), 20)-10;
    if (out < 0) {
        out = 0;
    }
    DrawText(progressStr.c_str(), out, GetScreenHeight() - 25, 20, WHITE);
}

int Loading::next() {
    progress++;
    if (progress > 100) {
        return 1;
    }
    return 0;
}