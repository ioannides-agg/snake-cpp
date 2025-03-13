#include "includes.h"

int main() {
    constexpr int fps_target = 15;
    constexpr int frame_delay = 1000/ fps_target;
    Uint64 frame_start;
    int frame_time;

    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("Could not initialize SDL modules: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Window* win;
    SDL_Renderer* renderer;

    if(!SDL_CreateWindowAndRenderer("Snake game", SG::width, SG::height, 0, &win, &renderer)) {
        SDL_Log("Could not create window or renderer: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    bool running = true;

    snake snek;

    std::vector<food> foods;
    for (size_t i = 0; i < 4; i++)
    {
        food berry;
        foods.push_back(berry);
    }
    

    SDL_FRect draw;
    draw.h = draw.w = SG::tile_size;

    while (running)
    {
        frame_start = SDL_GetTicks();
    { //GAME LOOP
        snek.move();
        snek.check_collision();
    }

    { //RENDER LOOP
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        for (auto &food : foods)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
            food.render(draw, *renderer);
        }
        
        
        SDL_SetRenderDrawColor(renderer, 0, 125, 40, SDL_ALPHA_OPAQUE);
        snek.render_body(draw, *renderer);

        SDL_SetRenderDrawColor(renderer, 0, 125, 125, SDL_ALPHA_OPAQUE);
        snek.render_head(draw, *renderer);

        SDL_RenderPresent(renderer);
        //SDL_Delay(90);
    }

    { //EVENT HANDLING
        SDL_Event event;
        if(SDL_PollEvent(&event)) {
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
                        snek.init_snake();
                    break;

                    case SDL_SCANCODE_W:
                    case SDL_SCANCODE_UP:
                        snek.dir = SG::up;
                    break;

                    case SDL_SCANCODE_S:
                    case SDL_SCANCODE_DOWN:
                        snek.dir = SG::down;
                    break;

                    case SDL_SCANCODE_A:
                    case SDL_SCANCODE_LEFT:
                        snek.dir = SG::left;
                    break;

                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        snek.dir = SG::right;
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

    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    
    return 0;
}

