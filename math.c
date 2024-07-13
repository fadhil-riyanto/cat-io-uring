#include <stdio.h>
int main() 
{
        int file_sz = 12000;
        int block = 4096;

        int z = (int) file_sz / block;
        // if (z )
        printf("%d\n", z);
}