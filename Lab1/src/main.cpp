#include <SDL/SDL.h>
#include "Graphic.h"
#include <float.h>
#include <cmath>


float usless_func(float x){
    return (x*x)/(x-2);
}

int main(int argc, char *argv[])
{
  SDL_Surface *screen;
  SDL_Event event;
  if (SDL_Init(SDL_INIT_VIDEO))
    return 1;
  if(!(screen=SDL_SetVideoMode(800,600,16, SDL_ANYFORMAT))){
    SDL_Quit();
    return 1;
  }
  Graphic *g = new Graphic(screen, &usless_func, -1.f, 9.f);
  g->draw();

  while(SDL_WaitEvent(&event)){
    if(event.type == SDL_QUIT ||
      (event.type == SDL_KEYDOWN &&
      event.key.keysym.sym == SDLK_ESCAPE))
    {
      SDL_Quit();
      return 0;
    }
  }
  SDL_Quit();
  return 2;
}
