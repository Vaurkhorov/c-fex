#include "meta_handling.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>


void clear_buffer();

enum device_id {
    nvme,
    sd,
};


int main() {
    enum device_id device;

    while (1) {
        printf("fex> ");

        char *menu_input;
        size_t input_length = 5;

        getline(&menu_input, &input_length, stdin);
        // fgets(menu_input, 5, stdin);
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


    char nvme_path[] = "/dev/nvme0n1p1";
    nvme_path[13] = '9';
    char sd_path[] = "/dev/sda1";


    FILE* drive = fopen(nvme_path, "rb");
    if (drive == NULL) {
        perror("File did not open.");

        return 1;
    }



    printf("Number of inodes = %d\n", get_inode_count(drive));
    printf("Number of blocks = %d\n", get_block_count(drive));
    printf("Inode size = %d\n", get_inode_size(drive));
    printf("Size of blocks = %d bytes\n", get_block_size(drive));

    fclose(drive);

    return 0;
}

void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
