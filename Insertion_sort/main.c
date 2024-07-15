#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define N  99999
#define MAX 100

unsigned short Tab[N];


int main()
{
	clock_t Deb, Fin;

	unsigned short V = 0;

	srand((unsigned int)time(0));

	for(int i = 0; i < N; i++)
	{
		Tab[i] = rand()%100;

	}
	Deb = clock();
	for(int k = 1; k < N; k++)
	{
		V = Tab[k];
		for(int u = 0; u < k; u++)
		{
			if(Tab[u] >= V)
			{
				for(int i = k; i > u; i--)
				{
					Tab[i] = Tab[i-1];
				}
				Tab[u] = V;
				break;
			}	
		}
	}
	Fin = clock();

	printf(" \n Tri de %ld valeurs en %.2f sec.\n", N, (Fin-Deb)/(double)CLOCKS_PER_SEC);
	printf("Press Enter to continue...");
    getchar();
	return 0;
}