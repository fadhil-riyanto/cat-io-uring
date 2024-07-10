#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cat_io_uring.h"
#include "io_uring_syscall.c"

static int init_io_uring(submitter_t *submitter)
{

}

static int __main(char *filename) 
{
    // define struct for io_uring base operation
    submitter_t *submit = (submitter_t *)malloc(sizeof(struct submitter));
    if (!submit) {
        perror("alloc submit struct\n");
        return -1;
    }

    memset(submit, 0, sizeof(struct submitter));
    

    return 0;
}

int main(int argc, char **argv) 
{
    if (argc < 2) {
        fprintf(stderr, "ups, usage: <filename>\n");
        return 1;
    }

    return __main(argv[1]);
}