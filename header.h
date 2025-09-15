#include <cstdint>
#include <string>

uint8_t getCompressionFromFile(std::string swfFile); //Just in case...
int isCompressed(std::string swfFile);
bool isAFile(std::string swfFile);
int getSWFVersion(std::string swfFile);
uint32_t getFileLength(std::string swfFile);
uint32_t getCompressedLength(std::string swfFile);