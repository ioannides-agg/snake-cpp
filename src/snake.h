#ifndef SNAKE_H
#define SNAKE_H

#include "SDL3/SDL.h"
#include "global.h"
#include <iostream>
#include <vector>

class snake {
public:
  snake() { init_snake(); }
  SG::direction dir;

  void init_snake() {
    snake_body.clear();
    snake_body.push_back(SG::random_tile());
    dir = SG::right;
  };

  void move() {
    if (snake_body.size() > 1) {
      for (int i = snake_body.size() - 1; i > 0; i--) {
        snake_body[i] = snake_body[i - 1];
      }
    }

    switch (dir) {
    case SG::up:
      snake_body[0].y -= 1;
      break;

    case SG::down:
      snake_body[0].y += 1;
      break;

    case SG::right:
      snake_body[0].x += 1;
      break;

    case SG::left:
      snake_body[0].x -= 1;
      break;
    }

    wrap_around();
  }

  void wrap_around() {
    if (snake_body[0].x > SG::width / SG::tile_size) {
      snake_body[0].x = 0;
    }
    if (snake_body[0].x < 0) {
      snake_body[0].x = SG::width / SG::tile_size;
    }
    if (snake_body[0].y > SG::height / SG::tile_size) {
      snake_body[0].y = 0;
    }
    if (snake_body[0].y < 0) {
      snake_body[0].y = SG::height / SG::tile_size;
    }
  }

  void check_collision() {
    if (snake_body.size() > 1) {
      for (int i = 1; i < snake_body.size(); i++) {
        if (snake_body[0].x == snake_body[i].x &&
            snake_body[0].y == snake_body[i].y) {
          SDL_Event event;
          event.type = SNAKE_COLLISION_EVENT;

          SDL_PushEvent(&event);

          return;
        }
      }
    }
  }

  void render_body(SDL_FRect &drawRect, SDL_Renderer &renderer) {
    for (int i = 1; i < snake_body.size(); i++) {
      drawRect.x = snake_body[i].x * SG::tile_size;
      drawRect.y = snake_body[i].y * SG::tile_size;
      SDL_RenderFillRect(&renderer, &drawRect);
    }
  }

  void render_head(SDL_FRect &drawRect, SDL_Renderer &renderer) {
    drawRect.x = snake_body[0].x * SG::tile_size;
    drawRect.y = snake_body[0].y * SG::tile_size;
    SDL_RenderFillRect(&renderer, &drawRect);
  }

  void grow() {
    SDL_Point new_part = snake_body.back();
    snake_body.push_back(new_part);
  }

  SDL_Point get_head() const { return snake_body[0]; }

private:
  std::vector<SDL_Point> snake_body;
};

#endif