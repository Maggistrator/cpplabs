#include <iostream>

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include "Apple.h"
#include "Hedgehog.h"

using namespace std;

int main ()
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
    Apple multiple_apples[] = {
        Apple(0, -200, 430, screen),
        Apple(100, -50, 430, screen),
        Apple(150, -150, 430, screen),
        Apple(320, -370, 430, screen),
        Apple(460, -120, 430, screen),
        Apple(590, -160, 430, screen)
    };

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
                    //Перезапуск игры по SPACE (не работает)
                    /*
                    if (event.key.keysym.sym == SDLK_SPACE)
                    {
                        multiple_apples[0] = Apple(0, -200, 430, screen);
                        multiple_apples[1] = Apple(100, -50, 430, screen);
                        multiple_apples[2] = Apple(150, -150, 430, screen);
                        multiple_apples[3] = Apple(320, -370, 430, screen);
                        multiple_apples[4] = Apple(460, -120, 430, screen);
                        multiple_apples[5] = Apple(590, -160, 430, screen);
                        hg.reanimate();
                    }
                    */

                    // Переключатель падения яблок
                    if (event.key.keysym.sym == SDLK_RETURN && !hg.isHit())
                    {
                        for(Apple & apple: multiple_apples) apple.fall();
                        cout << "falling";
                    }
                    break;
                }
            } // end switch
        } //====== конец перехвата событий =====


        // UPDATE  -------------------------------------------------

        for(Apple & apple: multiple_apples)
        {
            apple.update();
            if(hg.collides(apple))
            {
                hg.hit();
                apple.hit();
            }
        }
        hg.update();


        // RENDER  --------------------------------------------------

        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
        for(Apple & apple: multiple_apples) apple.render(screen);
        hg.render(screen);


        SDL_Flip(screen);
    } // end main loop

    printf("Exited cleanly\n");
    return 0;
}