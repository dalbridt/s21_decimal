#include "s21_decimal.h"

int get_bit(int src, int index){
    int mask = 1 << index; 
    int ret = (src & mask)== 0? 0: 1; 

    return ret; 
}

