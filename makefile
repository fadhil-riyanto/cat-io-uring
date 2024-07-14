CFLAGS = -g -O0 -fsanitize=address


clean:
	rm *.o

cat_sync: cat_syncthread.c
	gcc $? -o $@ ${CFLAGS}

cat_io_uring.c syscall.c:
	gcc $@ -o ${@}.o -c

cat_io_uring: cat_io_uring.o syscall.o
	gcc $? -o $@ ${CFLAGS} ${USEASAN}

block_memory_alg: block_memory.c
	gcc $? -o $@ ${CFLAGS}

gen_getpid_asm: syscall_rev.c 
	gcc $? -S -O0 -fno-asynchronous-unwind-tables