//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "../include/Animation.h"


void AnimationTest(SDL_Surface * screen){
    /*
    Test with initaliser

    SDL_Surface ** animList = (SDL_Surface**)malloc(sizeof(SDL_Surface*)*3);
    (*animList) = SDL_LoadBMP("hg1.bmp");
    *(animList+1) = SDL_LoadBMP("hg2.bmp");
    *(animList+2) = SDL_LoadBMP("hg3.bmp");

    Animation * anim = new Animation(3, animList);
    */

    //Test with get/set methods
    Animation * anim = new Animation();

    anim->loadFrame("hg1.bmp");
    anim->addFrame(SDL_LoadBMP("hg2.bmp"));
    anim->addFrame(SDL_LoadBMP("hg3.bmp"));

    while((SDL_GetTicks())<12000){
        anim->render(screen);
        SDL_Flip(screen);
        SDL_Delay( 2000 );
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
    }

}


