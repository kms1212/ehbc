#ifndef __PARAMS_H__
#define __PARAMS_H__

#include <stdbool.h>
#include <stdio.h>

#include "log.h"

struct param {
    char* p_callpath;

    FILE* p_cfgfile;

    bool p_color;

    enum loglevel p_loglvl;
    FILE* p_logstream;

    bool p_gui;
};

struct param* get_param();

int init_param(int argc, char** argv);

#endif  // __PARAMS_H__
