#ifndef CLIENTNETWORK_HPP
#define CLIENTNETWORK_HPP

#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

class ClientNetwork {
    public:
        ClientNetwork(const std::string& serverIp, int serverPort);
        ~ClientNetwork();

        bool connectToServer();
        bool sendData(const std::string& data);
        std::string receiveData();

    private:
        std:: string serverIP;
        int serverPort;
        SOCKET clientSocket;
    };


#endif // CLIENTNETWORK_HPP