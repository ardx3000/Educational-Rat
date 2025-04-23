#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <string>
#include <fstream>
#include <iostream>

class FileHandler {
    public:
        FileHandler(const std::string& filenmame);

        void writeFile(const std::string& data);
        std::string readFile();
        void clearFile();
        void fileExistance();

    private:
        std::string filename;
};


#endif // FILEHANDLER_HPP
