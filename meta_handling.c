#include "meta_handling.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

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
    return read_from_super(0x58, sizeof(uint32_t), drive);
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

enum device_id menu_get_device_id() {
    enum device_id device;
    
    size_t input_length = 5;
    char *menu_input = (char*)malloc(input_length);
    
    while (1) {
        printf("fex> ");


        getline(&menu_input, &input_length, stdin);
        clear_buffer();

        menu_input[strcspn(menu_input, "\n")] = '\0';

        if (!strcmp(menu_input, "help")) {
            printf(
                "Enter your device identifier.\n"
                "Supported identifiers:\n"
                "nvme - NVMe devices\n"
                "sd - SCSI, SATA, USB etc. devices\n"
            );
        }
        else if (!strcmp(menu_input, "nvme")) {
            device = nvme;
            break;
        }
        else if (!strcmp(menu_input, "sd")) {
            device = sd;
            break;
        }
        else {
            printf("Unknown device = \"%s\"", menu_input);
        }
    }

    free(menu_input);	
    return device;
}

void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
