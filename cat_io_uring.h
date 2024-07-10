#ifndef CAT_IO_URING_H
#define CAT_IO_URING_H

#include <sys/types.h>
typedef struct submitter {
    int ring_fd;
} submitter_t;

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

#endif