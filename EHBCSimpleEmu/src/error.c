#include "error.h"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "log.h"

void signal_handler(int signo) {
    switch (signo) {
    case SIGINT:
    case SIGQUIT:
        signal(signo, SIG_DFL);
        raise(signo);
        break;
    default:
        break;
    }
}

void prog_exit(int error) {
    exit(error);
}

void set_signals() {
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
}
