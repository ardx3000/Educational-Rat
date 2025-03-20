#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <string>

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
