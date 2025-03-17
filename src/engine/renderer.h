#ifndef RENDERER_H
#define RENDERER_H

#include "../global.h"
#include "SDL3/SDL.h"
#include <iostream>
#include <vector>

class Renderer {
public:
  Renderer(SDL_Window *win) {
    rend = SDL_CreateRenderer(win, 0);
    if (rend == NULL) {
      SDL_Log("Could not create renderer: %s", SDL_GetError());
      SDL_Quit();
    }

    drawRect.h = drawRect.w = settings::tile_size;
  }

  ~Renderer() {
    SDL_Log("Destroying Renderer!");
    SDL_DestroyRenderer(rend);
  }

  void refresh() {
    SDL_RenderPresent(rend);
    changeColor();
    SDL_RenderClear(rend);
  }

  void changeColor() {
    SDL_SetRenderDrawColor(rend, 0, 0, 0, SDL_ALPHA_OPAQUE);
  }

  void changeColor(int r, int g, int b) {
    SDL_SetRenderDrawColor(rend, r, g, b, SDL_ALPHA_OPAQUE);
  }

  template <typename T> void render(const T &point) {
    drawRect.x = point.x * settings::tile_size;
    drawRect.y = point.y * settings::tile_size;
    SDL_RenderFillRect(rend, &drawRect);
  }

  template <typename T> void render(const std::vector<T> &points) {
    for (int i = 0; i < points.size(); i++) {
      drawRect.x = points[i].x * settings::tile_size;
      drawRect.y = points[i].y * settings::tile_size;
      SDL_RenderFillRect(rend, &drawRect);
    }
  }

private:
  SDL_Renderer *rend;
  SDL_FRect drawRect;
};

#endif