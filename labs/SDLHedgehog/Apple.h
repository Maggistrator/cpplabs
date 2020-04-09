#ifndef APPLE_H_INCLUDED
#define APPLE_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL_image.h>

class Apple{
    public:
    int x, y, speed = 0, ground;
    float acceleration = 0;
    SDL_Surface * image = NULL;
    bool falling = false;

        SDL_Rect hitbox;

        Apple(){}
        Apple(int e_x, int e_y, int e_ground, SDL_Surface * target) : x(e_x), y(e_y), ground(e_ground)
        {
            hitbox.x = e_x;
            hitbox.y = e_y;
            hitbox.w = 50;
            hitbox.h = 50;

            SDL_Surface *temp = SDL_LoadBMP("res/apple.bmp");
            image = SDL_ConvertSurface(temp, target->format, SDL_SWSURFACE);
            SDL_FreeSurface(temp);
        }

        void fall()
        {
            falling = true;
            speed = 5;
            acceleration = 0.98f;
        }

        void update()
        {
            if(falling)
            {
                speed += acceleration;
                y += speed;
                if(y > ground) falling = false;

                hitbox.x = x;
                hitbox.y = y;
            }

        }

        void render(SDL_Surface * target)
        {
            //Make a temporary rectangle to hold the offsets
            SDL_Rect offset;

            //Give the offsets to the rectangle
            offset.x = x;
            offset.y = y;    //Blit the surface
            SDL_BlitSurface( image, NULL, target, &offset );
        }

        void hit()
        {
            falling = false;
        }

        void reset(int x, int y){
            this->x = x;
            this->y = y;
            hitbox.x = x;
            hitbox.y = y;
        }

        ~Apple()
        {
            SDL_FreeSurface(image);
        }
};

#endif // APPLE_H_INCLUDED
