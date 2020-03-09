#include <SDL/SDL.h>
#include "Graphic.h"
#include <float.h>


int usless_func(int x){
    return x;
}

int main(int argc, char *argv[])
{
  SDL_Surface *screen;
  SDL_Event event;
  if (SDL_Init(SDL_INIT_VIDEO))
    return 1;
  if(!(screen=SDL_SetVideoMode(640,480,32, SDL_ANYFORMAT))){
    SDL_Quit();
    return 1;
  }
  Graphic *g = new Graphic(screen, &usless_func, 1.f, 200.f);
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
