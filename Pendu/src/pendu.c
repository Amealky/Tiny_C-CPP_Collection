#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "inputs_utils.h"
#include "pendu.h"

void clearEcran() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

char lirechar()
{
    char caractere = 0;
    caractere = getchar();
    caractere = toupper(caractere);

    while (getchar() != '\n');

    return caractere;
}

int comptermot(FILE* fichier)
{
    int i = 0;
    char charactuel = '0';

    do {
        charactuel = fgetc(fichier);
        if (charactuel == '\n') {
            i++;
        }
    } while (charactuel != EOF);

    return i;
}

int longueurmotmystere(FILE* fichier, int ligne)
{
    int ligneactuel = 0;
    int taille = 0;
    char charactuel = '0';

    do {
        charactuel = fgetc(fichier);
        if (charactuel == '\n') {
            ligneactuel++;
        }
        if (ligne == 0) {
            rewind(fichier);
        }
    } while (ligneactuel != ligne);

    do {
        charactuel = fgetc(fichier);
        taille++;
    } while (charactuel != '\n' && charactuel != EOF);

    return taille;
}

void piochermot(FILE* fichier, int ligne, char motmystere[], int taille)
{
    int ligneactuel = 0;
    char charactuel = '0';

    do {
        charactuel = fgetc(fichier);
        if (charactuel == '\n') {
            ligneactuel++;
        }
        if (ligne == 0) {
            rewind(fichier);
        }
    } while (ligneactuel != ligne);

    fgets(motmystere, taille, fichier);
}

char* testlettre(char* motmystere, char lettreEntre, char* motcacher, int taillechaine)
{
    for (int i = 0; i < taillechaine; i++) {
        if (motmystere[i] == lettreEntre) {
            motcacher[i] = lettreEntre;
        }
    }

    return motcacher;
}

int testerreur(char* motmystere, char lettreEntre, char* motcacher, int taillechaine)
{
    int present = 0;

    for (int i = 0; i < taillechaine; i++) {
        if (motmystere[i] == lettreEntre) {
            present++;
        }
    }

    return present > 0 ? 1 : 0;
}

void mode_un_joueur()
{
    clearEcran();
    FILE* dico = fopen("./../../Dico.txt", "r");
    if (dico != NULL) {
        FILE* score = fopen("./../../Score.score", "a");
        if (score != NULL) {
            int nombredemot = comptermot(dico);
            rewind(dico);

            srand(time(NULL));
            int ligne = rand() % nombredemot;

            int taillechaine = longueurmotmystere(dico, ligne);
            char* motmystere = (char*)malloc(taillechaine * sizeof(char));
            char* motcacher = (char*)malloc(taillechaine * sizeof(char));

            if (motmystere == NULL || motcacher == NULL) {
                printf("Erreur memoire\n");
                exit(0);
            }

            rewind(dico);
            piochermot(dico, ligne, motmystere, taillechaine);
            for (int i = 0; i < taillechaine - 1; i++) {
                motcacher[i] = '*';
            }
            motcacher[taillechaine - 1] = '\0';

            char pseudo[100] = {0};
            printf("Entrez votre pseudo [MAXIMUM 100 CARACTÈRES] : ");
            lire(pseudo, 100);
            fprintf(score, "%s ", pseudo);

            int compteur = 10;
            int arret = 0;

            do {
                printf("Veuillez essayer une lettre : %s \n", motcacher);
                printf("Il vous reste %d essais ! \n", compteur);

                char lettreEntre = lirechar();
                printf("Vous avez entré la lettre : %c \n", lettreEntre);

                motcacher = testlettre(motmystere, lettreEntre, motcacher, taillechaine);
                int present = testerreur(motmystere, lettreEntre, motcacher, taillechaine);

                if (!present) {
                    compteur--;
                }

                if (strcmp(motcacher, motmystere) == 0 || compteur == 0) {
                    arret = 1;
                }

            } while (!arret);

            if (compteur == 0) {
                printf("Dommage, le mot mystère était : %s \n", motmystere);
            } else {
                printf("Bravo, le mot mystère était : %s \n", motcacher);
            }

            fprintf(score, "%d\n", compteur);

            free(motmystere);
            free(motcacher);
            fclose(score);

        } else {
            printf("Impossible d'ouvrir le fichier score \n");
        }
        fclose(dico);

    } else {
        printf("Impossible d'ouvrir le fichier dico\n");
    }
    printf("Press Enter to continue...");
    getchar(); 
}

void mode_deux_joueurs()
{
    clearEcran();
    char motmystere[100] = {0};
    char motcacher[100] = {0};
    int compteur = 10;
    int arret = 0;

    printf("Tapez le mot mystère [MAXIMUM 100 CARACTÈRES] : ");
    if (lire(motmystere, 100)) {
        for (int i = 0; i < strlen(motmystere); i++) {
            motmystere[i] = toupper(motmystere[i]);
            motcacher[i] = '*';
        }

        clearEcran();

        motcacher[strlen(motmystere)] = '\0';

        do {
            printf("Veuillez essayer une lettre : %s \n", motcacher);
            printf("Il vous reste %d essais ! \n", compteur);

            char lettreEntree = lirechar();
            printf("Vous avez entré la lettre : %c \n", lettreEntree);

            testlettre(motmystere, lettreEntree, motcacher, strlen(motcacher));
            int present = testerreur(motmystere, lettreEntree, motcacher, strlen(motcacher));

            if (!present) {
                compteur--;
            }

            if (strcmp(motcacher, motmystere) == 0 || compteur == 0) {
                arret = 1;
            }
        } while (!arret);

        if (compteur == 0) {
            printf("Dommage, le mot mystère était : %s \n", motmystere);
        } else {
            printf("Bravo, le mot mystère était bien : %s \n", motcacher);
        }

    } else {
        printf("Erreur lors de l'écriture du mot mystère \n");
        exit(0);
    }
    printf("Press Enter to continue...");
    getchar(); 
}

void afficher_scores()
{
    clearEcran();
    FILE* score = fopen("./../../Score.score", "r");
    if (score != NULL) {
        printf("Voici le nombre de coups qu'il restait au joueur ainsi que leurs noms : \n\n");

        char charactuel = fgetc(score);
        while (charactuel != EOF) {
            printf("%c", charactuel);
            charactuel = fgetc(score);
        }

        fclose(score);
    } else {
        printf("Impossible d'ouvrir le fichier score\n");
    }
    printf("Press Enter to continue...");
    getchar(); 
}

void quitter()
{
    printf("Au revoir !\n");
    printf("Press Enter to continue...");
    getchar(); 
    exit(0);
}