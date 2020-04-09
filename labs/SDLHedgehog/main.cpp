#include <iostream>

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Apple.h"
#include "Hedgehog.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

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

    if (TTF_Init() < 0) {
        printf( "Unable to init SDL_TTF: %s\n", SDL_GetError() );
        return 2;
    }
    atexit(TTF_Quit);
    srand (time(NULL));

    SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
    if ( !screen )
    {
        printf("Unable to set %dx%d video: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        return 3;
    }


    TTF_Font* pap_font = TTF_OpenFont("res/papyrus.ttf", 18);

    SDL_WM_SetCaption( "SDL Hedgehog", NULL );
    //Конец инициализации SDL =======================================

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

    //FONT SETTINGS ====================================================

    SDL_Color white;
    white.r = white.g = white.b = white.unused = 0xFF;
    SDL_Surface * play_text = TTF_RenderUTF8_Blended(pap_font, "Press ENTER to drop some apples", white);
    SDL_Surface * restart_text = TTF_RenderUTF8_Blended(pap_font, "Press SPACE to play again", white);
    SDL_Rect text_position;
    text_position.x = (SCREEN_WIDTH-280)/2;
    text_position.y = 0;

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

                    if (event.key.keysym.sym == SDLK_SPACE)
                    {

                        for(Apple & apple: multiple_apples)
                            apple.reset(apple.x, apple.y - rand() % 100 - 480);
                        hg.reanimate();
                    }

                    // Переключатель падения яблок
                    if (event.key.keysym.sym == SDLK_RETURN && !hg.isHit())
                    {
                        for(Apple & apple: multiple_apples) apple.fall();
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
        if(!hg.isHit()) SDL_BlitSurface( play_text, NULL, screen, &text_position);
        else SDL_BlitSurface( restart_text, NULL, screen, &text_position);

        SDL_Flip(screen);
    } // end main loop

    TTF_CloseFont(pap_font);
    printf("Exited cleanly\n");
    return 0;
}
