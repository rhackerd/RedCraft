#include "gameCreator.hpp"
#include <cmath>
#include <cstring>
#include <string>
#include "../gui/gui.hpp"
#include <raylib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../resources/textures.hpp"
#include "../gui/server.hpp"

GameCreator::GameCreator() : seed(324924929), confirm("Join", 10, GetScreenHeight() - 220, []() {  }, {223, 208, 184, 255}, {148, 137, 121, 255}, 0.1f), load("Quit", 10, GetScreenHeight() - 220, []() { debug("GameState Changed to -1"); }, {223, 208, 184, 255}, {148, 137, 121, 255}, 0.1f), back("Back", 10, GetScreenHeight() - 220, []() {  }, {223, 208, 184, 255}, {148, 137, 121, 255}, 0.1f), serverName(0,0), serverIP(0,500), createServer("Create", GetScreenWidth() - 100, GetScreenHeight() - 50, {  }, {223, 208, 184, 255}, {148, 137, 121, 255}, 0.1f) {
timeElapsed = 0;
servers = {}; 
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
    serverIP.update();
    serverName.update();
    confirm.Events();
    load.Events();
    back.Events();
    confirm.setX(GetScreenWidth()-100);
    confirm.setY(GetScreenHeight() - 50);
    back.setX(0);
    back.setY(GetScreenHeight() - 50);
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
    this->DrawBG();
    this->Update();
    if (this->creatingServer == false) { 
        this->drawServer(); 
        if (!Localserver.first) {
        DrawText("No servers found", 10, 10, 30, {255,255,255,255});
        DrawText("If you dont know how to create one\ngo to https://github.com/rhackerd/redcraft-server\nor create one manually with + below", 10, 45, 20, {255,255,255,100});
        }else{
            confirm.draw();
        }
    }else {
        serverIP.update();
        serverName.update();
        serverIP.draw();
        serverName.draw();
    }
    load.draw();
    back.draw();
}

void GameCreator::drawServer() {
    const int spacing = 10;
    const int size = 100;
    float y_offset = 0;  // Use float for y_offset to match the expected type in DrawRectangleRounded

    // Draw local server if it exists
    if (Localserver.first != 0) {
        DrawRectangleRounded(
            {10.0f, 10.0f, static_cast<float>(GetScreenWidth() - 20), static_cast<float>(size)}, 
            0.2f, 1, 
            {0, 0, 0, 255}
        );
        DrawText(Localserver.second.second.c_str(), 15, static_cast<int>(15 + y_offset), 30, {255, 255, 255, 255});
        DrawText(Localserver.second.first.c_str(), 15, static_cast<int>(45 + y_offset), 25, {255, 255, 255, 100});
    }
    y_offset += size + spacing; // Move to next position

    // Draw list of servers
    for (const auto& server : servers) {
        server.Update();
        server.Draw(y_offset);
        y_offset += size + spacing;
    }
    // draw another server with +
        if (CheckCollisionPointRec(GetMousePosition(), {10.0f, 10.0f + y_offset, static_cast<float>(GetScreenWidth() - 20), static_cast<float>(size)})) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                this->creatingServer = true;
            }
        }
            DrawRectangleRounded(
            {10.0f, 10.0f + y_offset, static_cast<float>(GetScreenWidth() - 20), static_cast<float>(size)}, 
            0.2f, 1, 
            {0, 0, 0, 255}
        );
        DrawText("+", 20+(GetScreenWidth()/2)-MeasureText("+", 100), y_offset+((size/2)-MeasureText("+", 100)+15), 100, {255,255,255,100});
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

void GameCreator::DrawBG() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Get the dimensions of the texture
    int textureWidth = grassTexture.width;
    int textureHeight = grassTexture.height;

    // Loop through the screen in steps of the texture size
    for (int y = 0; y < screenHeight; y += textureHeight) {
        for (int x = 0; x < screenWidth; x += textureWidth) {
            DrawTexture(stoneTexture, x, y, WHITE);
        }
    }
}