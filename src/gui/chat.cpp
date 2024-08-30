#include "../gui/chat.hpp"
#include <raylib.h>

#include <raylib.h>
#include <string>


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
        this->clearText();
        this->trySend();
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

void Chat::trySend() {
    if (this->tryToSend == true) {
        this->tryToSend = false;
    }
}

void Chat::drawErr() {
    if (this->isErr) {

    }
}

void Chat::drawBG() {
    DrawRectangle(0, GetScreenHeight()-24, GetScreenWidth(), 24, {0,0,0,150});
}


void Chat::drawHistory() {

}

void Chat::drawText() {
    DrawText(this->actText.c_str(), 2, GetScreenHeight() - 22, 20, WHITE);
}