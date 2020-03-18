#include <stdio.h>
#include <SDL.h>
#include <SDL_draw.h>
#include <math.h>
#include <SDL_ttf.h>

#define H 640
#define W 640
#define WHITE SDL_MapRGB(screen -> format, 255, 255, 255)

int main()
{
    SDL_Surface *screen = NULL;
    SDL_Event event;
    TTF_Font *fnt = NULL;
    SDL_Surface *text_surface = NULL;
    char hello_world[3];

    if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0)
        return 1;

    screen = SDL_SetVideoMode(W, H, 32, SDL_ANYFORMAT);

    if (!screen)
    {
        TTF_Quit();
        SDL_Quit();
        return 3;
    }
    //Ось Y
    Draw_VLine(screen, W / 2, 1, H - 1, WHITE);
    Draw_Line(screen, W / 2, 1, W / 2 - 5 * tan(M_PI / 6), 1 + 10, WHITE);
    Draw_Line(screen, W / 2, 1, W / 2 + 5 * tan(M_PI / 6), 1 + 10, WHITE);
    //Ось Х
    Draw_HLine(screen, 1, H / 2, W - 1, WHITE);
    Draw_Line(screen, W - 1, H / 2, W - 10, H / 2 - 5 * tan(M_PI / 6), WHITE);
    Draw_Line(screen, W - 1, H / 2, W - 10, H / 2 + 5 * tan(M_PI / 6), WHITE);

    SDL_Flip(screen);

    int xpix, ypix;
    double x, y, a = -1, b = 9, dx = 10e-4, scaleFactorX = W/32, scaleFactorY = H/32;

    if(!(fnt = TTF_OpenFont("res/fonts/Papyrus.ttf", scaleFactorX>scaleFactorY?scaleFactorX:scaleFactorY))){
        TTF_Quit();
        SDL_Quit();
        return 3;
    }

    for (x = a; x <= b; x += dx)
    {
        y = (x * x - 3) / (x + 2);
        xpix = round(W / 2 + x * scaleFactorX);
        ypix = round(H / 2 - y * scaleFactorY);

        Draw_Pixel(screen, xpix, ypix, WHITE);
    }

    for(int dx = scaleFactorX, i = 1; i < W / scaleFactorX; i++){
        Draw_VLine(screen, dx*i, H/2, H/2-5, WHITE);
    }

    for(int dx = scaleFactorY, i = 1; i < H / scaleFactorY; i++){
        Draw_HLine(screen, W/2, i*dx, W/2+5, WHITE);
    }

    SDL_Flip(screen);
    while(SDL_WaitEvent(&event))
    {
        if (event.type == SDL_QUIT ||
            (event.type == SDL_KEYDOWN &&
             (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_RETURN)))
        {
            TTF_Quit();
            SDL_Quit();
            return 0;
        }
    }

    TTF_Quit();
    SDL_Quit();
    return 2;
}
