#include <discord_register.h>
#include <discord_rpc.h>
#include <iostream>
#include <cstring>
#include <ctime>
#include <thread>

class Discord {
public:
    void init(const char* appID) {
        DiscordEventHandlers handlers;
        memset(&handlers, 0, sizeof(handlers));
        Discord_Initialize(appID, &handlers, 1, nullptr);

        DiscordRichPresence presence;
        memset(&presence, 0, sizeof(presence));
        presence.state = "In game";
        presence.startTimestamp = std::time(nullptr);
        presence.endTimestamp = std::time(nullptr) + 3600; // Example: 1 hour
        Discord_UpdatePresence(&presence);
    }

    void update() {
        Discord_UpdatePresence(&presence);
    }

private:
    DiscordRichPresence presence;
};
