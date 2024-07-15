#include "Rectangle.h"
#include "Utils.h"
#include <SDL2/SDL.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>

#define NBRECT 50
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Rectangles Rotating", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    srand(static_cast<unsigned>(time(0)));
    
    CRectangle R[NBRECT];
    int cx, cy, W, H;
    double A;
    SDL_Color col;

    for (int i = 0; i < NBRECT; i++)
    {
        cx = irand(150, 650);
        cy = irand(100, 500);
        W = irand(100, 250);
        H = irand(80, 150);
        col = { static_cast<Uint8>(irand(0, 255)), static_cast<Uint8>(irand(0, 255)), static_cast<Uint8>(irand(0, 255)), 255 };
        A = drand(0.1, 5);

        R[i].setCenter(cx, cy);
        R[i].setColor(col);
        R[i].setWidth(W);
        R[i].setHeight(H);
        R[i].setAngle(A);
    }

    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < NBRECT; i++)
        {
            R[i].draw(renderer);
            R[i].rotate(0.1);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}