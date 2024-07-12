#ifndef SYSCALL_H
#define SYSCALL_H

#include <unistd.h>
#include <linux/io_uring.h>
#include <linux/types.h>

int io_uring_setup(__u32 entry, struct io_uring_params *p);

#endif