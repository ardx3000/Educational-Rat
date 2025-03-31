#include "../lib/ClientNetwork.hpp"

ClientNetwork::ClientNetwork(const std::string& serverIP, int serverPort) : serverIP(serverIP), serverPort(serverPort), clientSocket(INVALID_SOCKET) {
    
    WSADATA wsaData;
    
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed ! " << WSAGetLastError() << std::endl;
        return;
    }
}

ClientNetwork::~ClientNetwork() {
    if(clientSocket != INVALID_SOCKET) {
        closesocket(clientSocket);
    }
    WSACleanup();
}

bool ClientNetwork::connectToServer() {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socked creation failed ! " << WSAGetLastError() << std::endl;
        return false; 
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);
    serverAddress.sin_addr.s_addr = inet_addr(serverIP.c_str());

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Connection failed !  " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        return false;
    }

    std::cout << "Connected to server at: " << serverIP << ":" << serverPort << std::endl;
    return true;
}

bool ClientNetwork::sendData(const std::string& data) {
        //TODO AES encryption before sending the data! 
        int result = send(clientSocket, data.c_str(), data.size(), 0);
        if (result == SOCKET_ERROR) {
            std::cerr << "From clinetSend failed ! " << WSAGetLastError() << std::endl;
            return false;
        }
        return true;
}

bool ClientNetwork::sendFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open the file: " << filePath << "!\n";
        return false;
    }

    //Send file
    char buffer[1024];
    while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0) {
        send (clientSocket, buffer, file.gcount(), 0);
    }
    
    //Send EOF
    send(clientSocket, "EOF", 3, 0);
    file.close();
    return true;
}

std::string ClientNetwork::receiveData() {
    char buffer[1024];
    int result = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (result == SOCKET_ERROR) {
        std::cerr << "Receive failed: " << WSAGetLastError() << std::endl;
        return "";
    }
    return std::string(buffer, result);
}