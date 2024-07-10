/*
        described in https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/arch/x86/entry/syscalls/syscall_64.tbl

        425	common	io_uring_setup		sys_io_uring_setup
        426	common	io_uring_enter		sys_io_uring_enter
        427	common	io_uring_register	sys_io_uring_register
*/

#include <unistd.h>
#include <linux/io_uring.h>
#include <linux/types.h>

/* ref: https://stackoverflow.com/questions/7218220/c-u32-type-header */

int io_uring_setup(__u32 entry, struct io_uring_params *p) 
{
        int fd = syscall(425, entry, p);
        return fd;
}