#include <iostream>

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <stdio.h>
#include "Hedgehog.h"
#include "Apple.h"

#define APPLE_COUNT 5

using namespace std;

Hedgehog hg(10, 270, 0, 640);
Apple apples[] = {
    Apple(0, -50, 430),
    Apple(150, -50, 430),
    Apple(320, -70, 430),
    Apple(460, -120, 430),
    Apple(590, -60, 430)
};

int main ()
{
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    atexit(SDL_Quit);

    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);

    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    // program main loop
    bool done = false;
    while (!done)
    {
        //======message processing loop======
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
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
//                    if (event.key.keysym.sym == SDLK_SPACE)
//                    {
//                        apples = {
//                            Apple(0, -50, 430),
//                            Apple(150, -50, 430),
//                            Apple(320, -70, 430),
//                            Apple(460, -120, 430),
//                            Apple(590, -60, 430)
//                        }
//                        hg.reanimate();
//                    }
                    if (event.key.keysym.sym == SDLK_RETURN && !hg.isHit())
                    {
                        for(Apple & apple: apples) apple.fall();
                    } //Apples fall here
                    break;
                }
            } // end switch
        } //======end of message processing=====


        // UPDATE  -------------------------------------------------
        hg.update();
        for(Apple & apple: apples) {
            apple.update();
            if(hg.collides(apple)){
                hg.hit();
                apple.hit();
            }
        }

        // RENDER  --------------------------------------------------
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
        hg.render(screen);
        for(Apple & apple: apples) apple.render(screen);

        SDL_Flip(screen);
    } // end main loop

    printf("Exited cleanly\n");
    return 0;
}
