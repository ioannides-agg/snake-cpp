#include "includes.h"

void resetGame(snake &s, std::vector<food> &foods) {
  s.initSnake();

  for (auto &food : foods) {
    food.reposition();
  }
}

int main() {
  constexpr int fps_target = 15;
  constexpr int frame_delay = 1000 / fps_target;
  Uint64 frame_start;
  int frame_time;

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Could not initialize SDL modules: %s", SDL_GetError());
    SDL_Quit();
    return -1;
  }

  Window window("Snake Game");
  Renderer renderer(window.getWindow());

  bool running = true;

  snake snek;

  std::vector<food> foods;
  for (size_t i = 0; i < 4; i++) {
    food berry;
    foods.push_back(berry);
  }

  while (running) {
    frame_start = SDL_GetTicks();
    { // GAME LOOP
      snek.move();
      snek.checkCollision();
      for (auto &food : foods) {
        food.collideWith(snek.getHead());
      }
    }

    { // RENDER LOOP
      renderer.refresh();

      for (auto &food : foods) {
        renderer.changeColor(255, 0, 0);
        renderer.render(food.getPoint());
      }

      renderer.changeColor(0, 125, 40);
      renderer.render(snek.getBody());

      renderer.changeColor(0, 120, 120);
      renderer.render(snek.getHead());
    }

    { // EVENT HANDLING
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT:
          running = false;
          break;

        case SDL_EVENT_KEY_DOWN:

          switch (event.key.scancode) {
          case SDL_SCANCODE_ESCAPE:
            running = false;
            break;

          case SDL_SCANCODE_R:
            resetGame(snek, foods);
            break;

          case SDL_SCANCODE_W:
          case SDL_SCANCODE_UP:
            snek.dir = game::up;
            break;

          case SDL_SCANCODE_S:
          case SDL_SCANCODE_DOWN:
            snek.dir = game::down;
            break;

          case SDL_SCANCODE_A:
          case SDL_SCANCODE_LEFT:
            snek.dir = game::left;
            break;

          case SDL_SCANCODE_D:
          case SDL_SCANCODE_RIGHT:
            snek.dir = game::right;
            break;
          }
          break;

        default: // handle custom events
          if (event.type == SNAKE_COLLISION_EVENT) {
            resetGame(snek, foods);
            break;
          }

          if (event.type == FOOD_COLLISION_EVENT) {
            // std::cout << "test" << "\n";
            snek.grow();
            food *eaten = static_cast<food *>(event.user.data1);
            eaten->reposition();
            break;
          }
          break;
        }
      }
    }

    frame_time = SDL_GetTicks() - frame_start;

    if (frame_delay > frame_time) {
      SDL_Delay(frame_delay - frame_time);
    }
  }

  SDL_Quit();

  return 0;
}
