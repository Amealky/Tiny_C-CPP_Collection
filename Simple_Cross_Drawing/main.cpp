#include <stdio.h>
#include <SDL2/SDL.h>

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

void drawCross(int x, int y);

int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_VIDEO);

    gWindow = SDL_CreateWindow("Simple Cross Drawing",
                               SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               400, 300, SDL_WINDOW_SHOWN);

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    int Xold, Yold, Btold, X, Y, Bt, x1, y1;

    SDL_bool quit = SDL_FALSE;
    SDL_Event e;

    SDL_GetMouseState(&Xold, &Yold);
    drawCross(Xold, Yold);

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
            {
                quit = SDL_TRUE;
            }
            else if (e.type == SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&X, &Y);
                if (Btold == 0 && Bt == 0)
                {
                    if (X != Xold || Y != Yold)
                    {
                        drawCross(Xold, Yold);
                        drawCross(X, Y);
                    }
                }
                Xold = X;
                Yold = Y;
                Btold = Bt;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                SDL_GetMouseState(&X, &Y);
                Bt = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT);
                if (Btold == 0 && Bt == 1)
                {
                    drawCross(Xold, Yold);
                    x1 = Xold;
                    y1 = Yold;
                    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
                    SDL_RenderDrawLine(gRenderer, x1, y1, X, Y);
                    SDL_RenderPresent(gRenderer);
                }
                else if (Btold == 1 && Bt == 1)
                {
                    if (X != Xold || Y != Yold)
                    {
                        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
                        SDL_RenderDrawLine(gRenderer, x1, y1, Xold, Yold);
                        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
                        SDL_RenderDrawLine(gRenderer, x1, y1, X, Y);
                        SDL_RenderPresent(gRenderer);
                    }
                }
                else if (Btold == 1 && Bt == 0)
                {
                    drawCross(Xold, Yold);
                }
                Btold = Bt;
                Xold = X;
                Yold = Y;
            }
        }
    }

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
    
    return 0;
}

void drawCross(int x, int y)
{
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(gRenderer, x - 5, y + 5, x + 5, y - 5);
    SDL_RenderDrawLine(gRenderer, x + 5, y + 5, x - 5, y - 5);
    SDL_RenderPresent(gRenderer);
}