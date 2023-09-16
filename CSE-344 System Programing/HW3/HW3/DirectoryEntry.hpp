#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <ctime>

typedef struct DirectoryEntry {
    char filename[8];
    char extension[3];
    uint8_t Reserved[10];
    uint8_t attributes; //00000001 read only, 00000010 archived, 00000100 hidden, 00010000 system bit
    uint16_t lastModificationTime;
    uint16_t lastModificationDate;
    uint16_t firstBlock;
    uint32_t size;

    DirectoryEntry(const std::string& filename, const std::string& extension,uint8_t attributes,uint16_t firstBlock, uint32_t size) {
        strncpy(this->filename, filename.c_str(), 8);
        strncpy(this->extension, extension.c_str(), 3);
        this->attributes = attributes;
        this->firstBlock = firstBlock;
        this->size = size;
    }
}__attribute__((packed)) DirectoryEntry;


