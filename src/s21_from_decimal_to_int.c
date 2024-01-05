#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst){
    if(dst == NULL){
        return 1; 
    } 
    *dst = src.bits[0];

    if(src.bits[3] & (1 << 31)){
        *dst = -1 * (*dst);
    }
    return 0; 
}