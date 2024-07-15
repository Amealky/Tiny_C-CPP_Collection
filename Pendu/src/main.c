#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "inputs_utils.h"
#include "pendu.h"

void afficher_menu()
{
    printf("Bienvenue dans le pendu ! \n");
    printf("A. MODE UN JOUEUR \n");
    printf("B. MODE DEUX JOUEURS \n");
    printf("C. Scores \n");
    printf("D. QUITTER \n");
}

int main()
{
    char choix = 0;

    afficher_menu();
    choix = lirechar();
	

    switch (choix) {
        case 'A':
            mode_un_joueur();
            break;
        case 'B':
            mode_deux_joueurs();
            break;
        case 'C':
            afficher_scores();
            break;
        case 'D':
            quitter();
            break;
        default:
            printf("Choix invalide \n");
            break;
    }

    return 0;
}