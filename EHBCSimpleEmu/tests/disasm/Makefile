CC=gcc
CFLAGS=-I../../include -std=c99

TARGET=disasm

SOURCES= \
	disasm.c \
	$(wildcard ../../src/cpu/mc68030/*.c)

all: build

clean:
	rm $(TARGET)

build: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^