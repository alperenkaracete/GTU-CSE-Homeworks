#include <cstdint>

typedef struct SuperBlock {
    float blockSize;  // Size of each block.
    uint16_t countOfBlocks;          // Total number of blocks in the file system.
    uint16_t rootDirectoryPosition; // Position of the root directory in blocks.
    uint8_t  bitMap[512]; //Bitmap is for track of free blocks.
    // Constructor 
    SuperBlock(float blockSize, uint16_t countOfBlocks, uint16_t rootDirectoryPosition)
        : blockSize(blockSize), countOfBlocks(countOfBlocks), rootDirectoryPosition(rootDirectoryPosition) {
       int length = sizeof(bitMap);     
       for (int i = 0; i < length; ++i) {
            bitMap[i] = 0;  //Initialize all elements of bitMap to 0
        }
    }
}__attribute__((packed)) SuperBlock;

void printSuperBlock(const SuperBlock& superBlock, std::ofstream& file) {

}
