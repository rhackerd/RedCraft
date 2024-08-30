#ifndef CHAT_HPP
#define CHAT_HPP
#include <raylib.h>
#include <string>

class Chat
{
    public:
        Chat();
        ~Chat();
        void Draw();
        void Update(); 
        int sock; 
        void clearText();

    private:

        void trySend();
        void drawErr();
        void drawBG();
        void drawText();
        void drawHistory();

        std::string actText;
        bool isErr;
        std::string errText;
        bool tryToSend;
        bool isChatOpen;
};


#endif