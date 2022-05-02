#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 640;

static const int TILE_WIDTH = 32;
static const int TILE_HEIGHT = 32;
static const int TILE_NUMBERS = 3;

static const int LEVEL_WIDTH = 800;
static const int LEVEL_HEIGHT = 1600;


class Game
{
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() {return isRunning;}

    static SDL_Renderer* renderer;

private:
    int count = 0;
    bool isRunning;
    SDL_Window* window = NULL;


};



#endif // GAME_H_INCLUDED
