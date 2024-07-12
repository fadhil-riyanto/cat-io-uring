
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

        pagesz is default page size defined by memory
    */
    int pagesz = getpagesize();
    int op_open_fd = open("lg4096.txt", O_RDONLY);
    f_sz = file_size(op_open_fd);

    char* charptr;

    /* how mmap(2) works
    *   null : start address by kernel
    * len: how many memory need?
    * fd: which fd we shoud map?
    * offset: byte(s) offset in file, example
    *
    * a contain 1 bytes, so 4098 a contain  4098, we need to print
    * bc, which located at bytes 4097 to 4098, len is 2
    * then, set offset to 4096, it will read 4097, 4098 and copy the buf
    * to the charptr
    *
    */
    charptr = mmap(NULL, f_sz - 4096, PROT_READ, MAP_SHARED | MAP_POPULATE, 
                    op_open_fd, 4096);
    // offsetset(op_open_fd);
    

    char* buf = malloc(sizeof(char) * 10); // 7 unused
    read(op_open_fd, buf, f_sz);
    write(1, buf, f_sz);

    close(op_open_fd);
}