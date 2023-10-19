#include "pch.hpp"

#include "myshell.hpp"
#include "file/Files.hpp"
#include "app/App.hpp"

#define BUFFER_SIZE 200

namespace Milho {
    
    bool verifyFile();
    void createFile();
    void writeFile();
    void writeFile(std::ofstream& file);
    void readFile();
    void read(std::ifstream& file, int& size, std::string& str);

    int save() {
        if (!verifyFile()) {
            createFile();
        }
        writeFile();
        return 0;
    }

    int load() {
        if (!verifyFile()) {
            GET_APP_INSTANCE.setMOTD(DEFAULT_MOTD);
            GET_APP_INSTANCE.setGoodbye(DEFAULT_GOODBYE);
            createFile();
            return 0;
        }
        readFile();
        return 0;
    }

    bool verifyFile() {
        std::ifstream file(FILE_NAME, std::ios::binary | std::ios::in);
        return file.good();
    }

    void createFile() {
        std::ofstream file(FILE_NAME, std::ios::binary | std::ios::out);
        writeFile(file);
    }

    void writeFile() {
        int size;
        std::ofstream file(FILE_NAME, std::ios::binary | std::ios::out);

        writeFile(file);
    }

    void writeFile(std::ofstream& file) {
        int size;

        size = GET_APP_INSTANCE.getMOTD().size() + 1;
        file.write((char *) &(size), sizeof(int));
        file.write(GET_APP_INSTANCE.getMOTD().c_str(), size);
        
        size = GET_APP_INSTANCE.getGoodbye().size() + 1;
        file.write((char *) &(size), sizeof(int));
        file.write(GET_APP_INSTANCE.getGoodbye().c_str(), size);
    }

    void readFile() {
        std::ifstream file(FILE_NAME, std::ios::binary | std::ios::out);
        std::string str;
        int size;

        file.read((char *) &size, sizeof(int));
        read(file, size, str);
        GET_APP_INSTANCE.setMOTD(str);

        file.read((char *) &size, sizeof(int));
        read(file, size, str);
        GET_APP_INSTANCE.setGoodbye(str);
    }

    void read(std::ifstream& file, int& size, std::string& str) {
        char buffer[BUFFER_SIZE];
        std::stringstream ss;
        int read = 0;
        while (read < size - BUFFER_SIZE + 1) {
            file.read(buffer, BUFFER_SIZE - 1);
            ss << buffer;
            read = BUFFER_SIZE;
        }
        file.read(buffer, size - read);
        ss << buffer;
        str = ss.str();
    }

}