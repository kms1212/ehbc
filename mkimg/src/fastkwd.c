#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

struct keyword {
    char* kwdstr;
    size_t kwdlen;
};

static const struct keyword kwdtbl[] = {
    { "fill", 4 },
    { "gterr", 5 },
    { "lterr", 5 },
    { "pad", 3 },
};

static const void* kwdlchtbl[3][26] = {
    {  // lvl0
        NULL,  // a
        NULL,  // b
        NULL,  // c
        NULL,  // d
        NULL,  // e
        "i",   // f
        "t",   // g
        NULL,  // h
        NULL,  // i
        NULL,  // j
        NULL,  // k
        "t",   // l
        NULL,  // m
        NULL,  // n
        NULL,  // o
        "p",   // p
        NULL,  // q
        NULL,  // r
        NULL,  // s
        NULL,  // t
        NULL,  // u
        NULL,  // v
        NULL,  // w
        NULL,  // x
        NULL,  // y
        NULL,  // z
    },
    {  // lvl1
        "d",   // a
        NULL,  // b
        NULL,  // c
        NULL,  // d
        NULL,  // e
        NULL,  // f
        NULL,  // g
        NULL,  // h
        "l",   // i
        NULL,  // j
        NULL,  // k
        NULL,  // l
        NULL,  // m
        NULL,  // n
        NULL,  // o
        NULL,  // p
        NULL,  // q
        NULL,  // r
        NULL,  // s
        "e",   // t
        NULL,  // u
        NULL,  // v
        NULL,  // w
        NULL,  // x
        NULL,  // y
        NULL,  // z
    },
    {  // lvl2
        NULL,  // a
        NULL,  // b
        NULL,  // c
        &kwdtbl[3],  // d
        &kwdtbl[1],  // e
        NULL,  // f
        NULL,  // g
        NULL,  // h
        NULL,  // i
        NULL,  // j
        NULL,  // k
        &kwdtbl[0],  // l
        NULL,  // m
        NULL,  // n
        NULL,  // o
        NULL,  // p
        NULL,  // q
        NULL,  // r
        NULL,  // s
        NULL,  // t
        NULL,  // u
        NULL,  // v
        NULL,  // w
        NULL,  // x
        NULL,  // y
        NULL,  // z
    },
};