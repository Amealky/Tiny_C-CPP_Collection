#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SDL2/SDL.h>

class CRectangle
{
public:
    CRectangle(void);
    ~CRectangle(void);

    void setCenter(int X, int Y);
    void setWidth(int W);
    void setHeight(int H);
    void setAngle(double A);
    void setColor(SDL_Color color);
    void draw(SDL_Renderer* renderer);
    void rotate(double dAngle);

private:
    int cx, cy;
    int m_W, m_H;
    double an;
    SDL_Color COL;
};

#endif