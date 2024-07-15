#include <stdlib.h>
#include <stdio.h>

#define N 10

void InitTab(int Tab[N][N]);

void FillTab(int Tab[N][N]);

void ShowTab(int Tab[N][N]);

void Binome();

int GetLength( int V );

int main(int argc, char *argv[])
{
	int Tab[N][N];
	
	InitTab(Tab);
	FillTab(Tab);
	ShowTab(Tab);

}

void InitTab(int Tab[N][N])
{
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			Tab[i][j] = 0;
		}
		
	}
}
void FillTab(int Tab[N][N])
{
	Tab[0][0] = 1;

	for(int i = 1; i < N; i++)
	{
		
		Tab[i][0] = 1;
		for(int j = 1; j < N; j++)
		{
			
			Tab[i][j] = Tab[i-1][j-1] + Tab[i-1][j];

		}
	}
}

void ShowTab(int Tab[N][N])
{
	int d = 0;
	for(int i = 0; i < N; i++)
	{
		
		
		for(int j = 0; j <= i; j++)
		{
			d = GetLength(Tab[N-1][j]);

			printf("%*d",  d+1,Tab[i][j]);

		}
		printf("\n");
	}

	printf("Press Enter to continue...");
    getchar();
}

int GetLength( int V )
{
	int i = 0;

	do
	{
		
		V = V / 10;
		i++;
		
	}while(V > 0);
	
	return i;

}