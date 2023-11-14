#ifndef __GUI_FB_H__
#define __GUI_FB_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct gui_fb {
    short               hres;
    short               vres;
    SDL_PixelFormatEnum pfmt;

    void*               buf;

    SDL_Texture*        tex;
};

struct gui_fb* fb_init(SDL_Renderer* renderer, short hres, short vres, SDL_PixelFormatEnum pfmt);
int fb_deinit(struct gui_fb* fb, SDL_Renderer* renderer);

int fb_event(struct gui_fb* fb, SDL_Event* event);
int fb_update(struct gui_fb* fb);
int fb_render(struct gui_fb* fb, SDL_Renderer* renderer);

#endif  // __GUI_FB_H__
