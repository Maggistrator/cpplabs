#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Hedgehog.cpp"
#include "Apple.cpp"
#include "World.h"
#include <vector>

#define APPLE_COUNT 5

int main ( int argc, char** argv )
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 32,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    //------------------------------------------------------------------
    //OBJECTS HERE
    World scene;
    Hedgehog hg(440, 280, scene);

    std::vector<Apple> apples;
    for(int i = 0; i < APPLE_COUNT; i++)
    {
        apples.push_back(Apple(i*100, -50, scene));
    }
    //------------------------------------------------------------------

    // program main loop
    bool done = false;
    while (!done)
    {
        //======message processing loop======
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    if (event.key.keysym.sym == SDLK_ESCAPE) done = true;
                    if (event.key.keysym.sym == SDLK_RETURN) ; //Apples fall here
                    break;
                }
            } // end switch
        } //======end of message processing=====


        // UPDATE
        hg.update();
        for(Apple apple: apples) apple.update();

        // RENDER
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
        hg.render(screen);
        for(Apple apple: apples) apple.render(screen);

        SDL_Flip(screen);
    } // end main loop

    printf("Exited cleanly\n");
    return 0;
}
