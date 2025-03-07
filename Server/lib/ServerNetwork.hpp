#ifndef SERVERNETWORK_HPP
#define SERVERNETWORK_HPP

#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

class ServerNetwork {
    public:
        ServerNetwork(int port);
        ~ServerNetwork();

        bool startServer();
        SOCKET acceptClient();
        bool sendData(SOCKET clientSocket, const std::string& data);
        std::string receiveData(SOCKET clientSocket);

    private:
        int serverPort;
        SOCKET serverSocket;

};

#endif // SERVERNETWORK_HPP