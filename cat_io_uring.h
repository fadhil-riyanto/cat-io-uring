#ifndef CAT_IO_URING_H
#define CAT_IO_URING_H

#include <sys/uio.h>
#include <linux/io_uring.h>

/*
        SQE : Submission Queue Event, the application submit SQE
        CQE: Completion Queue Event, kernel return in any order
*/

struct app_io_uring_sqe_ring {
        unsigned *head;
};

struct app_io_uring_cqe_ring {
        unsigned *head;
};

struct fileinfo {
    off_t file_sz;  /* obtained from st.file_sz */
    struct iovec iovecs[]; /* readv and writev syscall*/
};

typedef struct submitter {
    int ring_fd;
    struct app_io_uring_sqe_ring app_io_uring_sqe_ring;
    struct io_uring_sqe *sqe_ring;
    struct app_io_uring_cqe_ring app_io_uring_cqe_ring;

} submitter_t;

#endif