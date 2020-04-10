#include <iostream>

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include "../Hedgehog.h"

using namespace std;

// убрать "hedgehogtest_", и закомментить основной main() чтобы запустить тест
int hedgehogtest_main ()
{
    //Стандарная инициализация SDL ====================================
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    atexit(SDL_Quit);
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);

    //OBJECTS
    Hedgehog hg(0, 280, 0, 440);

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

                    if (event.key.keysym.sym == SDLK_RETURN)
                    {
                        cout << "falling";
                    }
                    break;
                }
            } // end switch
        }


        // UPDATE  -------------------------------------------------

        hg.update(0);

        // RENDER  --------------------------------------------------

        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
        hg.render(screen);

        SDL_Flip(screen);
    } // end main loop

    printf("Exited cleanly\n");
    return 0;
}
