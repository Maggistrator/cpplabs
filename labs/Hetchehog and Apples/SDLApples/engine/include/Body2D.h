#ifndef BODY2D_H
#define BODY2D_H
#include "Animation.h"
#include "Vector2D.h"

class World;

class Body2D
{
    protected:
        Animation * graphics = NULL;

    public:
        float weight = 1;
        Vector2D velocity = {0, 0};
        Vector2D position = {0, 0};
        Vector2D acceleration = {0, 0};
        Vector2D direction;
        SDL_Rect bounds;
        SDL_Rect hitbox;
        typedef enum {PLAYER, ENEMY, SOLID} type;
        type t;

        Body2D();

        Body2D(SDL_Surface *, int, int, int, int);

        Body2D(Animation *, int, int, int, int);

        void setAnimation(Animation *);

        void setSprite(SDL_Surface *);

        void render(SDL_Surface *);

        virtual void update();

        virtual bool collides(Body2D&);

        virtual const Body2D& collides(type, World&, Vector2D&);

        virtual ~Body2D();

        const bool operator==(const Body2D& other) const
        {
            bool equals;
            if(
                (weight != other.weight)        ||
                (!(velocity == other.velocity)) ||
                (!(position == other.position)) ||
                (!(acceleration == other.acceleration))||
                (bounds.w != other.bounds.w)    ||
                (bounds.h != other.bounds.h)    ||
                t != other.t
            ) equals = false;
            else equals = true;

            return equals;
        }

};
#endif // BODY2D_H
