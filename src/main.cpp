#include <raylib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include "core/Voxelium.hpp"
#include "utils/logging.hpp"
#include "core/Game.hpp"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include "resources/textures.hpp"




#define DEBUG false




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

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "Failed to initialize SDL: " << SDL_GetError() << endl;
        return 1;
    }
    SetTraceLogCallback(CustomLog);

    info("Welcome to redcraft!");
    if (DEBUG) {
        info("DEBUG MODE is set on");   
    }
    // Initialization
    Game game;
    game.init();
    game.debug(DEBUG);
    LoadAllTextures();
    std::cout << stoneTexture.id << std::endl;
    game.run();

    return 0;
}
