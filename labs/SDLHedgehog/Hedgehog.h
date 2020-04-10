#ifndef HEDGEHOG_H_INCLUDED
#define HEDGEHOG_H_INCLUDED

#include "Animation.h"
#include <SDL/SDL.h>
#include "Apple.h"

class Hedgehog {
    private:
        int x, y, speed = 1;

        bool m_hit = false;

        //Указатели на доступные анимации
        Animation * idle;
        Animation * idle_right;
        Animation * moving_right;
        Animation * moving_left;

        Animation * current;

        //границы маршрута
        int left_bound, right_bound;
        SDL_Rect hitbox;
        SDL_Rect drawrect;

        void turn()
        {
            speed = -speed;
            current = speed > 0 ? moving_right : moving_left;
        }

    public:
        Hedgehog(int e_x, int e_y, int e_left_bound, int e_right_bound) : x(e_x), y(e_y), left_bound(e_left_bound), right_bound(e_right_bound)
        {
            idle = new Animation();
            idle->loadFrame("res/idle.bmp");

            idle_right = new Animation();
            idle_right->loadFrame("res/idler.bmp");

            moving_left = new Animation();
            moving_left->loadFrame("res/hg1.bmp");
            moving_left->loadFrame("res/hg2.bmp");
            moving_left->loadFrame("res/hg3.bmp");
            moving_left->loadFrame("res/hg4.bmp");

            moving_right = new Animation();
            moving_right->loadFrame("res/hgr1.bmp");
            moving_right->loadFrame("res/hgr2.bmp");
            moving_right->loadFrame("res/hgr3.bmp");
            moving_right->loadFrame("res/hgr4.bmp");

            current = moving_right;

            hitbox.x = x + 30;
            hitbox.y = y + 30;
            hitbox.w = 140;
            hitbox.h = 100;

            drawrect.x = x;
            drawrect.y = y;
            drawrect.w = 200;
            drawrect.h = 140;
        }

        void update(int delta)
        {

            if(!m_hit)
            {
                if(x + speed > left_bound && x + speed < right_bound) x += speed;
                else turn();

                hitbox.x = x + 50;
                hitbox.y = y + 50;

                drawrect.x = x;
                drawrect.y = y;
            }
        }

        void render(SDL_Surface * target)
        {
            current->render(target, &drawrect);
        }

        bool collides(Apple& other)
        {
            int leftA, leftB;
            int rightA, rightB;
            int topA, topB;
            int bottomA, bottomB;

            leftA = other.hitbox.x;
            rightA = other.hitbox.x + other.hitbox.w;
            topA = other.hitbox.y;
            bottomA = other.hitbox.y + other.hitbox.h;

            leftB = hitbox.x;
            rightB = hitbox.x + hitbox.w;
            topB = hitbox.y;
            bottomB = hitbox.y + hitbox.h;

            if( bottomA <= topB )
            {
                return false;
            }

            if( topA >= bottomB )
            {
                return false;
            }

            if( rightA <= leftB )
            {
                return false;
            }

            if( leftA >= rightB )
            {
                return false;
            }

            return true;
        }

        void hit()
        {
            m_hit = true;
            current = speed > 0 ? idle_right : idle;
        }

        bool isHit(){ return m_hit; }

        void reanimate()
        {
            m_hit = false;
            current = speed > 0 ? moving_right : moving_left;
        }

        ~Hedgehog()
        {
            idle->~Animation();
            moving_left->~Animation();
            moving_right->~Animation();
        }
};

#endif // HEDGEHOG_H_INCLUDED
