#ifndef META_HANDLING_H
#define META_HANDLING_H

#include <bits/types/FILE.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void clear_buffer();

int get_inode_count(FILE*);

int get_inode_size(FILE*);

int get_block_size(FILE*);

int get_block_count(FILE*);

enum device_id {
    nvme,
    sd,
};

enum device_id menu_get_device_id();

#endif
