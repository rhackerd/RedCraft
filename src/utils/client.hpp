#ifndef CLIENT_HPP
#define CLIENT_HPP


#include <string>
#include <utility>
#include <vector>

#include <string>

// Function to connect to a server on a specified port
int connectToServer(int port);

// Function to receive data from a socket
std::string recieve_data(int sock);

// Function to send an integer to a socket
void send_int(int number, int sock);

// Function to send a string to a socket
void send_string(const std::string string, int sock);

std::string load_server(int sock, std::string player_name);

void unload_server(int sock, std::string player_name);

std::pair<int, std::vector<int>> get_cell(int sock, int x, int y);

int recieve_int(int sock);

#endif // CLIENT_HPP
