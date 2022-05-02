#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"



using namespace std;

SDL_Texture* background;
SDL_Rect BgSrc = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT}, BgDest = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
GameObject* player;
Map* mapper;

SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flag = 0;
    if(fullscreen)
    {
        flag = SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        cout << "Initialized..." << endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flag);
        if(window)
        {
            cout << "Window created!" << endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            cout << "Renderer created!" << endl;
        }
        isRunning = true;
    } else {
        isRunning = false;
    }

    background = TextureManager::LoadTexture("image/sky.png");
    player = new GameObject("image/king_right_2.png", 0 , LEVEL_HEIGHT - 32);
    mapper = new Map();
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT)
    {
        isRunning = false;
    }
    else if( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
        {
            switch( event.key.keysym.sym )
            {
                /*
                case SDLK_RIGHT: player->xvel += player->xspeed; break;
                case SDLK_LEFT: player->xvel -= player->xspeed; break;
                case SDLK_UP: player->yvel -= player->yspeed; break;
                case SDLK_DOWN: player->yvel += player->yspeed; break;
                */
                case SDLK_RIGHT: player->RunRight(); break;
                case SDLK_LEFT: player->RunLeft(); break;
                case SDLK_SPACE: player->Jump(); break;
            }
        }
    else if( event.type == SDL_KEYUP && event.key.repeat == 0 )
    {
        switch( event.key.keysym.sym )
            {
                /*
                case SDLK_RIGHT: player->xvel -= player->xspeed; break;
                case SDLK_LEFT: player->xvel += player->xspeed; break;
                case SDLK_UP: player->yvel += player->yspeed; break;
                case SDLK_DOWN: player->yvel -= player->yspeed; break;
                */
                case SDLK_RIGHT: player->Stop(); break;
                case SDLK_LEFT: player->Stop(); break;
                case SDLK_SPACE: player->Stop(); break;
            }
    }
}
void Game::update()
{
    player->Update(mapper->tile, mapper->mapping);
}
void Game::render()
{
    SDL_RenderClear(renderer);
    TextureManager::Draw(background, player->Camera, BgDest);
    mapper->DrawMap(player->Camera);
    player->Render();
    SDL_RenderPresent(renderer);

}
void Game::clean()
{
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    player->ObjectClose();
    player = NULL;
    mapper->CloseMap();
    mapper = NULL;

    IMG_Quit();
    SDL_Quit();
    cout << "Game cleaned" << endl;
}

