#include <cstdint>
#include <string>
#include <vector>
#include <utility>

uint8_t getCompressionFromFile(std::string swfFile); //Just in case...
int isCompressed(std::string swfFile);
bool isAFile(std::string swfFile);
int getSWFVersion(std::string swfFile);
uint32_t getFileLength(std::string swfFile);
uint32_t getCompressedLength(std::string swfFile);
std::vector<uint8_t> getLzmaOptions(std::string swfFile);
uint32_t getDictSize(std::string swfFile);
std::vector<uint8_t> fileToVector(std::string swfFile);
int getFrameBitSize(std::vector<uint8_t> swfFile); //For Debugging...
std::vector<int> getFrameCoords(std::vector<uint8_t> swfFile);
std::vector<float> getFrameRate(std::vector<uint8_t> swfFile);
std::vector<std::pair<uint16_t, int>> getFrameCount(std::vector<uint8_t> swfFile, float startingByte);