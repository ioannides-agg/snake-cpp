#ifndef GLOBAL_H
#define GLOBAL_H

#include "SDL3/SDL.h"

const Uint32 FOOD_COLLISION_EVENT = SDL_RegisterEvents(1);
const Uint32 SNAKE_COLLISION_EVENT = SDL_RegisterEvents(1);

namespace SG {
    constexpr int width = 1200;
    constexpr int height = 700;
    constexpr int tile_size = 32;

    SDL_Point random_tile() {
        return (SDL_Point){SDL_rand(width / tile_size),
                            SDL_rand(height / tile_size)};
    }
 
    enum direction {
        up,
        down,
        left,
        right
    };
}

#endif