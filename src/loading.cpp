#include "loading.hpp"
#include <string>
#include <raylib.h>


Loading::Loading() {
    progress = 0;
}

Loading::~Loading() {}

void Loading::draw() {
    ClearBackground(BLACK);
    DrawText("RedCraft", (GetScreenWidth()-MeasureText("RedCraft", 40))/2, 50, 40, WHITE);
    DrawText("Loading...", 200, 250, 20, WHITE);
    DrawText(std::to_string(progress).c_str(), 200, 300, 20, WHITE);
}

int Loading::next() {
    //progress++;
    if (progress > 100) {
        return 1;
    }
    return 0;
}