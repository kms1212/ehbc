#ifndef __IO_DISK_H__
#define __IO_DISK_H__

#include <stdio.h>
#include <stdlib.h>

enum io_disk_type {
    IO_DISK_IMAGE,
    IO_DISK_RAMDISK,
};

struct io_disk {
    char* path;
    FILE* file;
    enum io_disk_type type;

    bool input;
    bool output;

    size_t sectorcnt;
    size_t sectorsize;
};

struct io_dev_disk* io_disk_init(char* path, enum io_disk_type type,
    bool input, bool output);
int io_disk_deinit(struct io_dev_disk* dev);

size_t io_disk_write(struct io_dev_disk* dev,
    char* buf, size_t lba, size_t blkcnt);

size_t io_disk_read(struct io_dev_disk* dev,
    char* buf, size_t lba, size_t blkcnt);

#endif  // __IO_DISK_H__
