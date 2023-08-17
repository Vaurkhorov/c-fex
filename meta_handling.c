#include "meta_handling.h"
#include <stdint.h>
#include <stdio.h>

#define SUPERBLOCK_START_OFFSET 1024


int read_from_super(int offset, int size, FILE *drive) {
    int value;

    fseek(drive, (SUPERBLOCK_START_OFFSET + offset), SEEK_SET);
    fread(&value, size, 1, drive);

    return value;
}

int get_inode_count(FILE *drive) {
    return read_from_super(0x0, sizeof(uint32_t), drive);
}


int get_inode_size(FILE *drive) {
    return read_from_super(0x58, sizeof(uint32_t), drive); // TODO!!
}    


int get_block_size(FILE *drive) {
    int block_size_exponent = read_from_super(0x18, sizeof(uint32_t), drive);
    int block_size = 1024;

    while (block_size_exponent--) {
        block_size *= 2;
    }

    return block_size;
}


int get_block_count(FILE *drive) {
    return read_from_super(0x4, sizeof(uint32_t), drive);
}
