#include "includes.h"

constexpr double width = 1200;
constexpr double height = 720;

int main() {
    if(!SDL_Init(SDL_INIT_VIDEO)){
        std::cerr << "Failed to initialize SDL " << SDL_GetError() << std::endl;
        return -2;
    }

    SDL_Window* win = SDL_CreateWindow("Snake game", width, height, 0);

    bool running = true;

    while (running)
    {
        SDL_Event event;
        if(SDL_PollEvent(&event) > 0){
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                running = false;
                break;
            }
        }
    }

    SDL_DestroyWindow(win);
    SDL_Quit();
    
    return 0;
}