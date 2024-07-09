#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/fs.h>

int main()
{
  int fd = open("/dev/sda", O_RDONLY);
  unsigned int soft_block_size = 0, logical_block_size = 0, physical_block_size = 0;
  int rcs = ioctl(fd, BLKBSZGET, &soft_block_size);
  int rcl = ioctl(fd, BLKSSZGET, &logical_block_size);
  int rcp = ioctl(fd, BLKPBSZGET, &physical_block_size);
  printf("Soft block size: %u\n", soft_block_size);
  printf("Logical block size: %u\n", logical_block_size);
  printf("Physical block size: %u\n", physical_block_size);
}