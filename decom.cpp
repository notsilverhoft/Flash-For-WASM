#include <fstream>
#include <vector>
#include <cstdint>
#include <iostream>
#include <zlib.h>
#include "decom.h"

std::vector<uint8_t> decompressSWF(std::string swfFile, std::size_t fileSize, int compAlg ) { //File size of decompressed file

    std::fstream file(swfFile, std::ios::binary | std::ios::in);
    std::vector<uint8_t> buffer(fileSize);
    
    file.seekg(0, std::ios::end);
    std::size_t compSize = static_cast<std::size_t>(file.tellg()) - 8;


    std::vector<uint8_t> compBuffer(compSize);

    if (compAlg == 1) { // Zlib Decompression

        std::size_t outputSize = fileSize - 8;
        file.seekg(8);
        file.read(reinterpret_cast<char*>(compBuffer.data()), compSize);

        if (!file) {

            std::cout << "Error: Something happend when reading file, please try again!\n";

            return {};

        }
        int check = uncompress(buffer.data(), &outputSize, compBuffer.data(), compSize);
        
        if (check != Z_OK) {

            std::cout << "Error: Decompression failed with code: " << check << ". Please try again. If issue persists, please make an issue on GitHub\n";

            return {};

        }
        return buffer;

    } else if (compAlg == 2) {

        

    } 
    
    else {

        std::cout << "Not Supported Yet!\n";

        return {};

    }


}