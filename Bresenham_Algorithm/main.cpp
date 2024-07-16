#include <SDL2/SDL.h>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

int Abs(int value);
int Sgn(int value);
void Line(SDL_Renderer* renderer, int X0, int Y0, int X1, int Y1, SDL_Color color);

int main(int argc, char** argv) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Line Drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }


    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_Color white = { 255, 255, 255, SDL_ALPHA_OPAQUE };

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 25, 25, 25, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
        for (int Y = 0; Y < WINDOW_HEIGHT; Y += 4) {
            Line(renderer, 0, 0, Y, WINDOW_HEIGHT, white);
        }

        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

int Abs(int value) {
    return value < 0 ? -value : value;
}

int Sgn(int value) {
    return (value > 0) - (value < 0);
}

void Line(SDL_Renderer* renderer, int X0, int Y0, int X1, int Y1, SDL_Color color) {
    int DeltaX = Abs(X1 - X0);
    int DeltaY = Abs(Y1 - Y0);
    int SgnX = Sgn(X1 - X0);
    int SgnY = Sgn(Y1 - Y0);

    bool isSteep = DeltaY > DeltaX;
    if (isSteep) {
        int temp = DeltaX;
        DeltaX = DeltaY;
        DeltaY = temp;

        temp = X0;
        X0 = Y0;
        Y0 = temp;

        temp = X1;
        X1 = Y1;
        Y1 = temp;

        temp = SgnX;
        SgnX = SgnY;
        SgnY = temp;
    }

    int Error = 2 * DeltaY - DeltaX;

    for (int i = 0; i <= DeltaX; i++) {
        if (isSteep) {
            SDL_RenderDrawPoint(renderer, Y0, X0);
        } else {
            SDL_RenderDrawPoint(renderer, X0, Y0);
        }

        if (Error > 0) {
            Y0 += SgnY;
            Error -= 2 * DeltaX;
        }
        X0 += SgnX;
        Error += 2 * DeltaY;
    }
}