#include <stdio.h>
#include <stdint.h>

int main()
{
        /* crop least significant 16 bit integer to 8 bit integer*/

        uint16_t mask = 0xff;           // aka 0000000011111111
        uint16_t target = 0xa66d;       // aka 1010011001101101 (crop 8 first byte using & operator)

        uint8_t res = mask & target;
        

        /*      res: 109 aka 0x01101101
                target: 0x1010011001101101
                extracted: 01101101
        */
        printf("res: %s", (0x6d == res) ? "1" : "0");
}