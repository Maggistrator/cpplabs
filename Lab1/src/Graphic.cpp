#include "Graphic.h"
#include <math.h>
#include <SDL_draw/SDL_draw.h>
#define PITCH (sf->pitch / 4)

Graphic::Graphic(SDL_Surface *sf, float (*func)(float), float a, float b)
{
    this->sf = sf;
    this->func = func;
    this->a = a;
    this->b = b;
}

void Graphic::draw()
{
// Lock surface if needed
  if (SDL_MUSTLOCK(sf))
    if (SDL_LockSurface(sf) < 0)
      return;

    float p_x = a, p_y = func(p_x), n_x, n_y;
    //convertCoords(&prev);

    while((n_x=p_x+dx) != b+dx){
        n_y = func(n_x);
        if(!isinf(n_y)){
            puts("works~");
            //convertCoords(&next);
            Draw_Line(sf, p_x, p_y, n_x, n_y,0xFFFFFF);
        } else {
            puts("inf!");
            Draw_Circle(sf, n_x, n_y = func(n_x+0.005f), 3, 0xFFFFFF);
        }
        p_x = n_x;
        p_y = n_y;
    }

  // Unlock if needed
  if (SDL_MUSTLOCK(sf))
    SDL_UnlockSurface(sf);

  // Tell SDL to update the whole screen
  SDL_UpdateRect(sf, 0, 0, 640, 480);
}

void Graphic::convertCoords(float * x, float * y)
{
    *x += (sf->w)/2;
    *y = (sf->h) - *y;
}

void Graphic::setdx(float dx)
{
    this->dx = dx;
}

float Graphic::getdx()
{
    return dx;
}
void Graphic::setGraphicInterval(float a, float b)
{
    this->a = a < b ? a : b;
    this->b = b > a ? b : a;
}

float Graphic::getA()
{
    return a;
}

float Graphic::getB()
{
    return b;
}

Graphic::~Graphic()
{
    //i dunno wha is dat
}
