#include "logging.hpp"

void log(const string& msg, bool endl) {
    cout << BOLDCYAN << "[LOG] " << RESET << msg;
    if (endl) cout << std::endl;
    else cout << '\n';
}

void error(const string& msg, bool endl) {
    cout << BOLDRED << "[ERROR] " << RESET << msg;
    if (endl) cout << std::endl;
    else cout << '\n';
}

void warning(const string& msg, bool endl) {
    cout << BOLDYELLOW << "[WARNING] " << RESET << msg;
    if (endl) cout << std::endl;
    else cout << '\n';
}

void info(const string& msg, bool endl) {
    cout << BOLDBLUE << "[INFO] " << RESET << msg;
    if (endl) cout << std::endl;
    //else cout << '\n';
}

void debug(const string& msg, bool endl) {
    cout << BOLDMAGENTA << "[DEBUG] " << RESET << msg;
    if (endl) cout << std::endl;
    else cout << '\n';
}
