#ifndef SYSCALL_H
#define SYSCALL_H

#include <unistd.h>
#include <linux/io_uring.h>
#include <linux/types.h>
#include <signal.h>

int io_uring_setup(__u32 entry, struct io_uring_params *p);
int io_uring_enter(unsigned int fd, unsigned int to_submit,
                        unsigned int min_complete, unsigned int flags,
                        sigset_t *sig);

#endif