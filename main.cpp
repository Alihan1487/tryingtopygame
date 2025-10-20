#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#else
// Заглушка для обычной сборки (чтобы ccls не жаловался)
inline void emscripten_set_main_loop(void(*)(void), int, int) {}
inline void emscripten_cancel_main_loop() {}
#endif


SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* txt;
SDL_Rect rect={100,100,100,100};
bool running = true;
int cur=0;
int last=0;

void loop() {
    cur=SDL_GetTicks();
    float delta=(cur-last)/1000.f;
    last=SDL_GetTicks();
    SDL_Event e;
    const Uint8* k=SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            running = false;
    }

    if (!running)
        emscripten_cancel_main_loop();
    if (k[SDL_SCANCODE_W]){
        rect.y-=1;
    }
    if (k[SDL_SCANCODE_S]){
        rect.y+=1;
    }
    if (k[SDL_SCANCODE_A]){
        rect.x-=1;
    }
    if (k[SDL_SCANCODE_D]){
        rect.x+=1;
    }
    SDL_SetRenderDrawColor(renderer, 0, 150, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer,&rect);
    {
        SDL_Rect r{300,300,100,100};
        SDL_RenderCopy(renderer,txt,nullptr,&r);
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
