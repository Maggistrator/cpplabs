#include "Graphic.h"
#include <math.h>
#include "SDL_draw.h"

Graphic::Graphic(SDL_Surface *sf, int (*func)(int), float a, float b)
{
    this->sf = sf;
    this->func.integer = func;
    this->isIntFunctPassed = true;
    this->a = a;
    this->b = b;
}

Graphic::Graphic(SDL_Surface *sf, double (*func)(double), float a, float b)
{
    this->sf = sf;
    this->func.real = func;
    this->isIntFunctPassed = false;
    this->a = a;
    this->b = b;
}
void Graphic::draw()
{
    int _x = (int)a, _y = func.integer(_x), temp_x, temp_y;
    //SDL рисует от левого верхнего угла, а мне нужно от левого нижнего - нужно вывести зависимость координат
    do{
        temp_x = _x;
        temp_y = _y;
        _x += dx;
        _y = func.integer(_x);
        if(SDL_LockSurface(sf) == -1) printf("nope");
        else {
            Draw_Line(sf, temp_x, temp_y, _x, _y, 0xFFFFFFFF);
            SDL_UnlockSurface(sf);
        }
    }
    while(_x < b);
}

Graphic::Point* Graphic::convertCoords(Graphic::Point *pt)
{
    point m_pt;
    m_pt.x = pt->x;
    m_pt.y = sf->h - pt->y;
    return &m_pt;
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
