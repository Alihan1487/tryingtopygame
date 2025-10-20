#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <emscripten.h>


SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* txt;
SDL_Rect rect={100,100,100,100};
bool running = true;
int cur=0;
int last=0;
std::vector<SDL_Rect> walls={SDL_Rect{600,500,100,100}};

void loop() {
    cur=SDL_GetTicks();
    float delta=(cur-last)/1000.f;
    last=cur;
    SDL_Event e;
    int speed=400;
    const Uint8* k=SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            running = false;
    }
    if (!running)
        emscripten_cancel_main_loop();
    if (k[SDL_SCANCODE_W]){
        rect.y-=speed*delta;
        for (auto& i:walls)
            if (SDL_HasIntersection(&rect,&i)){
                rect.y=i.y+i.h;
            }
    }
    if (k[SDL_SCANCODE_S]){
        rect.y+=speed*delta;
        for (auto& i:walls)
            if (SDL_HasIntersection(&rect,&i)){
                rect.y=i.y-rect.h;
            }
    }
    if (k[SDL_SCANCODE_A]){
        rect.x-=speed*delta;
        for (auto& i:walls)
            if (SDL_HasIntersection(&rect,&i)){
                rect.x=i.x+i.w;
            }
    }
    if (k[SDL_SCANCODE_D]){
        rect.x+=speed*delta;
        for (auto& i:walls)
            if (SDL_HasIntersection(&rect,&i)){
                rect.x=i.x-rect.w;
            }
    }
    SDL_SetRenderDrawColor(renderer, 0, 150, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer,&rect);
    {
        SDL_Rect r{300,300,100,100};
        SDL_RenderCopy(renderer,txt,nullptr,&r);
    }
    for (auto& i:walls){
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderFillRect(renderer,&i);
    }
    SDL_RenderPresent(renderer);
}

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("SDL + Emscripten", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface* surf=IMG_Load("assets/olo.png");
    txt=SDL_CreateTextureFromSurface(renderer,surf);
    // Важно! Вместо while используем Emscripten loop:
    emscripten_set_main_loop(loop, 0, 1);
    return 0;
}
