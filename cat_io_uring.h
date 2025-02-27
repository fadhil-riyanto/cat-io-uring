#ifndef CAT_IO_URING_H
#define CAT_IO_URING_H

#include <sys/uio.h>
#include <linux/io_uring.h>

/*
        SQE : Submission Queue Event, the application submit SQE
        CQE: Completion Queue Event, kernel return in any order
*/

/* warning: https://i.sstatic.net/v8efq.png */

/* https://github.com/torvalds/linux/blob/34afb82a3c67f869267a26f593b6f8fc6bf35905/include/uapi/linux/io_uring.h#L462C1-L473C1 */
struct app_io_uring_sqe_ring {
        unsigned int *head;
        unsigned int *tail;
	unsigned int *ring_mask;
	unsigned int *ring_entries;
	unsigned int *flags;
	unsigned int *dropped;
	unsigned int *array;
};


/* https://github.com/torvalds/linux/blob/34afb82a3c67f869267a26f593b6f8fc6bf35905/include/uapi/linux/io_uring.h#L481 */
struct app_io_uring_cqe_ring {
        unsigned int *head;
	unsigned int *tail;
	unsigned int *ring_mask;
	unsigned int *ring_entries;
	unsigned int *overflow;
	unsigned int *cqes;
	unsigned int *flags;
	unsigned int *resv1;
	__u64 user_addr;

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

struct cleanup_addr {
	/* cleaning its initializer
	* cleaning the child buf
	*/
	struct iovec **iovecs; // iovecs arr
	struct iovec *iovecs_alt; // iovecs arr
	struct iovec *iovec; // iovecs head addr
	struct iovec_prop *iovec_prop;
	int iovecs_size;
};

/* sorry I forgot about abstraction layer
 iovecs loses its size while entering kernel, so in the cq
 we dont know what size is
*/

struct iovec_prop {
	struct iovec *iovecs;
	int iovecs_size;
};

#endif