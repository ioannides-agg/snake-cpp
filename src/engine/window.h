#ifndef WINDOW_H
#define WINDOW_H

#include "../global.h"
#include "SDL3/SDL.h"
#include <iostream>
#include <vector>

class Window {
public:
  Window(const char *window_name) {
    win = SDL_CreateWindow(window_name, settings::width, settings::height, 0);
    if (win == NULL) {
      SDL_Log("Could not create window: %s", SDL_GetError());
      SDL_Quit();
    }
  }

  ~Window() {
    SDL_Log("Destroying Window!");
    SDL_DestroyWindow(win);
  }

  SDL_Window *getWindow() { return win; }

private:
  SDL_Window *win;
};

#endif