#include "gui/gui.h"

#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "gui/console.h"
#include "gui/fb.h"
#include "log.h"
#include "params.h"
#include "error.h"
#include "dbgutils.h"

#define CONSOLE

static uint32_t elapsedtime = 0;
static uint32_t count = 0;

void fpscounter(uint32_t timedelta) {
    elapsedtime += timedelta;
    count++;

    if (elapsedtime > 1000) {
        lprintf(LL_DEBUG, "fps: %d", count);
        elapsedtime = 0;
        count = 0;
    }
}

int gui_main(void* arg) {
    // struct param* param = get_param();
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        lprintf(LL_FATAL, "SDL2 Initialization Error");
        return 1;
    }

    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if ((IMG_Init(flags) & flags) != flags) {
        lprintf(LL_FATAL, "SDL2_img Initialization Error");
        return 1;
    }

    if (TTF_Init() != 0) {
        lprintf(LL_FATAL, "SDL2_ttf Initialization Error");
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Emulator",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 480,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        lprintf(LL_FATAL, "SDL2 Window Creation Error");
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        lprintf(LL_FATAL, "SDL2 Renderer Creation Error");
        return 1;
    }

#ifdef CONSOLE
    struct gui_console* console = console_init(renderer, 80, 30);
#else
    struct gui_fb* fb = fb_init(renderer, 640, 480, SDL_PIXELFORMAT_ARGB8888);
#endif

    bool done = false;
    uint32_t prev = SDL_GetTicks();
    uint32_t now = SDL_GetTicks();

    while (!done) {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    done = true;
                    break;
                case SDL_KEYDOWN:
                    if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        done = true;
                    }
                    break;
            }

#ifdef CONSOLE
            console_event(console, &e);
#else
            fb_event(fb, &e);
#endif
        }

#ifdef CONSOLE
        console_update(console);
#else
        fb_update(fb);
#endif

        now = SDL_GetTicks();
        uint32_t delta = now - prev;
        if (delta > 17) {  // Render window
            prev = now;
            fpscounter(delta);


            SDL_RenderClear(renderer);

#ifdef CONSOLE
            console_render(console, renderer);
#else
            fb_render(fb, renderer);
#endif

            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

#ifdef CONSOLE
    console_deinit(console);
#else
    fb_deinit(fb, renderer);
#endif

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
