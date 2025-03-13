#ifndef GLOBAL_H
#define GLOBAL_H

#include "SDL3/SDL.h"

namespace SG {
    constexpr int width = 1200;
    constexpr int height = 700;
    constexpr int tile_size = 32;

    SDL_FPoint random_tile() {
        return (SDL_FPoint){(float)SDL_rand(width / tile_size),
                            (float)SDL_rand(height / tile_size)};
    }
 
    enum direction {
        up,
        down,
        left,
        right
    };
}

#endif