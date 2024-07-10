CFLAGS = -ggdb3 -O0

cat_sync: cat_syncthread.c
	gcc $? -o $@ ${CFLAGS}

cat_io_uring: cat_io_uring.c
	gcc $? -o $@ ${CFLAGS}


block_memory_alg: block_memory.c
	gcc $? -o $@ ${CFLAGS}

