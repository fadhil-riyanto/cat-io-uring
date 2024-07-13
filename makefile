CFLAGS = -g -O0
CXXFLAGS = -Wall -g

clean:
	rm *.o

cat_sync: cat_syncthread.c
	gcc $? -o $@ ${CFLAGS}

cat_io_uring.c syscall.c:
	gcc $@ -o ${@}.o -c

cat_io_uring: cat_io_uring.o syscall.o
	gcc $? -o $@ ${CFLAGS}

block_memory_alg: block_memory.c
	gcc $? -o $@ ${CFLAGS}

gen_getpid_asm: syscall_rev.c 
	gcc $? -S -O0 -fno-asynchronous-unwind-tables