#include"../lib/ClientNetwork.hpp"
#include <iostream>

int main() {
    std::cout << "Client working " << std::endl;
    
    ClientNetwork client("127.0.0.1", 1234);

    if (!client.connectToServer()) {
        std::cerr << "Failed to connect to server." << std::endl;
        return 1; 
    }

    client.sendData("I am the Client ! ");
    std::string response = client.receiveData();

    std::cout << "FROM(SERVER):" << response << std::endl;

    std::cin.get();

    return 0;
}

