#include <linux/io_uring.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cat_io_uring.h"
#include "io_uring_syscall.c"



static int init_io_uring(submitter_t *submitter)
{
        /* copy the reference from malloc() */
        struct app_io_uring_sqe_ring sqe_ring = submitter->app_io_uring_sqe_ring;
        struct app_io_uring_cqe_ring cqu_ring = submitter->app_io_uring_cqe_ring;

        /*
                reference:
                struct io_uring_params {
                        __u32 sq_entries;
                        __u32 cq_entries;
                        __u32 flags;
                        __u32 sq_thread_cpu;
                        __u32 sq_thread_idle;
                        __u32 resv[5];
                        struct io_sqring_offsets sq_off;
                        struct io_cqring_offsets cq_off;
                };
        */
        struct io_uring_params io_params;
        void *sqe_ptr, *cqe_ptr;

        


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