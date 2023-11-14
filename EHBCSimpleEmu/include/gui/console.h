#ifndef __GUI_CONSOLE_H__
#define __GUI_CONSOLE_H__

#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct gui_console {
    short           col;
    short           row;
    SDL_Texture*    font;

    char*           buf;

    struct {
        short       col;
        short       row;
    } cur;
};

struct gui_console* console_init(SDL_Renderer* renderer, short col, short row);
int console_deinit(struct gui_console* con);

int console_event(struct gui_console* con, SDL_Event* event);
int console_update(struct gui_console* con);
int console_render(struct gui_console* con, SDL_Renderer* renderer);

#endif  // __GUI_CONSOLE_H__
