#ifndef APPLE_H_INCLUDED
#define APPLE_H_INCLUDED

#include <SDL.h>

class Apple{
    int x, y, speed = 0, ground;
    float acceleration = 0;
    SDL_Surface * image;
    SDL_Rect * draw_rect;
    bool falling = false;

    public:
        SDL_Rect hitbox;

        Apple(){}
        Apple(int e_x, int e_y, int e_ground) : x(e_x), y(e_y), ground(e_ground)
        {
            hitbox.x = draw_rect->x = e_x;
            hitbox.y = draw_rect->y = e_y;
            hitbox.w = draw_rect->w = 50;
            hitbox.h = draw_rect->h = 50;
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

                hitbox.x = draw_rect->x = x;
                hitbox.y = draw_rect->y = y;
            }
        }

        void render(SDL_Surface * target)
        {
            SDL_BlitSurface(image, draw_rect, target, draw_rect);
        }

        void hit()
        {
            falling = false;
        }
};

#endif // APPLE_H_INCLUDED
