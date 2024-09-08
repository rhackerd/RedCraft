#ifndef GAMECREATOR_H
#define GAMECREATOR_H
#include <raylib.h>
#include <string>
#include "../utils/constants.hpp"
#include "../gui/gui.hpp"
#include <utility>
#include <vector>
#include <string>
#include "../gui/server.hpp"
#include "../gui/input.hpp"


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
    void Events();
    void CheckServers();
    void drawServers();
    void pingServer();
    std::string recieve_data(int sock);
    void send_int(int number, int sock);
    int connectToServer(int port);
    void drawServer();
    void unLoad();
    int getServerPort();

private:
    void DrawBG();
    void addServer(std::vector<std::pair<std::string, std::pair<int, std::pair<std::string, std::string>>>>& servers, const std::string& ip, int port, const std::string& motd, const std::string& name);
    int seed = 324924929; // this is default seed for the perlin noise
    std::string saveName;
    int difficulty = NORMAL;
    bool cheats = false;
    Button confirm;
    Button load;
    Button back;
    int timeElapsed;
    std::pair<int, std::pair<std::string, std::string>> Localserver;
    //       port, motd                 , server name
    int sock;
    std::vector<Server> servers;
    int selected = -1;
    int serverPort;
    std::string serverIp;
    Input serverName;
    Input serverIP;
    bool creatingServer = false;
    Button createServer;

};



#endif