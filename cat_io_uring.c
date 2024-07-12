
#include <linux/io_uring.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cat_io_uring.h"
#include "syscall.h"

#define QUEUE_DEPTH 1 /* must be power of 2 */

/*
        refence for submission queue entry, here https://kernel.dk/io_uring.pdf

        struct io_uring_sqe {
                __u8 opcode;                  // opcode field that describes the operation code, example: IORING_OP_READV
                __u8 flags;                   // flags contains modifier flags
                __u16 ioprio;                 // ioprio is the priority of this request, see ioprio_set(2)
                __s32 fd;                     // fd is the file descriptor associated with the request
                __u64 off;                    // off holds the offset at which the operation should take place
                __u64 addr;                   // addr contains the address at which the operation should perform IO, if the op-code describes an operation that transfers data. If the
                                              // operation is a vectored read/write of some sort, this will be a pointer 
                                              // to an struct iovec array, as used by preadv(2), for
                                              // example. For a non-vectored IO transfer,
                                              // addr must contain the address directly
                __u32 len;                    // This carries into len, which is either a byte count for a non-vectored IO 
                                              // transfer, or a number of vectors described by
                                              // addr for a vectored IO transfer
                union {
                        __kernel_rwf_t rw_flags;        // Next follows a union of flags that are specific to the op-code
                        __u32 fsync_flags;
                        __u16 poll_events;
                        __u32 sync_range_flags;
                        __u32 msg_flags;
                };
                __u64 user_data;                        // untouched by the kernel
                union {
                        __u16 buf_index;                // buf_index will be described in the advanced use cases section
                        __u64 __pad2[3];       // unused, for future and padding in 64
                };
        };
*/

static int init_io_uring(submitter_t *submitter)
{
        short ret;

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
                        struct io_sqring_offsets sq_off; // https://gist.github.com/fadhil-riyanto/35083851fea9b044f28a887dd8801653#file-io_uring-h
                        struct io_cqring_offsets cq_off; // https://github.com/torvalds/linux/blob/34afb82a3c67f869267a26f593b6f8fc6bf35905/include/uapi/linux/io_uring.h#L481
                };
        */
        struct io_uring_params io_params;
        void *sqe_ptr, *cqe_ptr;

        memset(&io_params, 0, sizeof(struct io_uring_params));

        /* if this syscall are success, sq_off and cq_off will be returned */
        ret = io_uring_setup(QUEUE_DEPTH, &io_params);
        if (ret < 0) {
                perror("sys_io_uring_setup");
        }

        printf("io_uring fd: %d", ret);

        // calculate sqe, cqe from buildin struct

        /* important note
        *       sq_entries : filled by kernel, used to define how many sqe entry this ring support
        *       cq_entries : tell how big CQ ring is
        */
        int sqe_ring_size = io_params.sq_off.array + io_params.sq_entries * sizeof(unsigned);
        int cqe_ring_size = io_params.cq_off.cqes + io_params.cq_entries * sizeof(struct io_uring_cqe);
        

        // assert(io_params.features & IORING_FEAT_SINGLE_MMAP);
        // printf("done");

        if (io_params.features & IORING_FEAT_SINGLE_MMAP) {
                printf("IORING_FEAT_SINGLE_MMAP is set\n");
                if (cqe_ring_size > sqe_ring_size) 
                        sqe_ring_size = cqe_ring_size;

                cqe_ring_size = sqe_ring_size;
        }

        /* allocate memory on sqe */

        return 0;
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

        init_io_uring(submit);
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