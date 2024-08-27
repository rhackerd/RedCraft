#include "../core/Game.hpp"
#include "../gui/gui.hpp"
#include "gameCreator.hpp"
#include <cstdint>
#include <cstdlib>
#include <netinet/in.h>
#include <raylib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <iostream>

std::string recieve_data(int sock) {
    char buffer[1024] = {0};
    int valread = read(sock, buffer, sizeof(buffer) - 1);
    if (valread < 0) {
        std::cerr << "Error reading from socket" << std::endl;
        return "";
    }
    std::string response = std::string(buffer, valread);
    if (response.empty()) {
            std::cerr << "Failed to receive data" << std::endl;
        }
    return response;
}

void send_int(int number, int sock) {
    int value = number;
    int32_t network_value = htonl(value);
    if (send(sock, &network_value, sizeof(network_value), 0) < 0) {
        std::cerr << "Send failed: " << strerror(errno) << std::endl;
        close(sock);
    }
    return;
}

void send_string(std::string string, int sock) {
    std::string message = string;
    int bytes_sent = send(sock, message.c_str(), message.size(), 0);
    if (bytes_sent < 0) {
        std::cerr << "Send failed: " << strerror(errno) << std::endl;
        close(sock);
    }
}
int connectToServer(int port) {
    int sock = 0;
    struct sockaddr_in serv_addr;

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error: " << strerror(errno) << std::endl;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 address from text to binary
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address / Address not supported" << std::endl;
        close(sock);
    }

    // Connect to server
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection failed: " << strerror(errno) << std::endl;
        close(sock);
    }
    return sock;

}

Game::Game()
    : gameState(0), width(800), height(600),
      menu(width, height), voxelium(), settings(), loading(), creator(), debugging(false), inventory(), discord(){
}

Game::~Game() {
    close(sock);
    CloseWindow(); // Properly close the raylib window
}

void Game::run() {
    while (!WindowShouldClose()) {
        update();
        render();
    }
}

void Game::debug(bool debug) {
    debugging = debug;
}

void Game::init() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);

    std::string title = debugging ? "RedCraft DEBUG" : "RedCraft";
    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);
    discord.init("1026924641962430464"); // Pass application ID as a string
    voxelium.init();
}

void Game::update() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    menu.updateButtonPositions(screenWidth, screenHeight);
    handleGameState();
}

void Game::render() {
    BeginDrawing();
    ClearBackground(DARKGRAY);

    switch (gameState) {
        case 0:
            loading.draw();
            break;
        case 1:
            menu.draw();
            break;
        case 2:
            creator.Draw();
            break;
        case 3:
            voxelium.draw();
            inventory.draw();
            break;
    }

    if (debugging) {
        char stateText[50];
        snprintf(stateText, sizeof(stateText), "State: %d", gameState);
        DrawText(stateText, 0, 0, 20, WHITE);
        snprintf(stateText, sizeof(stateText), "Win focused: %s", IsWindowFocused() ? "true" : "false");
        DrawText(stateText, 0, 20, 20, WHITE);
        snprintf(stateText, sizeof(stateText), "Win ready: %s", IsWindowReady() ? "true" : "false");
        DrawText(stateText, 0, 40, 20, WHITE);
        snprintf(stateText, sizeof(stateText), "FPS: %d", GetFPS());
        DrawText(stateText, 0, 60, 20, WHITE);
    }

    EndDrawing();
}

void Game::handleGameState() {
    discord.update();
    switch (gameState) {
        case 0:
            gameState += loading.next();
            discord.changeState("Loading...");
            break;
        
        case 1: {
            int nextStage = menu.nextStage();
            if (nextStage == 1) {
                gameState += 1;
                creator.Unload();
            } else if (nextStage == -1) {
                info("closing game");
                CloseWindow();
                exit(0);
            }
            menu.handleEvents();
            discord.changeState("In menu");
            break;
        }

        case 2: {
            gameState += creator.next();
            if (creator.next() == 1) {
                sock = connectToServer(creator.getServerPort());

                // Send integer to server
                int value = 1;
                send_int(value, sock);

                std::string message = "rhacker_8853";
                send_string(message, sock);

                std::string response = recieve_data(sock);
                info(response);
                 

            }
            discord.changeState("Connecting to server");
            break;
        }

        case 3:
            voxelium.update();
            discord.changeState("In game");
            inventory.update();
            break;

        default:
            break;
    }
}