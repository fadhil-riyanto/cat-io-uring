#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <linux/fs.h>

#define BLOCK_SZ    4096

struct runtime {
        int cur_op_fd;
};

/* define vectorized struct for operation readv, writev syscall */

struct io_vector {
        void *io_vector_base;
        size_t io_vector_len;
};

static off_t file_get_size(struct runtime *runtime) 
{
        struct stat st;
        short ret;
        memset(&ret, 0, sizeof(short));

        ret = fstat(runtime->cur_op_fd, &st);
        if (ret < 0) {
                perror("fstat");
                return -1;
        }

        ret = S_ISBLK(st.st_mode);
        
        if (ret) {
                printf("device is block\n");
                unsigned long long bytes;
                if (ioctl(runtime->cur_op_fd,  BLKGETSIZE64, &bytes)) {
                        perror("ioctl");
                        return -1;
                }
                return bytes;
        } else if (S_ISREG(st.st_mode)) {
                printf("normal file detected\n");
                return st.st_size;
        }
        
        return -1;
}

static int reader(struct iovec *io_vectors, off_t *bytes_remaining)
{
        int cur_block = 0;
        
        
        // while (*bytes_remaining) {
        //         printf("remaining byte %llu\n", 
        //                         (unsigned long long)*bytes_remaining);

        //         if (*bytes_remaining < BLOCK_SZ) 
        //                 bytes_to_read = BLOCK_SZ;

        //         bytes_remaining -= bytes_to_read;
        // }
        while (*bytes_remaining) {
                off_t bytes_to_read = *bytes_remaining;

                if (*bytes_remaining > BLOCK_SZ) 
                        bytes_to_read = BLOCK_SZ;

                void *buf;
                if (posix_memalign(&buf, BLOCK_SZ, BLOCK_SZ)) {
                        perror("memalign");
                        return -1;
                }

                io_vectors[cur_block].iov_base = buf;
                io_vectors[cur_block].iov_len = bytes_to_read;
                printf("start block : %llu\n", (unsigned long long)bytes_to_read);
                cur_block++;

                *bytes_remaining -= bytes_to_read;
        }

        return 0; /* debug here */
}

static int read_and_print(char *filename, struct runtime *runtime) {
        short ret = 0;

        struct iovec *io_vectors;
        runtime->cur_op_fd = open(filename, O_RDONLY);
        if (runtime->cur_op_fd < 0) {
                perror("open");
                return -1;
        } 
        off_t file_size = file_get_size(runtime);
        off_t bytes_remaining = file_size;
        printf("filesize from st.size | ioctl res: %llu\n", (unsigned long long)file_size);

        int blocks = (int) file_size / BLOCK_SZ; // cast
        if (file_size % BLOCK_SZ) 
                blocks++;

        printf("block generated %d\n", blocks);
        
        io_vectors = (struct iovec*)malloc(sizeof(struct io_vector) * blocks);
        ret = reader(io_vectors, &bytes_remaining);

        if (ret != 0) {
                perror("error");
                return -1;
        }
        readv(runtime->cur_op_fd, io_vectors, blocks);
        for (int i = 0; i < blocks; i++) {
                write(1, io_vectors[i].iov_base, io_vectors[i].iov_len);
        }
        write(1, "\n\0", 2);

        return 0;
}


static inline void __debug_argv(int len, char** argc) 
{
    for(int i = 0; i < len; i++) {
        printf("debug[%d]: %s\n", i, argc[i]);
    }
}

int __main(char* filename) {
        struct runtime runtime;
        read_and_print(filename, &runtime);
        return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage, ./cat_sync <filename>\n");
        return -1;
    }

    __debug_argv(argc, argv);
    __main(argv[1]);


    return 0;
}