#ifndef HEDGEHOG
#define HEDGEHOG

//directions constants
#define LEFT {-1, 0}
#define RIGHT {1, 0}
#define UP {0, -1}
#define DOWN {0, 1}

//speed constants
#define CALM {0, 0}

#include "Body2D.h"
#include "Animation.h"
#include <typeinfo>

class Hedgehog : public Body2D
{
    private:
        Animation * idle;
        Animation * moving_right;
        Animation * moving_left;

        Vector2D route;

    public:
        Hedgehog(int x, int y, int left_bound, int right_bound)
        {
            idle = new Animation();
            idle->loadFrame("res/hg3.bmp");
            Body2D(idle, x, y, 200, 200);

            velocity = LEFT;
            acceleration = CALM;

            route = {left_bound, right_bound};

            t = type.PLAYER;
        }

        void update() override {
            Body2D::update();
            if(position.x < route.x) {direction = RIGHT; velocity = direction;}
            else if(position.x > route.y) {direction = LEFT; velocity = direction;}
        }

        void intersects(Body2D * other, Vector2D& dir) override {
            if(other->t == Body2D.type.ENEMY) velocity = CALM;
            if(other->t == Body2D.type.SOLID && (dir==direction)) velocity = ;
        }

        ~Hedgehog(){
            idle->~Animation();
            moving_left->~Animation();
            moving_right->~Animation();
        }

    private:
        Animation * graphics;
};

#endif // BODY2D_H

