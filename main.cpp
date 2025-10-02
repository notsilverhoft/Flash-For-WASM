#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <utility>
#include "header.h"
#include "main.h"
#include "decom.h"

int main(int argc, char* argv[]) {

    if (argc > 1) {

        std::string inputFile(argv[1]);
        bool debug(argv[2]); 

        if (isAFile(inputFile)) {
            
            play(inputFile, debug);

            return 0;

        } else {

            std::cout << "Invalid file or file is empty! Please try again with another file.\n";

        }
    } else {

        std::cout << "Usage: ./main <Swf file>\n";

    }
}

void play(std::string swfFile, bool debug = false) {

    int compression = isCompressed(swfFile);
    int version = getSWFVersion(swfFile);
    uint32_t fileSizeUint = getFileLength(swfFile);
    uint32_t compressedSize;
    size_t fileSize = static_cast<size_t>(fileSizeUint);
    if (compression == 2) {

        compressedSize = getCompressedLength(swfFile);

    }
    switch(compression) {

        case 0: {
            std::cout << "File is uncompressed... Continue.\n";
            std::vector<uint8_t> mainSwf = fileToVector(swfFile);

            if( debug ) {

                std::cout << "Debug: First Byte: " << (int)mainSwf[0] << "\n";

            }

            play(mainSwf, debug);

            break;
        }
        case 1: {
            std::cout << "File is compressed with Zlib... Decompressing...\n";
            std::vector<uint8_t> mainSwf = decompressSWF(swfFile, fileSize, 1);

            if( debug ) { 

                std::cout << "Debug: Actual output size:" << fileSize << "\n";
                std::cout << "Debug: Size of decompressed output:" << mainSwf.size() << "\n";
                std::cout << "Debug: First Byte:" << (int)mainSwf[0] << "\n";

            }

            play(mainSwf, debug);

            break;
        }
        case 2: {
            std::cout << "File is compressed with LZMA... Decompressing...\n";
            std::vector<uint8_t> mainSwf = decompressSWF(swfFile, fileSize, 2);

            if( debug ) { 

                std::cout << "Debug: Actual output size:" << fileSize << "\n";
                std::cout << "Debug: Size of decompressed output:" << mainSwf.size() << "\n";
                std::cout << "Debug: First Byte:" << (int)mainSwf[0] << "\n";

            }
            
            play(mainSwf, debug);

            break;
        }
        default: {
            std::cout << "Bad compression, use another file, or try again.\n";
            return;
        }

    }

}
extern "C" void play_c(const char* swfFile, int debug) { //EMScripten Wrapper

    play(std::string(swfFile), debug != 0);

}

void play(std::vector<uint8_t> swfFile, bool debug = false) { //After compression stuff

    std::vector<int> frameCoords = getFrameCoords(swfFile);
    std::vector<float> frameRate = getFrameRate(swfFile);
    std::vector<std::pair<uint16_t, int>> frameCount = getFrameCount(swfFile, frameRate[1]);

    if( debug ) {

        std::cout << "Debug: temp: " << (int)swfFile[0] << "\n";
        int bitSize = getFrameBitSize(swfFile);
        std::cout << "Debug: Frame Bit Size: " << bitSize << "\n";
        std::cout << "Debug: Xmin: " << frameCoords[0] << "\n";
        std::cout << "Debug: Xmax: " << frameCoords[1] << "\n";
        std::cout << "Debug: Ymin: " << frameCoords[2] << "\n";
        std::cout << "Debug: Ymax: " << frameCoords[3] << "\n";
        std::cout << "Debug: Framerate: " << frameRate[0] << "\n";
        std::cout << "Debug: Frame count: " << frameCount[0].first << "\n";

    }
    



}