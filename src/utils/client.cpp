#include "arpa/inet.h"
#include "sys/socket.h"
#include "unistd.h"
#include "string.h"
#include "errno.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "client.hpp"


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

int recieve_int(int sock) {
    char buffer[4];
    int valread = read(sock, buffer, 4);  // Read exactly 4 bytes
    if (valread < 0) {
        std::cerr << "Error reading from socket: " << strerror(errno) << std::endl;
        return -1;  // Indicate an error
    } else if (valread == 0) {
        std::cerr << "Connection closed by the server" << std::endl;
        return -1;  // Indicate the connection was closed
    }

    // Convert the 4-byte buffer to an integer
    return ntohl(*reinterpret_cast<int*>(buffer));
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

std::pair<std::string, std::string> ping_server(int sock) { }

std::string load_server(int sock, std::string player_name) {
    send_int(1, sock);
    send_string(player_name, sock);
    return recieve_data(sock);
}

void unload_server(int sock, std::string player_name) {
    send_int(3, sock);
    send_string(player_name, sock);
}

std::pair<int, std::vector<int>> get_cell(int sock, int x, int y) {
    std::vector<int> cell;
    int size = 16;

    // Send command to the server to get a cell
    send_int(8, sock);  // Command code for fetching a cell
    send_int(x, sock);  // Send the x-coordinate
    send_int(y, sock);  // Send the y-coordinate

    // Receive the cell data from the server
    for (int i = 0; i < size * size; i++) {
        int data = recieve_int(sock);  // Receive 4 bytes and convert to an integer
        if (data == -1) {
            // Handle error case, returning an error code and empty vector
            return std::make_pair(-1, std::vector<int>());
        }
        cell.emplace_back(data);
    }

    // Return the success code (e.g., 0) and the cell data
    return std::make_pair(size, cell);
}
