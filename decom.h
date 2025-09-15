#include <vector>
#include <cstdint>
#include <iostream>

std::vector<uint8_t> decompressSWF(std::string swfFile, std::size_t fileSize, int compAlg);