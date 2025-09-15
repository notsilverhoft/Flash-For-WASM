#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include "header.h"

uint8_t getCompressionFromFile(std::string swfFile) {

    std::ifstream file(swfFile, std::ios::binary);
    uint8_t binOut;
    file.read(reinterpret_cast<char*>(&binOut), 1);

    return binOut;

}
int isCompressed(std::string swfFile) {

    uint8_t headerBin = getCompressionFromFile(swfFile);

    switch(headerBin) {

        case 0x46:
            return 0;
            break; //For my peace of mind...
        case 0x43:
            return 1;
            break;
        case 0x5A:
            return 2;
            break;
        default:
            std::cout << "Not in correct SWF(Shock Wave Flash) format, please use another file!\n";

    }

}
bool isAFile(std::string swfFile) {

    std::ifstream file(swfFile, std::ios::binary);
    uint8_t pH; //Place holder
    file.read(reinterpret_cast<char*>(&pH), 1);

    if (file.good()){

        return true;

    }
    else {

        return false;

    }

}
int getSWFVersion(std::string swfFile) {

    std::ifstream file(swfFile, std::ios::binary);
    uint8_t binOut;
    file.seekg(3);
    file.read(reinterpret_cast<char*>(&binOut), 1);

    return binOut;

}
uint32_t getFileLength(std::string swfFile) {

    std::ifstream file(swfFile, std::ios::binary);
    uint8_t val1;
    uint8_t val2;
    uint8_t val3;
    uint8_t val4;
    uint32_t binOut;

    file.seekg(4);
    file.read(reinterpret_cast<char*>(&val1), 1);
    file.read(reinterpret_cast<char*>(&val2), 1);
    file.read(reinterpret_cast<char*>(&val3), 1);
    file.read(reinterpret_cast<char*>(&val4), 1);

    binOut = val1 + (val2 << 8) + (val3 << 16) + (val4 << 24);

    return binOut;

}
uint32_t getCompressedLength(std::string swfFile) {

    std::ifstream file(swfFile);
    uint8_t val1;
    uint8_t val2;
    uint8_t val3;
    uint8_t val4;
    uint32_t binOut;

    file.seekg(13);
    file.read(reinterpret_cast<char*>(&val1), 1);
    file.read(reinterpret_cast<char*>(&val2), 1);
    file.read(reinterpret_cast<char*>(&val3), 1);
    file.read(reinterpret_cast<char*>(&val4), 1);

    binOut = val1 + (val2 << 8) + (val3 << 16) + (val4 << 24);

    return binOut;

}
