#include <stdlib.h>
#include <stdio.h>


#define W 15
#define H 21

int main()
{
	//Debut de la face Haute
	for (int i = 0; i < H; i++)
	{
		
		
		int plustest = 2 * i;

		if (plustest >= 16)
		{
			plustest = 15;

		}

		for (int E = 0; E < (33 - i); E++)
		{
			printf(" ");
		}

		for (int DI = 0; DI < W; DI++)
		{
			printf("#");

		}
		for (int EC = 0; EC < (2 * i - W); EC++)
		{

			printf(" ");
		}
		
		for (int plus = 0; plus < plustest; plus++)
		{
			printf("+");
			
		}
	
		printf("\n");
	}
	//Fin de la face Haute

	//Debut de la face Basse
	for (int i = H; i > 0; i--)
	{


		int plustest = 2 * i;

		if (plustest >= 16)
		{
			plustest = 15;

		}

		for (int E = 0; E < (33 - i); E++)
		{
			printf(" ");
		}

		for (int DI = 0; DI < W; DI++)
		{
			printf("#");

		}
		for (int EC = 0; EC < (2 * i - W); EC++)
		{

			printf(" ");
		}

		for (int plus = 0; plus < plustest; plus++)
		{
			printf("+");

		}

		printf("\n");
	}
	//Fin de la face basse

	printf("Press Enter to continue...");
    getchar();

	return 0;
}