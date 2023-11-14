#ifndef __IO_STREAM_H__
#define __IO_STREAM_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum io_stream_type {
    IO_STREAM_FILE,
    IO_STREAM_GUI,
};

struct io_stream {
    char* path;
    FILE* file;
    enum io_stream_type type;
    bool input;
    bool output;
};

struct io_stream* io_stream_init(
    char* path, enum io_stream_type type,
    bool input, bool output);
int io_stream_deinit(struct io_stream* dev);
size_t io_stream_write(struct io_stream* dev, char* buf, size_t len);
size_t io_stream_read(struct io_stream* dev, char* buf, size_t len);

#endif  // __IO_STREAM_H__
