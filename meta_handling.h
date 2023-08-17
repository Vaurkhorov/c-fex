#ifndef META_HANDLING_H
#define META_HANDLING_H

#include <bits/types/FILE.h>
#include <stdio.h>
#include <stdint.h>


int get_inode_count(FILE*);

int get_inode_size(FILE*);

int get_block_size(FILE*);

int get_block_count(FILE*);


#endif
