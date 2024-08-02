#ifndef GAMECREATOR_H
#define GAMECREATOR_H
#include <raylib.h>
#include <string>
#include "constants.hpp"
#include "gui.hpp"


class GameCreator
{
public:
    GameCreator();
    ~GameCreator();
    void Init();
    void Update();
    void Draw();
    void Unload();
    int next();
    int getSeed();
    std::string getSaveName();
    int getDifficulty();
    int getCheats();

private:
    int seed = 324924929; // this is default seed for the perlin noise
    std::string saveName;
    int difficulty = NORMAL;
    bool cheats = false;
    Button confirm;
    Button load;
    
};



#endif