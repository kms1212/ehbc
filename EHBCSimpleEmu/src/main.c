#define LOG_IDEN "main"

#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "compat.h"
#include "emulator.h"
#include "params.h"
#include "error.h"
#include "dbgutils.h"
#include "memory/memory.h"
#include "gui/gui.h"
#include "gui/console.h"
#include "log.h"

int main(int argc, char** argv) {
    set_signals();

    int error = init_param(argc, argv);
    if (error) return error;

    struct param* param = get_param();

    thread_t thr_emu;
    create_thread(&thr_emu, NULL, emulator_main, NULL);

    if (param->p_gui) {  // GUI Enabled
        error = gui_main(NULL);
    } else {  // GUI Disabled
        error = 0;
    }

    void* emu_estat;
    join_thread(thr_emu, &emu_estat);

    lprintf(LL_DEBUG, "Exiting program");
    return error;
}
