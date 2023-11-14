#include "gui/console.h"

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "gui/gui.h"
#include "log.h"
#include "dbgutils.h"
#include "params.h"
#include "error.h"

typedef struct gui_console console_t;

console_t* console_init(SDL_Renderer* renderer, short col, short row) {
    if (col < 40 || row < 15) return NULL;
    console_t* con = (console_t*)malloc(sizeof(console_t));

    con->col = col;
    con->row = row;

    con->font = IMG_LoadTexture(renderer, "vga437.bmp");
    if (con->font == NULL) {
        lprintf(LL_FATAL, "Bitmap font open error");
        prog_exit(1);
    }

    con->cur.col = 0;
    con->cur.row = 0;

    con->buf = (char*)malloc(row * col);
    memset(con->buf, 0, row * col);

    return con;
}

int console_deinit(console_t* con) {
    SDL_DestroyTexture(con->font);
    free(con->buf);
    free(con);

    return 0;
}

int newline(console_t* con) {
    if (con->cur.row < con->row - 1) {
        con->cur.row++;
        con->cur.col = 0;
    } else {
        memmove(con->buf, con->buf + con->col, con->col * (con->row - 1));
        memset(con->buf + con->col * (con->row - 1), 0, con->col);
        con->cur.col = 0;
        con->cur.row = con->row - 1;
    }

    return 0;
}

int console_event(console_t* con, SDL_Event* event) {
    switch(event->type) {
        case SDL_TEXTINPUT: {
            con->buf[con->col * con->cur.row + con->cur.col] = event->text.text[0];
            con->cur.col++;

            if (con->cur.col >= con->col) newline(con);

            break;
        }
        case SDL_KEYDOWN: {
            switch(event->key.keysym.sym) {
                case SDLK_RETURN:
                    newline(con);
                    break;
                case SDLK_BACKSPACE: {
                    int i = con->col * con->cur.row + con->cur.col;
                    while(con->buf[i] == 0 && i > 0) i--;
                    con->buf[i] = 0;
                    con->cur.row = i / con->col;
                    con->cur.col = i % con->col;
                }
            }

            break;
        }
    }

    return 0;
}

int console_update(console_t* con) {
    return 0;
}

int console_render(console_t* con, SDL_Renderer* renderer) {
    for (int i = 0; i < con->row; i++) {
        for (int j = 0; j < con->col; j++) {
            uint8_t glyph = con->buf[con->col * i + j];

            SDL_Rect src = { (glyph & 0x1F) << 3, (glyph & 0xE0) >> 1, 8, 16 };
            SDL_Rect dest = { j * 8, i * 16, 8, 16 };

            SDL_RenderCopy(renderer, con->font, &src, &dest);
        }
    }
    if (((SDL_GetTicks() >> 8) & 1) == 0) {
        SDL_Rect cursor = { con->cur.col * 8, con->cur.row * 16 + 12, 8, 2 };
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderDrawRect(renderer, &cursor);
    }

    return 0;
}
