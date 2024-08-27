#include <discord_register.h>
#include <discord_rpc.h>
#include <iostream>
#include <cstring>
#include <ctime>
#include <thread>

class Discord {
public:
    void init(const char* appID) {
        this->state = "In Menu";
        DiscordEventHandlers handlers;
        memset(&handlers, 0, sizeof(handlers));
        Discord_Initialize(appID, &handlers, 1, nullptr);

        DiscordRichPresence presence;
        memset(&presence, 0, sizeof(presence));
        presence.state = "In game";
        presence.startTimestamp = std::time(nullptr);
        presence.endTimestamp = std::time(nullptr) + 3600; // Example: 1 hour
        presence.largeImageKey = "icon";
        Discord_UpdatePresence(&presence);
    }

    void update() {
        Discord_UpdatePresence(&presence);
        presence.state = state.c_str();
        presence.largeImageKey = "icon";
    }

    void changeState(std::string state) {
        this->state = state;
    }

private:
    DiscordRichPresence presence;

    std::string state;
};
