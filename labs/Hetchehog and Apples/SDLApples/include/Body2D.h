#ifndef BODY2D_H
#define BODY2D_H
#ifndef <SDL/SDL.h>
#include <SDL/SDL.h>
#include "Animation.h"

class Body2D
{
    public:
        struct Vector2D{
            float x;
            float y;
        }

        float weight;
        Vector2D velocity;
        SDL_Rect bounds;
        SDL_Rect hitbox;

        void setAnimation(Animation * anim){
            graphics = anim;
        }

        void setSprite(SDL_Surface * sprite){
            Animation temp = new Animation(1, {sprite});
            graphics = &temp;
        }

        Body2D();

        virtual ~Body2D();

    private:
        Animation * graphics;
};

#endif // BODY2D_H
