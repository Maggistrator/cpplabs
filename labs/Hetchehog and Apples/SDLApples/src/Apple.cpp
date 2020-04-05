#ifndef APPLE
#define APPLE

//directions constants
#define UP {0, -1}
#define DOWN {0, 1}

//speed constants
#ifndef CALM
    #define CALM {0, 0}
#endif

#include "Body2D.h"
#include "Animation.h"
#include "World.h"
#include "SDL_image.h"

class Apple : public Body2D
{
    private:

        World homeworld;

    public:
        Apple(){}//needed for array initalising

        Apple(int x, int y, World& homeworld)
        {
            SDL_Surface * apple_image = SDL_LoadBMP("res/apple.bmp");

            setSprite(apple_image);

            direction = DOWN;
            velocity = direction;
            acceleration = {0, 0.98f};

            this->homeworld = homeworld;
            t = ENEMY;
        }

        void update() override {
            if(position.y > homeworld.bounds->h) velocity = CALM;

            if(!(&collides(PLAYER, homeworld, direction) == this)) velocity = CALM;
            Body2D::update();
        }

};

#endif // BODY2D_H
