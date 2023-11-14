#include "gui/fb.h"

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "gui/gui.h"
#include "log.h"
#include "params.h"
#include "error.h"

typedef struct gui_fb fb_t;

int start = 0;

fb_t* fb_init(SDL_Renderer* renderer, short hres, short vres, SDL_PixelFormatEnum pfmt) {
    if (hres < 320 || vres < 240) return NULL;
    fb_t* fb = (fb_t*)malloc(sizeof(fb_t));

    fb->hres = hres;
    fb->vres = vres;
    fb->pfmt = pfmt;

    fb->buf = malloc(hres * vres * SDL_BYTESPERPIXEL(pfmt));

    return fb;
}

int fb_deinit(fb_t* fb, SDL_Renderer* renderer) {
    SDL_DestroyTexture(fb->tex);

    free(fb->buf);
    free(fb);

    return 0;
}

int fb_event(fb_t* fb, SDL_Event* event) {
    
    return 0;
}

uint32_t fastrng( uint32_t a) {
    a = (a ^ 61) ^ (a >> 16);
    a = a + (a << 3);
    a = a ^ (a >> 4);
    a = a * 0x27d4eb2d;
    a = a ^ (a >> 15);
    return a;
}

int fb_update(fb_t* fb) {
    return 0;
}

int fb_render(fb_t* fb, SDL_Renderer* renderer) {
    int i;
    for (i = 0; i < fb->hres * fb->vres; i++)
        ((uint32_t*)(fb->buf))[i] = ((fastrng(i + start) & 0xFF) * 0x00010101) | 0xFF000000;
    start += i;
    SDL_Texture* tex = SDL_CreateTexture(renderer, fb->pfmt, SDL_TEXTUREACCESS_STREAMING, fb->hres, fb->vres);
    SDL_UpdateTexture(tex, NULL, fb->buf, fb->hres * sizeof(uint32_t));
    SDL_Rect rect = { 0, 0, fb->hres, fb->vres };
    SDL_RenderCopy(renderer, tex, NULL, &rect);

    return 0;
}
