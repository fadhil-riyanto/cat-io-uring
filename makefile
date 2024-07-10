CFLAGS = -ggdb3 -O0

cat_sync: cat_syncthread.c
	gcc $? -o $@ ${CFLAGS}

cat_io_uring: cat_io_uring.c cat_io_uring.h syscall.c
	gcc $? -o $@ ${CFLAGS}


block_memory_alg: block_memory.c
	gcc $? -o $@ ${CFLAGS}

gen_getpid_asm: syscall_rev.c 
	gcc $? -S -O0 -fno-asynchronous-unwind-tables