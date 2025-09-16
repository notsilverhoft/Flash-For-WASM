#include <fstream>
#include <vector>
#include <cstdint>
#include <iostream>
#include <zlib.h>
#include <lzma.h>
#include "decom.h"
#include "header.h"

std::vector<uint8_t> decompressSWF(std::string swfFile, std::size_t fileSize, int compAlg ) { //File size of decompressed file

    std::fstream file(swfFile, std::ios::binary | std::ios::in);
    std::vector<uint8_t> buffer(fileSize);
    

    if (compAlg == 1) { // Zlib Decompression

        file.seekg(0, std::ios::end);
        std::size_t compSize = static_cast<std::size_t>(file.tellg()) - 8;
        std::vector<uint8_t> compBuffer(compSize);

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

    } else if (compAlg == 2) { // LZMA Compression

        file.seekg(0, std::ios::end);
        std::size_t compSize = static_cast<std::size_t>(file.tellg()) - 17;
        std::vector<uint8_t> compBuffer(compSize);

        std::size_t outputSize = fileSize - 17;
        file.seekg(17);
        file.read(reinterpret_cast<char*>(compBuffer.data()), compSize);

        if (!file) {

            std::cout << "Error: Something happend when reading file, please try again!\n";

            return {};

        }

        std::vector<uint8_t> options = getLzmaOptions(swfFile);
        uint32_t dictSize = getDictSize(swfFile);
        lzma_options_lzma opt = {};

        opt.lc = options[0];
        opt.lp = options[1];
        opt.pb = options[2];
        opt.dict_size = dictSize;

        lzma_filter filters[2];
        filters[0].id = LZMA_FILTER_LZMA1;
        filters[0].options = &opt;
        filters[1].id = LZMA_VLI_UNKNOWN;

        lzma_stream strm = LZMA_STREAM_INIT;
        if (lzma_raw_decoder(&strm, filters) != LZMA_OK) {

            throw std::runtime_error("Failed to start decompression! Please try again. If issue persists, please make an issue on GitHub\n");
            return {};
        }
        strm.next_in = compBuffer.data();
        strm.avail_in = compSize;

        strm.next_out = buffer.data();
        strm.avail_out = outputSize;

        lzma_ret decomp = lzma_code(&strm, LZMA_FINISH);
        if (decomp != LZMA_STREAM_END && strm.total_out != outputSize) {
            
            throw std::runtime_error("Decompression failed! Please try again. If issue persists, please make an issue on GitHub\n");
            return {};

        }
        lzma_end(&strm);
        return buffer;

    } 
    
    else {

        std::cout << "Not Supported Yet!\n";

        return {};

    }


}