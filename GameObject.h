#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "Game.h"


enum condition { standing, running, jumping, falling};

class GameObject
{
public:
    GameObject(const char* texturesheet, int x, int y);
    ~GameObject();

    friend void Game::handleEvents();

    SDL_Rect GetCollider() { return collider; }

    void Update(SDL_Rect Tile[][25], int Mapping[][25]);

    void RunLeft();
    void RunRight();
    void Jump();
    void Stop();


    void Render();
    void ObjectClose();
    bool Collide(SDL_Rect &x, SDL_Rect Tile[][25], int Mapping[][25]);
    bool checkCollision2( SDL_Rect a, SDL_Rect b );

    int Getxspeed(){ return xspeed; }
    int Getxvel() { return xvel; }
    int Getyvel() { return yvel; }


    static const int xspeed = 8;
    static const int yspeed = 8;

    static const int KING_WIDTH = 30;
    static const int KING_HEIGHT = 32;

    SDL_Rect Camera = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};



private:

    int xpos;
    int ypos;

    int xvel;
    int yvel;

    SDL_Texture* objTexture = NULL;
    SDL_Rect srcRect, destRect, collider;

    condition status;
    bool onGround;

};
#endif // GAMEOBJECT_H_INCLUDED
