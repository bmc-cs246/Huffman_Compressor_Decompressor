#include "bit.h"


int buf = 0;
int bits_in_buf = 0;


int bit(int data, int bit) {
  return (data >> bit) & 1;
}

void write_bit_to_buf(int bit) {
  buf = buf | (bit << bits_in_buf);
  bits_in_buf++;
}

int boolean(int in) {
  return !!in;
}

void feed_buf(encoding_record enc) {
  int data = enc.code;
  int bits_remaining = enc.length;
  while (bits_remaining > 0) {
    bits_remaining--;
    int bit_to_write = boolean(data & (1 << bits_remaining));
    write_bit_to_buf(bit_to_write);
  }
}

unsigned char reverse(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

int reverse_byte(int in) {
  int out = 0;
  for(int i = 0; i < 8; i++) {
    out |= ((in >> i) & 1) << (7 - i);
  }
  return out;
}

int get_buf_byte() {
  if (bits_in_buf >= 8) {
    bits_in_buf -= 8;
    int out = reverse_byte(buf & 0xff);
    buf >>= 8;
    return out;
  }
  return -1;
}

int buf_flush() {
  if (bits_in_buf > 0) {
    bits_in_buf = 0;
    return buf & 0xff;
  }
  return -1;
}


