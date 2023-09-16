#include "DirectoryEntry.hpp"
#include "SuperBlock.hpp"
#include <fstream>

using namespace std;

#define KB 1024
#define MAX_FILE_SIZE KB*1024*16
#define MULTIPLY_CONST 4

int createFileSystem(string tempName,float blockSize ,uint16_t *reservedBlocks){

    size_t dotPos = tempName.find('.');
    size_t maximumFat12Size = KB * KB * MULTIPLY_CONST * blockSize;
    size_t remainingBytes = maximumFat12Size - sizeof(struct SuperBlock);
    string filename = tempName.substr(0, dotPos);
    string extension = tempName.substr(dotPos + 1);
    uint16_t countOfBlocks = maximumFat12Size / (blockSize * KB);
    if (blockSize * KB <= 0 || MULTIPLY_CONST * KB * blockSize * KB > MAX_FILE_SIZE || countOfBlocks < 1) {
            
            cout << "File is bigger than Maximum File Size or you have entered wrong block size!" << endl;
            return -1;
    }
    reservedBlocks++; //1 Block is reserving now so increase reserver blocks.
    uint16_t countOfBlocksWithoutSuperBlock = remainingBytes / (blockSize * KB);
    uint16_t reservedSize = *reservedBlocks * blockSize * KB; //Calculate the size of the reserved area in bytes
    uint16_t fatSize = (countOfBlocksWithoutSuperBlock * 12) / 8;
    uint16_t rootDirPosition = reservedSize + fatSize;
    struct SuperBlock superBlock(blockSize,countOfBlocksWithoutSuperBlock,rootDirPosition);
    uint16_t firstBlock = maximumFat12Size - superBlock.countOfBlocks * superBlock.blockSize * KB;
    struct DirectoryEntry DirectoryEntry(filename,extension,0,firstBlock,2 * sizeof(DirectoryEntry));

    ofstream file(tempName);

    if (file.is_open()) {
        // Write data to the file

        vector<char> empty(KB, 0);
        file << "File Infos" << endl;
        file << DirectoryEntry.filename << "."; 
        file << DirectoryEntry.extension << endl;
        for (const auto& reserved : DirectoryEntry.Reserved) {
            file << static_cast<int>(reserved) << " ";
        }
        file << endl;
        file << static_cast<int>(DirectoryEntry.attributes) << endl;
        file << DirectoryEntry.lastModificationTime << endl;
        file << DirectoryEntry.lastModificationDate << endl;
        file << DirectoryEntry.firstBlock << endl;
        file << DirectoryEntry.size << endl;

        file << "Superblock Infos" << endl;
        file << superBlock.blockSize << endl;
        file << superBlock.countOfBlocks << endl;
        file << superBlock.rootDirectoryPosition << endl; 

        
        for (int i = 0; i < blockSize * KB * MULTIPLY_CONST; i++) {
            file.write(&empty[0], empty.size());  // Write the block to the file
        }

        // Close the file
        file.close();

        cout << "File created and written successfully." << endl;
    } else {
        cerr << "Failed to create the file." << endl;
    }

    return 0;

}

int main(int argc,char *argv[]){


    if (argc==3 && !strcmp(argv[0],"./makeFileSystem")){

        float blockSize = atof(argv[1]);
        string tempName = argv[2];
        uint16_t reservedBlocks = 0;
        createFileSystem(tempName,blockSize,&reservedBlocks);
        return 0;
    }

    return -1;
}