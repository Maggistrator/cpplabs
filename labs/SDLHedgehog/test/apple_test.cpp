#include <iostream>

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include "../Apple.h"

//The attributes of the screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

using namespace std;

int appletest_main ()
{
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

    //OBJ
    Apple single_apple(100, -50, 430, screen, Apple::RED);
    Apple multiple_apples[] = {
        Apple(0, -50, 430, screen, Apple::YELLOW),
        Apple(150, -50, 430, screen, Apple::YELLOW),
        Apple(320, -70, 430, screen, Apple::RED),
        Apple(460, -120, 430, screen, Apple::RED),
        Apple(590, -60, 430, screen, Apple::RED)
    };

    bool done = false;
    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                done = true;
                break;

            case SDL_KEYDOWN:
                {
                    if (event.key.keysym.sym == SDLK_ESCAPE) done = true;

                    if (event.key.keysym.sym == SDLK_RETURN && !single_apple.falling)
                    {
                        for(Apple & apple: multiple_apples) apple.fall();
                        cout << "falling";
                        single_apple.fall();
                    }
                    break;
                }
            } // end switch
        }


        // UPDATE  -------------------------------------------------

        for(Apple & apple: multiple_apples) apple.update();
        single_apple.update();


        // RENDER  --------------------------------------------------

        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
        for(Apple & apple: multiple_apples) apple.render(screen);
        single_apple.render(screen);

        SDL_Flip(screen);
    } // end main loop

    printf("Exited cleanly\n");
    return 0;
}
