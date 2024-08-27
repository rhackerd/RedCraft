#include "gameCreator.hpp"
#include <cmath>
#include <cstring>
#include <string>
#include "../gui/gui.hpp"
#include <raylib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

GameCreator::GameCreator() : seed(324924929), confirm("Create", 10, GetScreenHeight() - 220, []() {  }, {223, 208, 184, 255}, {148, 137, 121, 255}, 0.1f), load("Quit", 10, GetScreenHeight() - 220, []() { debug("GameState Changed to -1"); }, {223, 208, 184, 255}, {148, 137, 121, 255}, 0.1f) {
timeElapsed = 0;

Localserver = {0, {"", ""}};
}
GameCreator::~GameCreator() {

}


void GameCreator::Init() {
}

std::string GameCreator::recieve_data(int sock) {
    char buffer[1024] = {0};
    int valread = read(sock, buffer, sizeof(buffer) - 1);
    if (valread < 0) {
        
        return "";
    }
    std::string response = std::string(buffer, valread);
    if (response.empty()) {
            
        }
    return response;
}

void GameCreator::send_int(int number, int sock) {
    int value = number;
    int32_t network_value = htonl(value);
    if (send(sock, &network_value, sizeof(network_value), 0) < 0) {
        
        close(sock);
    }
    return;
}
int GameCreator::connectToServer(int port) {
    int sock = 0;
    struct sockaddr_in serv_addr;

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 address from text to binary
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        
        close(sock);
    }

    // Connect to server
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        
        close(sock);
    }
    return sock;

}

void GameCreator::Update() {
    confirm.Events();
    load.Events();
    confirm.setX(GetScreenWidth()-100);
    confirm.setY(GetScreenHeight() - 50);
    this->Events();
    if (GetTime() > 3.0 + timeElapsed) {
        timeElapsed += 3.0;
        this->CheckServers();
    }
}

void GameCreator::Events() {
    timeElapsed += GetFrameTime();
}

void GameCreator::CheckServers() {
    info("checking for servers");

    this->pingServer();
}

void GameCreator::Unload() { close(sock); };

void GameCreator::pingServer() {
    sock = connectToServer(25566);

    // send ping
    send_int(7, sock);

    std::string response = recieve_data(sock);
    if (response == "rc") {
        send_int(0, sock);
        std::string motd = recieve_data(sock);
        std::string name = recieve_data(sock);
        Localserver = {25566, {motd, name}};   
    }else{
        Localserver = {0, {"", ""}};   
    }
    close(sock);
}


void GameCreator::Draw() {
    this->Update();
    this->drawServer();
    if (!Localserver.first) {
        DrawText("No servers found", 10, 10, 30, {255,255,255,255});
        DrawText("If you dont know how to create one\ngo to https://github.com/rhackerd/redcraft-server", 10, 45, 20, {255,255,255,100});
    }else {
        confirm.draw();
    }
    load.draw();
}

void GameCreator::drawServer() {
    if (Localserver.first != 0) {
        DrawRectangleRounded({10,10,static_cast<float>(GetScreenWidth() - 20), 100}, 0.2, 1, {0,0,0 ,255});
        DrawText(Localserver.second.second.c_str(), 15, 15, 30, {255,255,255,255});
        DrawText(Localserver.second.first.c_str(), 15, 45, 25, {255,255,255,100});
    }
}


int GameCreator::getServerPort() {
    return this->Localserver.first;
}

int GameCreator::next() {
    if (confirm.isClicked()){
        return 1;
    }
    return 0;
}


int GameCreator::getSeed() {
    return seed;
}


std::string GameCreator::getSaveName() {
    return saveName;
}


int GameCreator::getDifficulty() {
    return difficulty;
}


int GameCreator::getCheats() {
    // like creative etc.
    return cheats;
}