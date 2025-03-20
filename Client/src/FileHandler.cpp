#include "../lib/FileHandler.hpp"
#include <fstream>
#include <iostream>

FileHandler::FileHandler(const std::string& filename) : filename(filename) {
    fileExistance();
}

void FileHandler::writeFile(const std::string& data) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << data;
        file.close();
    } 
    else {
        std::cerr << "Error: Could not open file for writing!" << std::endl;
    }
} 

std::string FileHandler::readFile() {
    std::ifstream file(filename);
    std::string content , line;
    if (file.is_open()) {
        while(getline(file, line)) {
            content += line + "\n";
        }
        file.close();
    }
    else {
        std::cerr << "Error: Could not open file for reading!" << std::endl;
    }
    return content;
}


void FileHandler::clearFile() {
    std::ofstream file(filename, std::ios::trunc); 
    if (!file.is_open()) {
        std::cerr << "Error: Could not clear file!" << std::endl;
    }
    file.close();
}

void FileHandler::fileExistance() {
    std::ifstream file(filename);
    if (!file.good()) {  
        std::ofstream createFile(filename);
        if (createFile.is_open()) {
            createFile.close();
        } else {
            std::cerr << "Error: Could not create file!" << std::endl;
        }
    }
}