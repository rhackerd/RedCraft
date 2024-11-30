#include "../gui/chat.hpp"
#include <cmath>
#include <cstdio>
#include <raylib.h>
#include "../utils/logging.hpp"
#include <raylib.h>
#include <string>
#include <vector>


Chat::Chat() {
    this->isChatOpen = false;
    this->isErr = false;
    this->tryToSend = false;
    this->actText = "";
    this->errText = "";
}

Chat::~Chat() {

}
/// Draw the chat window. This includes the background, the text entry box, the chat history, and any error messages.

void Chat::Draw() {
    if (this->isChatOpen) {
        this->drawBG();
        this->drawText();
        this->drawErr();
    }
    this->drawHistory();
}

void Chat::Update() {
    if (IsKeyPressed(KEY_ENTER)) {
        this->trySend();
        this->clearText();
    }else if (IsKeyPressed(KEY_T) && this->isChatOpen == false) {
        this->isChatOpen = true;
    }else if((IsKeyPressedRepeat(KEY_BACKSPACE) || IsKeyPressed(KEY_BACKSPACE)) && this->actText.length() > 0) {
        this->actText.pop_back();
    }
    else if(this->isChatOpen) {
        int key = GetCharPressed();
        if (key != 0) {
            this->actText += key;
        }
    }
}

void Chat::clearText() {
    this->actText = "";
    this->isErr = false;
    this->errText = "";
    this->isChatOpen = false;
}

bool Chat::isEnabled() {
    return this->isChatOpen;
}

void Chat::trySend() {
    if (this->actText.length() > 0) {
        if (this->actText[0] == '/') {
            this->command(this->actText.erase(0, 1), {});   
        }else{
            sendBuffer.push_back(this->actText);
        }
    }
}

void Chat::readCache(std::string cache) {

}

void Chat::drawErr() {
    if (this->isErr) {

    }
}

void Chat::drawBG() {
    DrawRectangle(0, GetScreenHeight()-24, GetScreenWidth(), 24, {0,0,0,150});
}


void Chat::drawHistory() {
    for (int i = 0; i < this->messages.size(); i++) {
        DrawText(this->messages[i].c_str(), 2, 0 + 22 + (i * 20) - 24, 20, WHITE);
    }
}

void Chat::drawText() {
    DrawText(this->actText.c_str(), 2, GetScreenHeight() - 22, 20, WHITE);
}

void Chat::send(std::string text) {
    this->messages.push_back(text);
}

void Chat::command(std::string command, std::vector<std::string> args = {}) {
    if (command == "help") {
        std::string help = "Commands:\n";
        this->send(help);
    }else if (command == "clear") {
        this->messages.clear();
    }else if(command == "leave") {
        send("leaving...");
        exit(0);
    }else {
        char buffer[256];
        std::sprintf(buffer, "command not found: %s", command.c_str());
        send(buffer); 
    }
}