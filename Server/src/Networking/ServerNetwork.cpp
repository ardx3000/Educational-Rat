#include "../lib/Networking/ServerNetwork.hpp"

ServerNetwork::ServerNetwork(int port) : serverPort(port), serverSocket(INVALID_SOCKET) {

    WSADATA wsaData;
    
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed ! " << WSAGetLastError() << std::endl;
        return;
    }
}

ServerNetwork::~ServerNetwork() {
    if (serverSocket != INVALID_SOCKET) {
        closesocket(serverSocket);
    }
    WSACleanup();
}

bool ServerNetwork::startServer() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socked creation failed ! " << WSAGetLastError() << std::endl;
        return false; 
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY; // Accept connections forom any IP. Change to accept connection from a set of addresess stored in a data struct. Since this is a security problem.
    serverAddress.sin_port = htons(serverPort);
    
    //bind socket to port
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Bind failed ! " << WSAGetLastError() << std::endl;
        return false;
    }
    
    
    //listen for inc connections
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed ! " << WSAGetLastError() << std::endl;
        return false;
    }

    std::cout << "Server started on port " << serverPort << std::endl;
    return true;
}

SOCKET ServerNetwork::acceptClient() {
    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);
    SOCKET clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Accept failed ! " << WSAGetLastError() << std::endl;
        return INVALID_SOCKET;
    }

    std::cout << "Client connected!" << std::endl;
    return clientSocket;
}

bool ServerNetwork::sendData (SOCKET clientSocket, const std::string& data) {
    //TODO AES encryption before sending the data! 
    int result = send(clientSocket, data.c_str(), data.size(), 0);
    if (result == SOCKET_ERROR) {
        std::cerr << "Send failed ! " << WSAGetLastError() << std::endl;
        return false;
    }
    return true;
}

std::string ServerNetwork::receiveData(SOCKET clientSocket) {
    char buffer[1024];
    int result = recv(clientSocket, buffer, sizeof(buffer), 0);
    //TODO AES decryption after the data is received!
    if (result == SOCKET_ERROR) {
        std::cerr << "Receive failed ! " << WSAGetLastError() << std::endl;
        return "";
    }
    return std::string(buffer, result);
}

bool ServerNetwork::receiveFile(SOCKET clientSocket, const std::string& savePath) {
    std::ofstream file (savePath, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to create file: " << savePath << "!\n";
        return false;
    }

    char buffer[1024];
    int bytesReceived;
    while ((bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        // Check for EOF
        if (bytesReceived == 3 && std::string(buffer, 3) == "EOF") {
            break;
        }
        file.write(buffer, bytesReceived);
    } 
    file.close();
    return true;
}