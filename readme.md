<a href="https://www.gnu.org/software/coreutils/manual/coreutils.html#cat-invocation">cat</a> but using <a href="https://kernel.dk/io_uring.pdf">io_uring</a>
--
warn: experimental package, use at your own risk

---

introduction
-
this repository is a clone of the cat *nix command but made it myself.
used to know how io_uring works, and some posix function

compile instruction:
```sh
make cat_io_uring
```

if you see something unexpected:
```sh
make clean && make cat_io_uring
```

debug
-
- using default Address Sanitizer (ASan)<br>
append this on CFLAGS 
  ```sh
  -fsanitize=address
  ```

- using valgrind
 ```sh
 valgrind --leak-check=full \
 --show-leak-kinds=all \
 --track-origins=yes \
 --verbose \
 ./cat_io_uring something.txt
 ```

- gdb
 if you found something crash, run program with gdb, example 

 ```sh
 gdb ./cat_io_uring
 > r something.txt
 > bt
 ```
 its will tell you where the program crash

tested operating system:
Arch Linux

uname -a:
```Linux integral2 6.9.6-arch1-1 #1 SMP PREEMPT_DYNAMIC Fri, 21 Jun 2024 19:49:19 +0000 x86_64 GNU/Linux```

license: MIT