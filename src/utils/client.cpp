// Client.cpp
#include "client.hpp"

Client::Client(const std::string& ip, int port) : connected(false) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr);
}

Client::~Client() {
    if (connected) {
        close(sockfd);
    }
}

void Client::connectToServer() {
    if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    connected = true;
}

void Client::update() {
    // Implement receiving and handling server messages if needed
}

void Client::sendPing() {
    int eventType = PING;
    sendData(&eventType, sizeof(eventType));
}

void Client::sendLoad(const std::string& playerName) {
    int eventType = LOAD;
    sendData(&eventType, sizeof(eventType));
    sendData(playerName.c_str(), playerName.size() + 1); // Including null terminator
}

void Client::sendGameCommand(const std::string& command) {
    int eventType = GAME_COMMANDS;
    sendData(&eventType, sizeof(eventType));
    sendData(command.c_str(), command.size() + 1); // Including null terminator
}

void Client::sendData(const void* data, size_t size) {
    if (send(sockfd, data, size, 0) < 0) {
        std::cerr << "Send failed" << std::endl;
    }
}

void Client::receiveData(void* buffer, size_t size) {
    if (recv(sockfd, buffer, size, 0) < 0) {
        std::cerr << "Receive failed" << std::endl;
    }
}
