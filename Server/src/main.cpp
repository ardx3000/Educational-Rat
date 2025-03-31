#include"../lib/ServerNetwork.hpp"
#include <iostream>

int main() {
    std::cout << "Server working " << std::endl;

    ServerNetwork server(1234);
    if (!server.startServer()) {
        std::cerr << "Failed to start server ! " << std::endl;
        return 1;
    }
    
    while (true) {
        std::cout << "Waiting for a client to connect..." << std::endl;
        SOCKET clientSocket = server.acceptClient();
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Failed to accept client!" << std::endl;
            continue;
        }

        std::cout << "Client connected!" << std::endl;

        while (true) {
            std::string receivedData = server.receiveData(clientSocket);

            if (receivedData.empty()){
                std::cout << "Client disconnected.\n";
                break;
            }

            std::cout << "FROM CLIENT: " << receivedData << std::endl;

            if (receivedData == "SEND_FILE") {
                std::cout << "Receiving file..." << std::endl;
                if (server.receiveFile(clientSocket, "received.txt")) {
                    std::cout << "File received successfully!\n";
                } 
                else {
                    std::cerr << "File transfer failed.\n";
                }
            } 
            else {
                server.sendData(clientSocket, "Message received!");
            }
        }
        closesocket(clientSocket);
    }

    return 0;
}