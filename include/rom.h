#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>


#define ROM_SIZE 256

std::string readBinFileToHex(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary); // Open in binary mode
    if (!file) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return "";
    }

    std::ostringstream hexStream;
    unsigned char byte;
    
    while (file.read(reinterpret_cast<char*>(&byte), 1)) {
        hexStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }

    return hexStream.str();
}

// Gets hex value of byte at index from hex string
std::string getHexByteAtIndexFromHexString(const std::string& hexString, 
size_t byteIndex) {
    size_t hexPos = byteIndex * 2;


    return hexString.substr(hexPos, 2);
}


class ROM{
    public:
    std::string file;
    ROM(std::string file_path){
        this->file = readBinFileToHex(file_path);
        std::cout << file << std::endl;
    }

    std::string get(int pointer){
        return getHexByteAtIndexFromHexString(file, pointer);
    }
};