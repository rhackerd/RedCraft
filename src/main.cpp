#include <raylib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

#include "Voxelium.hpp"
#include "logging.hpp"
#include "Game.hpp"
#include <stdio.h>

using namespace std;

void CustomLog(int msgType, const char *text, va_list args)
{
    //printf("%s", text);
    switch (msgType)
    {
        case LOG_INFO: info("", false); break;
        case LOG_ERROR: error("", false); break;
        case LOG_WARNING: warning("", false); break;
        case LOG_DEBUG: debug("", false); break;
        default: break;
    }

    vprintf(text, args);
    printf("\n");
}

int main() {

    SetTraceLogCallback(CustomLog);

    info("Welcome to redcraft!");
    // Initialization
    Game game;
    game.init();
    game.run();

    return 0;
}
