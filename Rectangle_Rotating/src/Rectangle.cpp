#include "Rectangle.h"
#include <cmath>
#include <SDL2/SDL.h>

CRectangle::CRectangle(void) : cx(0), cy(0), m_W(0), m_H(0), an(0.), COL({0, 0, 0, 255}) {}

CRectangle::~CRectangle(void) {}

void CRectangle::setCenter(int X, int Y)
{
    cx = X;
    cy = Y;
}

void CRectangle::setWidth(int W)
{
    m_W = W;
}

void CRectangle::setHeight(int H)
{
    m_H = H;
}

void CRectangle::setAngle(double A)
{
    an = A;
}

void CRectangle::setColor(SDL_Color color)
{
    COL = color;
}

void CRectangle::draw(SDL_Renderer* renderer)
{
    double ux = (m_W / 2) * cos(an);
    double uy = (m_W / 2) * sin(an);

    double vx = (-m_H / 2) * sin(an);
    double vy = (m_H / 2) * cos(an);

    SDL_SetRenderDrawColor(renderer, COL.r, COL.g, COL.b, COL.a);

    SDL_Point points[5];
    points[0] = { static_cast<int>(cx + ux + vx), static_cast<int>(cy + uy + vy) };
    points[1] = { static_cast<int>(cx - ux + vx), static_cast<int>(cy - uy + vy) };
    points[2] = { static_cast<int>(cx - ux - vx), static_cast<int>(cy - uy - vy) };
    points[3] = { static_cast<int>(cx + ux - vx), static_cast<int>(cy + uy - vy) };
    points[4] = points[0];  // Close the rectangle

    SDL_RenderDrawLines(renderer, points, 5);
}

void CRectangle::rotate(double dAngle)
{
    an += dAngle * (M_PI / 180);  // Convert degrees to radians
}