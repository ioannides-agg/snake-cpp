#ifndef GLOBAL_H
#define GLOBAL_H

#include "SDL3/SDL.h"

const Uint32 FOOD_COLLISION_EVENT = SDL_RegisterEvents(1);
const Uint32 SNAKE_COLLISION_EVENT = SDL_RegisterEvents(1);

namespace settings {
constexpr int width = 1200;
constexpr int height = 700;
constexpr int tile_size = 32;

} // namespace settings

namespace game {

SDL_Point random_tile() {
  return (SDL_Point){SDL_rand(settings::width / settings::tile_size),
                     SDL_rand(settings::height / settings::tile_size)};
}

enum direction { up, down, left, right };
} // namespace game

#endif