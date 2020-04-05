#include "World.h"


void World::init(){}

void World::update(){
    for(Body2D e: entities)
    {
        e.update();
    }
}

void World::render(SDL_Surface * screen){
    SDL_BlitSurface(background, bounds, screen, bounds);
    for(Body2D e: entities)
    {
        e.render(screen);
    }
}

const Body2D& World::collides(Body2D::type t, Body2D * caller)
{
    for(Body2D e: entities)
    {
        if(caller->collides(e) && !(&e == caller))
        {
            static Body2D entity = e;
            return entity;
        }
    }
    return *caller;
}

void World::setBackground(SDL_Surface * pic)
{
    background = pic;
}


void World::setSize(int width, int height){
    bounds->w = width;
    bounds->h = height;
}

void World::addEnitity(Body2D * entity)
{
    entities.push_front(*entity);
}

void World::removeEntity(Body2D * entity)
{
    entities.remove(*entity);
}

World::~World()
{
    SDL_FreeSurface(background);
}
