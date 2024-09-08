#ifndef SERVER_HPP
#define SERVER_HPP

#include <raylib.h>
#include <string>

class Server {
    // this is just server block
    public:
        Server();
        void Draw(int y_offset) const;
        void Update() const;
        void Events() const;
    private:
        std::string serverName;
        std::string motd;
        int port;
        std::string ip;
        bool hovered;
        bool enabled;
};

#endif