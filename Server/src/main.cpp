#include"../lib/ServerNetwork.hpp"
#include <iostream>

int main() {
    std::cout << "Server working " << std::endl;

    ServerNetwork server(1234);
    if (!server.startServer()) {
        std::cerr << "Failed to start server ! " << std::endl;
        return 1;
    }
    
    SOCKET clientSocket = server.acceptClient();
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Failed to accept client ! " << std::endl;
        return 1;
    }

    std::string receivedData = server.receiveData(clientSocket);
    std::cout << "FROM(CLIENT): " << receivedData << std::endl;

    server.sendData(clientSocket, "From server ! ");

    closesocket(clientSocket);

    std::cin.get();

    return 0;
}