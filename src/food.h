#ifndef FOOD_H
#define FOOD_H

#include <iostream>
#include "SDL3/SDL.h"
#include "global.h"

class food {
    public:
    food() { food_point = SG::random_tile(); }
    //~food() { std::cout << "destroyed food!" << "\n"; }

    void reposition() {
        food_point = SG::random_tile();
        collided = false;
    }

    void render(SDL_FRect &drawRect, SDL_Renderer &renderer) {
        drawRect.x = food_point.x * SG::tile_size;
        drawRect.y = food_point.y * SG::tile_size;
        SDL_RenderFillRect(&renderer, &drawRect);
    }

    float x() const { return food_point.x; }
    float y() const { return food_point.y; }

    void collide_with(SDL_Point snake_head) {
        if(collided) return;

        if(snake_head.x == food_point.x && snake_head.y == food_point.y) {
            collided = true;
            SDL_Event event;
            event.type = FOOD_COLLISION_EVENT;
            event.user.data1 = this;
            SDL_PushEvent(&event);
        }
    }

    private:
    bool collided = false;
    SDL_Point food_point;
};

#endif