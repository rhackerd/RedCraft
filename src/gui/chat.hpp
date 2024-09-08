#ifndef CHAT_HPP
#define CHAT_HPP
#include <raylib.h>
#include <string>
#include <vector>

class Chat
{
    public:
        Chat();
        ~Chat();
        void Draw();
        void Update(); 
        int sock; 
        void clearText();
        void send(std::string text);
        void command(std::string command, std::vector<std::string> args);
        bool isEnabled();
        std::vector<std::string> sendBuffer;

    private:

        void trySend();
        void readCache(std::string cache);
        void drawErr();
        void drawBG();
        void drawText();
        void drawHistory();
        std::vector<std::string> messages;
        std::string actText;
        bool isErr;
        std::string errText;
        bool tryToSend;
        bool isChatOpen;
};


#endif