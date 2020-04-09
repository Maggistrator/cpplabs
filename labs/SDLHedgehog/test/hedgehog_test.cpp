#include <iostream>

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include "../Hedgehog.h"

using namespace std;

// Раскомментировать
int hedgehogtest_main ()
{
    //Стандарная инициализация SDL ====================================
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    atexit(SDL_Quit);
    //=================================================================

    //Экран и его свойства (не все работают) ==========================
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }
    //Конец инициализации экрана =======================================

    //OBJECTS
    Hedgehog hg(0, 280, 0, 440);

    // основной игровой цикл ===========================================
    bool done = false; // флаг завершения главного цикла
    while (!done)
    {
        //====== начало перехвата событий ======
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            // переключатель выхода
            case SDL_QUIT:
                done = true;
                break;

            // переключатель пользовательских нажатий
            case SDL_KEYDOWN:
                {
                    if (event.key.keysym.sym == SDLK_ESCAPE) done = true;

                    // Переключатель падения яблок
                    if (event.key.keysym.sym == SDLK_RETURN)
                    {
                        cout << "falling";
                    }
                    break;
                }
            } // end switch
        } //====== конец перехвата событий =====


        // UPDATE  -------------------------------------------------

        hg.update();

        // RENDER  --------------------------------------------------

        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
        hg.render(screen);

        SDL_Flip(screen);
    } // end main loop

    printf("Exited cleanly\n");
    return 0;
}
