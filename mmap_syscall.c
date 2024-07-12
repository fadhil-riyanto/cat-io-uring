
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>

/*  goal, copy "bc" to memory using mmap(2), 
    and print the result, free using munmap(2), 
    ignore "a", and "d\n"
    
    mmap() syscall returned by remap_pfn_range
     */

static int file_size(int fd) 
{
    struct stat st;
    short ret;

    ret = fstat(fd, &st);
    return st.st_size;
}

static int offsetset(int fd) 
{
    short ret;

    ret = lseek(fd, 1, SEEK_SET);
    return ret;
}

int main() 
{
    off_t f_sz = 0;

    /* use gdb, dump set breakpoint to line 42, dump variable pagesz
        gef➤  p/d pagesz
        $2 = 4096
    */
    int pagesz = getpagesize();
    int op_open_fd = open("lg4096.txt", O_RDONLY);
    f_sz = file_size(op_open_fd);

    char* charptr;
    charptr = mmap(NULL, f_sz - 1000, PROT_READ, MAP_SHARED | MAP_POPULATE, 
                    op_open_fd, 0);
    // offsetset(op_open_fd);
    

    char* buf = malloc(sizeof(char) * 10); // 7 unused
    read(op_open_fd, buf, f_sz);
    write(1, buf, f_sz);

    close(op_open_fd);
}