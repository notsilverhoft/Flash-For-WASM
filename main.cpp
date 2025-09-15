#include <iostream>
#include <string>
#include <cstdint>
#include "header.h"
#include "main.h"
#include "decom.h"

int main(int argc, char* argv[]) {

    if (argc > 1) {

        std::string inputFile(argv[1]);

        if (isAFile(inputFile)) {
            
            play(inputFile);

            return 0;

        } else {

            std::cout << "Invalid file or file is empty! Please try again with another file.\n";

        }
    } else {

        std::cout << "Usage: ./main <Swf file>\n";

    }
}

void play(std::string swfFile) {

    int compression = isCompressed(swfFile);
    int version = getSWFVersion(swfFile);
    uint32_t fileSizeUint = getFileLength(swfFile);
    uint32_t compressedSize;
    size_t fileSize = static_cast<size_t>(fileSizeUint);
    if (compression == 2) {

        compressedSize = getCompressedLength(swfFile);

    }
    switch(compression) {

        case 0:
            std::cout << "File is uncompressed... Continue.\n";
            break;
        case 1:
            std::cout << "File is compressed with Zlib... Decompressing...\n";
            decompressSWF(swfFile, fileSize, 1);
            break;
        case 2:
            std::cout << "File is compressed with Lzma... Unsupported...\n";
            break;
        default:
            std::cout << "Bad compression, use another file, or try again.\n";
            return;

    }
    

}