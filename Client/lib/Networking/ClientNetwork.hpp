#ifndef CLIENTNETWORK_HPP
#define CLIENTNETWORK_HPP

#include <iostream>
#include <WinSock2.h>
#include <fstream>

#pragma comment(lib, "ws2_32.lib")

class ClientNetwork {
    public:
        ClientNetwork(const std::string& serverIP, int serverPort);
        ~ClientNetwork();

        bool connectToServer();
        bool sendData(const std::string& data);
        bool sendFile(const std::string& filePath);
        std::string receiveData();

    private:
        std:: string serverIP;
        int serverPort;
        SOCKET clientSocket;
    };


#endif // CLIENTNETWORK_HPP