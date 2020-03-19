#ifndef BODY2D_H
#define BODY2D_H
#include "Animation.h"
#include "Vector2D.h"
#include "World.h"

class Body2D
{
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
        World world;


        Body2D(){}

        Body2D(SDL_Surface * sprite, int x, int y, int w, int h, World& world)
        {
            setSprite(sprite);
            bounds.x = x;
            bounds.y = y;
            bounds.w = w;
            bounds.h = h;

            position.x = x;
            position.y = y;

            hitbox.x = 0;
            hitbox.y = 0;
            hitbox.h = h;
            hitbox.w = w;

            this->world = world;
        }

        Body2D(Animation * anim, int x, int y, int w, int h, World& world)
        {
            setAnimation(anim);
            bounds.x = x;
            bounds.y = y;
            bounds.w = w;
            bounds.h = h;

            position.x = x;
            position.y = y;

            hitbox.x = 0;
            hitbox.y = 0;
            hitbox.h = h;
            hitbox.w = w;

            this->world = world;
        }

        void setAnimation(Animation * anim)
        {
            graphics = anim;
        }

        void setSprite(SDL_Surface * sprite)
        {
            Animation * temp = new Animation();
            temp->addFrame(sprite);
            graphics = temp;
        }
        void render(SDL_Surface * target){
            if(graphics != NULL) graphics->render(target);
        }

        virtual void update(){
            velocity = velocity + acceleration;
            position = position + velocity;
        }

        virtual Body2D * intersects(type tp, Vector2D& direction){
            Body2D other;
            if((other = world.findEntity(position+direction)) != NULL){
                if(other.t == tp) return other;
            } else return NULL;
        }

        virtual void intersects(Body2D * other){};
        virtual ~Body2D();

    protected:
        Animation * graphics = NULL;
};

#endif // BODY2D_H
