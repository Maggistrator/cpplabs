#ifndef HEDGEHOG
#define HEDGEHOG

//directions constants
#define LEFT {-1, 0}
#define RIGHT {1, 0}

//speed constants
#define CALM {0, 0}

#include "Body2D.h"
#include "Animation.h"
#include "World.h"

class Hedgehog : public Body2D
{
    private:
        //Указатели на доступные анимации
        Animation * idle;
        Animation * moving_right;
        Animation * moving_left;

        //границы маршрута
        int left_bound, right_bound;

        World homeworld;

    public:
        Hedgehog(int x, int y, World& homeworld)
        {
            idle = new Animation();
            idle->loadFrame("res/hg3.bmp");

            moving_left = new Animation();
            moving_left->loadFrame("res/hg1.bmp");

            moving_right = new Animation();
            moving_right->loadFrame("res/hg2.bmp");

            Body2D(moving_left, x, y, 200, 200);

            direction = LEFT;
            velocity = direction;
            acceleration = CALM;

            this->left_bound = 0;
            this->right_bound = homeworld.bounds->w;

            t = PLAYER;
            this->homeworld = homeworld;
        }

        void update() override {
            if(position.x < left_bound) {direction = RIGHT; velocity = direction;}
            else if(position.x > right_bound) {direction = LEFT; velocity = direction;}

            if(!(&collides(ENEMY, homeworld, direction) == this)) velocity = CALM;
            Body2D::update();
        }

        ~Hedgehog(){
            idle->~Animation();
            moving_left->~Animation();
            moving_right->~Animation();
        }

};

#endif // BODY2D_H

