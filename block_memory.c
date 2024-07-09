
#include <stdio.h>
#define BLOCK_SZ    4096

/*
 * block memory chunk calculation explained
 *
 * first, divide filesize with wanted chunk size, example
 * if size 1024, chunk size 4096. the result will 0.25, which lower, the cast to int
 * this causes rounding down, make 0.xx treated as 0
 *
 * if the size greather than 4096, example 4097, so the program will return 1.x, which causes
 * to rounding down to 1, because 4096 byte block has been filled, we need one block
 * to achieve this, we need a if else, the if else operand that good is mod operator
 *
 * suppose, 1024 % 4096, its will give 1024, because 1024 / 4096 eq 1/4, which 1/4 * 4096 = 1024
 * then, the value "1024" treated as true by comparator, if the result are 0, the comparator 
 * gives false, the true result, will increment of blocks++ will cause where 
 * 
 * | area of 0 to 4096 | area of 4097 to 8192 | area of 8193 to 11288 | etc
 *                       ^~__ here
 *
 * 4096                | 1                    | void                  | void... etc
 */

int main() {
    unsigned long long size = 4000;
    int blocks = (int) size / BLOCK_SZ;
    printf("%d\n", blocks); // <--- rounding

    if (size % BLOCK_SZ) blocks++;
    printf("%d\n", blocks); // <--- add block, if n mod y are not null (rounding except zero)
    
}