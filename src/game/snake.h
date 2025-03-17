#ifndef SNAKE_H
#define SNAKE_H

#include "../global.h"
#include "SDL3/SDL.h"
#include <iostream>
#include <vector>

class snake {
public:
  snake() { initSnake(); }
  game::direction dir;

  void initSnake() {
    snake_body.clear();
    snake_body.push_back(game::random_tile());
    dir = game::right;
  };

  void move() {
    if (snake_body.size() > 1) {
      for (int i = snake_body.size() - 1; i > 0; i--) {
        snake_body[i] = snake_body[i - 1];
      }
    }

    switch (dir) {
    case game::up:
      snake_body[0].y -= 1;
      break;

    case game::down:
      snake_body[0].y += 1;
      break;

    case game::right:
      snake_body[0].x += 1;
      break;

    case game::left:
      snake_body[0].x -= 1;
      break;
    }

    wrapAround();
  }

  void wrapAround() {
    if (snake_body[0].x > settings::width / settings::tile_size) {
      snake_body[0].x = 0;
    }
    if (snake_body[0].x < 0) {
      snake_body[0].x = settings::width / settings::tile_size;
    }
    if (snake_body[0].y > settings::height / settings::tile_size) {
      snake_body[0].y = 0;
    }
    if (snake_body[0].y < 0) {
      snake_body[0].y = settings::height / settings::tile_size;
    }
  }

  void checkCollision() {
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

  void grow() {
    SDL_Point new_part = snake_body.back();
    snake_body.push_back(new_part);
  }

  SDL_Point getHead() const { return snake_body[0]; }

  std::vector<SDL_Point> getBody() const {
    return std::vector<SDL_Point>(snake_body.begin() + 1, snake_body.end());
  }

private:
  std::vector<SDL_Point> snake_body;
};

#endif