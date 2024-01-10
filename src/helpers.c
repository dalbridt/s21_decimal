#include "s21_decimal.h"

int get_bit(int src, int index) {
  int mask = 1 << index;
  int ret = (src & mask) == 0 ? 0 : 1;

  return ret;
}

/*  index 0 - 31 = bits[0]
    index 32 - 63 = bits[1]
    index 64 - 95 = bits[2]
    index 96 - 127 = bits[3]
*/

void set_bit(s21_decimal * src, int index, int value) {
  int arr_index = index / 32; 
  int bit_index = index % 32;
    if(value == 1){
        src->bits[arr_index] |= (1 << bit_index); 
    } else if (value == 0){
        src->bits[arr_index] &= ~(1 << bit_index); 
    }
}

