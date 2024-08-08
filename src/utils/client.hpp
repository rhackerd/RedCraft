// Client.hpp
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

#define PING 0
#define LOAD 1
#define UNLOAD 3 
#define GAME_VERSION 4
#define SERVER_VERSION 5
#define GAME_COMMANDS 6

class Client {
public:
    Client(const std::string& ip, int port);
    ~Client();
    
    void connectToServer();
    void update();
    void sendPing();
    void sendLoad(const std::string& playerName);
    void sendGameCommand(const std::string& command);

private:
    int sockfd;
    sockaddr_in serverAddr;
    bool connected;
    
    void sendData(const void* data, size_t size);
    void receiveData(void* buffer, size_t size);
};

#endif // CLIENT_HPP
