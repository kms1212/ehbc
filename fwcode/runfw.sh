#!/bin/bash

qemu-system-m68k -M none -cpu m68030 -m 128 -device loader,file=build/fw.bin,addr=0
