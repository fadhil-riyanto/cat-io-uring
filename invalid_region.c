#include <stdlib.h>
#define MEMBLK_SIZE 1025

void change(void **p) {
        void *rand;
        *p = rand;
}

int main() {
        void *buf;
        if (posix_memalign(buf, MEMBLK_SIZE, MEMBLK_SIZE)) {

        }
        return 0;
}