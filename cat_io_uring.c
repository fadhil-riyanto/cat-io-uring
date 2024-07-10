#include <stdio.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "ups, usage: <filename>\n");
        return 1;
    }
}