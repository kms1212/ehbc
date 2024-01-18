#!/bin/sh

set -e

qemu-system-m68k -name 030hbc -M none -cpu m68030 -m 128M \
    -monitor stdio -display cocoa -g 640x480 \
    -device loader,file=build/fw.bin,addr=0 
