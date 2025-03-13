#ifndef FOOD_H
#define FOOD_H

#include <iostream>
#include "SDL3/SDL.h"
#include "global.h"

class food {
    public:
    food() { food_point = SG::random_tile(); }

    void on_step() {
        std::cout << "grow!" << "\n";
    }

    void render(SDL_FRect &drawRect, SDL_Renderer &renderer) {
        drawRect.x = food_point.x * SG::tile_size;
        drawRect.y = food_point.y * SG::tile_size;
        SDL_RenderFillRect(&renderer, &drawRect);
    }

    private:
    SDL_FPoint food_point;
};

#endif