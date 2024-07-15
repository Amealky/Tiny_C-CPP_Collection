#include "Utils.h"
#include <cstdlib>
#include <ctime>

double drand(double m, double M)
{
    return m + rand() * (M - m) / RAND_MAX;
}

int irand(int m, int M)
{
    return m + rand() % (M - m + 1);
}