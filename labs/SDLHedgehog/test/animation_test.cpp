#include <iostream>

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "../Animation.h"


int animation_main (){
   //Стандарная инициализация SDL ====================================
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    atexit(SDL_Quit);

    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    /*
    Test with initaliser

    SDL_Surface ** animList = (SDL_Surface**)malloc(sizeof(SDL_Surface*)*3);
    (*animList) = SDL_LoadBMP("res/hg1.bmp");
    *(animList+1) = SDL_LoadBMP("res/hg2.bmp");
    *(animList+2) = SDL_LoadBMP("res/hg3.bmp");

    Animation * anim = new Animation(3, animList);
    */

    //Test with get/set methods
    Animation * anim = new Animation();

    anim->loadFrame("res/hg1.bmp");
    anim->addFrame(SDL_LoadBMP("res/hg2.bmp"));
    anim->addFrame(SDL_LoadBMP("res/hg3.bmp"));

    while((SDL_GetTicks())<12000){
        anim->render(screen, NULL);
        SDL_Flip(screen);
        SDL_Delay( 2000 );
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
    }

}


