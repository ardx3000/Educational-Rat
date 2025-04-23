#ifndef SERVERNETWORK_HPP
#define SERVERNETWORK_HPP

#include <iostream>
#include <WinSock2.h>
#include <fstream>

#pragma comment(lib, "ws2_32.lib")

class ServerNetwork {
    public:
        ServerNetwork(int port);
        ~ServerNetwork();

        bool startServer();
        SOCKET acceptClient();
        bool sendData(SOCKET clientSocket, const std::string& data);
        std::string receiveData(SOCKET clientSocket);
        bool receiveFile(SOCKET clientSocket, const std::string& savePath);

    private:
        int serverPort;
        SOCKET serverSocket;

};

#endif // SERVERNETWORK_HPP