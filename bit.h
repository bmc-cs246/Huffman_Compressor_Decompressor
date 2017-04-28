#ifndef BITTER
#define BITTER

#include "huff_tree.h"

void feed_buf(encoding_record enc);

int get_buf_byte();

int buf_flush();

#endif
