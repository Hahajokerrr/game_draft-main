#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "Game.h"
#include "GameObject.h"

class Map
{
public:
    Map();
    ~Map();

    void LoadMap(int arr[50][25]);
    void DrawMap(SDL_Rect Camera);
    void CloseMap();
    bool checkCollision( SDL_Rect a, SDL_Rect b );

    friend void GameObject::Update(SDL_Rect Tile[][25], int Mapping[][25]);
    friend bool Collide(SDL_Rect Tile[], int Mapping[][25]);
    friend void Game::update();

private:
    SDL_Rect src, dest;

    SDL_Texture* dirt;
    SDL_Texture* grass;
    SDL_Texture* stone;

    int mapping[50][25];
    SDL_Rect tile[50][25];

};
#endif // MAP_H_INCLUDED
