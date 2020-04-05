#include "Body2D.h"
#include "World.h"

Body2D::Body2D(){}

Body2D::Body2D(SDL_Surface * sprite, int x, int y, int w, int h)
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
}

Body2D::Body2D(Animation * anim, int x, int y, int w, int h)
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
}

void Body2D::setAnimation(Animation * anim)
{
    graphics = anim;
}

void Body2D::setSprite(SDL_Surface * sprite)
{
    Animation * temp = new Animation();
    temp->addFrame(sprite);
    graphics = temp;
}

void Body2D::render(SDL_Surface * target)
{
    if(graphics != NULL) graphics->render(target);
}

void Body2D::update(){
    velocity = velocity + acceleration;
    position = position + velocity;
}

bool Body2D::collides(Body2D& other)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = other.bounds.x;
    rightA = other.bounds.x + other.bounds.w;
    topA = other.bounds.y;
    bottomA = other.bounds.y + other.bounds.h;

    leftB = bounds.x;
    rightB = bounds.x + bounds.w;
    topB = bounds.y;
    bottomB = bounds.y + bounds.h;

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

const Body2D& Body2D::collides(type other_type, World& w, Vector2D& direction)
{
    Vector2D old_position = position;
    position = position + direction;
    static Body2D result = w.collides(other_type, this);
    position = old_position;
    //TODO: найти способ возвращать NULL, если столкновение не обнаружено, а не то же тело, которое делает вызов
    return result;
}

Body2D::~Body2D(){
    graphics->~Animation();
}
