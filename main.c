#include "meta_handling.h"



int main() {
    enum device_id device = menu_get_device_id();

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

