#ifndef FOOD_H
#define FOOD_H

#include "../global.h"
#include "SDL3/SDL.h"
#include <iostream>

class food {
public:
  food() { food_point = game::random_tile(); }

  void reposition() {
    food_point = game::random_tile();
    collided = false;
  }

  float x() const { return food_point.x; }
  float y() const { return food_point.y; }

  void collide_with(SDL_Point snake_head) {
    if (collided)
      return;

    if (snake_head.x == food_point.x && snake_head.y == food_point.y) {
      collided = true;
      SDL_Event event;
      event.type = FOOD_COLLISION_EVENT;
      event.user.data1 = this;
      SDL_PushEvent(&event);
    }
  }

  SDL_Point get_point() { return food_point; }

private:
  bool collided = false;
  SDL_Point food_point;
};

#endif