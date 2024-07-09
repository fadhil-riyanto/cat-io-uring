#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/fs.h>

#define BLOCK_SZ    4096

struct runtime {
        int cur_op_fd;
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

static int read_and_print(char *filename, struct runtime *runtime) {
        
        runtime->cur_op_fd = open(filename, O_RDONLY);
        if (runtime->cur_op_fd < 0) {
                perror("open");
                return -1;
        } 
        off_t file_size = file_get_size(runtime);
        off_t bytes_remaining = file_size;

        int blocks = (int) file_size / BLOCK_SZ; // cast
        if (file_size % BLOCK_SZ) 
                blocks++;

        printf("block generated %d\n", blocks);

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