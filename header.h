#include <cstdint>
#include <string>
#include <vector>

uint8_t getCompressionFromFile(std::string swfFile); //Just in case...
int isCompressed(std::string swfFile);
bool isAFile(std::string swfFile);
int getSWFVersion(std::string swfFile);
uint32_t getFileLength(std::string swfFile);
uint32_t getCompressedLength(std::string swfFile);
std::vector<uint8_t> getLzmaOptions(std::string swfFile);
uint32_t getDictSize(std::string swfFile);
std::vector<uint8_t> fileToVector(std::string swfFile);