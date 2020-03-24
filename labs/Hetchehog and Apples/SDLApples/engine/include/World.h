#ifndef WORLD_H
#define WORLD_H

#include "Body2D.h"
#include "Vector2D.h"
#include <list>

class World
{
    //protected:
    //std::list<Body2D> entities;

    public:
    SDL_Surface * background;
    SDL_Rect bounds;
    std::list<Body2D> entities;

    virtual void update();

    virtual void render(SDL_Surface *);

    const Body2D& collides(Body2D::type, Body2D *);

    void setBackground(SDL_Surface *);

    void addEnitity(Body2D *);

    void removeEntity(Body2D *);

    ~World();

};
#endif // WORLD_H
