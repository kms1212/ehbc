#include "params.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include <errno.h>
#include <stdarg.h>

#include "error.h"
#include "common.h"

static struct param parameter = {
    .p_callpath = NULL,
    .p_color = true,
    .p_loglvl = LL_INFO,
    .p_logstream = NULL,
    .p_gui = true,
};

static const struct option long_options[] = {
    {"nocolor",     no_argument,        NULL, 'c'},
    {"color",       no_argument,        NULL, 'C'},
    {"help",        no_argument,        NULL, 'h'},
    {"version",     no_argument,        NULL, 'v'},
    {"gui",         no_argument,        NULL, 'G'},
    {"no-gui",      no_argument,        NULL, 'g'},
    {"log-level",   required_argument,  NULL, 'l'},
    {"log-output",  required_argument,  NULL, 'L'},
    {"config",      required_argument,  NULL, 'D'},
    {NULL, 0, NULL, 0}
};

void print_usage() {
    printf("Usage: "PROGRAM_NAME" [options]\n");
}

void print_help() {
    print_usage();
    printf(
        "\nOptions:\n"
        "  --odd, -O            Extract odd bytes\n"
        "  --even, -E           Extract even bytes\n"
        "  --output, -o <arg>   Specify output file name\n"
        "  --help, -h           Display this information\n"
        "  --verbose, -v        Verbose program operationsq\n");
}

void print_version() {
    printf(PROGRAM_NAME" version %d.%d.%d "__DATE__"\n",
        PROGRAM_VER_MAJOR, PROGRAM_VER_MINOR, PROGRAM_VER_PATCH);
}

struct keyvalue {
    char* key;
    size_t keylen;
    char* value;
    size_t valuelen;
};

char* parse_keyvalue_next(
    char* cur, char* keybuf, size_t kblen, char* valbuf, size_t vblen) {
    if (cur == NULL) return NULL;

    int arglen = strnlen(cur, 256);

    bool value = false;
    int kcur = 0, vcur = 0;

    keybuf[0] = 0;
    valbuf[0] = 0;

    for (int i = 0; i < arglen; i++) {
        switch (cur[i]) {
            case ':':
            case '=':
                value = true;
                break;
            case ',':
                return cur + i + 1;
                break;
            default:
                if (!value) {
                    keybuf[kcur] = cur[i];
                    kcur++;
                } else {
                    valbuf[vcur] = cur[i];
                    vcur++;
                }
                break;
        }
        if (kcur >= kblen || vcur >= vblen) {
            kcur = 0;
            vcur = 0;
        }
    }
    
    keybuf[kcur] = 0;
    valbuf[vcur] = 0;

    return NULL;
}

int init_param(int argc, char** argv) {
    parameter.p_callpath = argv[0];
    parameter.p_logstream = stderr;

    // Parse Command Line Arguments
    int val;
    while ((val = getopt_long(argc, argv, "cChvl:L:gG", long_options, NULL)) != -1) {
        switch (val) {
        case 'c':  // Disable Terminal Color
            parameter.p_color = false;
            break;
        case 'C':  // Enable Terminal Color
            parameter.p_color = true;
            break;
        case 'h':  // Help
            print_help();
            prog_exit(0);
        case 'v':  // Show version information
            print_version();
            prog_exit(0);
        case 'l':  // Log Level
            if (strncmp(optarg, "debug", 8) == 0) {
                parameter.p_loglvl = LL_DEBUG;
            } else if (strncmp(optarg, "verbose", 8) == 0) {
                parameter.p_loglvl = LL_VERBOSE;
            } else if (strncmp(optarg, "info", 8) == 0) {
                parameter.p_loglvl = LL_INFO;
            } else if (strncmp(optarg, "warning", 8) == 0) {
                parameter.p_loglvl = LL_WARNING;
            } else if (strncmp(optarg, "error", 8) == 0) {
                parameter.p_loglvl = LL_ERROR;
            } else if (strncmp(optarg, "fatal", 8) == 0) {
                parameter.p_loglvl = LL_FATAL;
            } else {
                fprintf(stderr,
                    "Unknown log level. Available options: "
                    "debug, verbose, info, warning, error, fatal\n");
                return EINVAL;
            }
            break;
        case 'L': {  // Log Output
            char keybuf[64], valbuf[64];
            char* cur = optarg;
            while (cur != NULL) {
                cur = parse_keyvalue_next(cur, keybuf, 64, valbuf, 64);

                if (valbuf[0] == 0 && keybuf[0] != 0) {  // Value only
                    if (strncmp(optarg, "stdout", 8) == 0) {
                        parameter.p_logstream = stdout;
                    } else if (strncmp(optarg, "stderr", 8) == 0) {
                        parameter.p_logstream = stderr;
                    } else if (strncmp(optarg, "none", 8) == 0) {
                        parameter.p_logstream = NULL;
                    } else {
                        fprintf(stderr,
                            "Unknown output option. Available options: "
                            "stdout, stderr, none\n");
                        fprintf(stderr, 
                            "Type 'emulator --help' for more options\n");
                        return EINVAL;
                    }
                    break;
                }
            }
            break;
        }
        case 'g':  // Disable GUI
            parameter.p_gui = false;
            break;
        case 'G':  // Enable GUI
            parameter.p_gui = true;
            break;
        case '?':
            return EINVAL;
            break;
        case ':':
            break;
        default:
            return EINVAL;
            break;
        }
    }

    return 0;
}

struct param* get_param() {
    return &parameter;
}
