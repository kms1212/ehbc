#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <signal.h>
#include <errno.h>
#include <stdarg.h>

#include "node.h"
#include "dtsl.tab.h"

#define ESTR_BUF_SIZE   256
#define IFILE_MAX       256

#define APP_NAME        "dtsl"

#define RAISE_ERR(err)      \
    { error = err; \
    goto exit; }

#define EMSG(msg, ...)  fprintf(stderr, APP_NAME": error: "msg, __VA_ARGS__)
#define E_ODD_FSIZE     "size of file %s is not even\n"

#define VMSG(msg)           if (verbose) fprintf(stdout, msg)
#define VMSG_V(msg, ...)    if (verbose) fprintf(stdout, msg, __VA_ARGS__)
#define VERBOSE_BEGIN       if (verbose) {
#define VERBOSE_END         }

// A Wrapper for a File Operation Without Return Value  (USE ONLY INSIDE main())
#define FILE_OP(op)         if ((error = op) != 0) RAISE_ERR(errno)
// A Wrapper for a File Operation With Return Value     (USE ONLY INSIDE main())
#define FILE_VOP(var, op)   if ((var = op) == -1) RAISE_ERR(errno)

static const struct option long_options[] = {
    {"inspect", no_argument, NULL, 'i'},
    {"dry-run", no_argument, NULL, 'E'},
    {"help", no_argument, NULL, 'h'},
    {"output", required_argument, NULL, 'o'},
    {"verbose", required_argument, NULL, 'v'},
    {NULL, 0, NULL, 0}
};

char* input_files[IFILE_MAX];
FILE* input_fstructs[IFILE_MAX];
size_t input_fsizes[IFILE_MAX];
int input_count = 0;

char* output_file;
FILE* output_fstruct;

int verbose = 0;
int odd = 0;

void signal_handler(int signo);
int exit_prog(int error);

int main(int argc, char** argv) {
    int error = 0;

    // Set Signal Handler
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);

    // Parse Command Line Arguments
    int val;
    while ((val = getopt_long(argc, argv, "EOho:v", long_options, NULL)) != -1) {
        switch (val) {
        case 'E':  // Even bytes
            VMSG("Copy Even Bytes\n");
            odd = 0;
            break;
        case 'O':  // Odd bytes
            VMSG("Copy Odd Bytes\n");
            odd = 1;
            break;
        case 'h':  // Help
            printf(
                "Usage: "APP_NAME" [options] (--output | -o) output_file input_files...\n\n"
                "Options:\n");
            return 0;
            break;
        case 'o':  // Output file
            output_file = optarg;
            break;
        case 'v':  // Verbose
            verbose = 1;
            break;
        case '?':
            break;
        case ':':
            break;
        default:
            RAISE_ERR(EINVAL);
            break;
        }
    }

    if (optind == argc) RAISE_ERR(EINVAL);  // No input specified.

    VMSG_V("optind: %d, argc: %d\n", optind, argc);
    while (optind < argc)  // Input files
        input_files[input_count++] = argv[optind++];


    // Handle Error, Cleanup, and Exit
exit:
    return exit_prog(error);
}

int cleanup() {
    int error;
    for (int i = 0; i < input_count; i++) {
        if ((error = fclose(input_fstructs[i])) != 0)
            return error;
    }
    if ((error = fclose(output_fstruct)) != 0)
        return error;
    return 0;
}

int exit_prog(int error) {
    int cu_err = cleanup();
    if (error == 0)
        error = cu_err;

    if (error != 0) {
        char errbuf[ESTR_BUF_SIZE];
        strerror_r(error, errbuf, ESTR_BUF_SIZE);
        fputs(errbuf, stderr);
    }

    return error;
}

void signal_handler(int signo) {
    switch (signo) {
    case SIGINT:
    case SIGQUIT:
        cleanup();
        signal(signo, SIG_DFL);
        raise(signo);
        break;
    default:
        break;
    }
}
