#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "inputs_utils.h"

int lire(char* chaine, int longueur) {
    char *positionEntree = NULL;
    
    if (fgets(chaine, longueur, stdin) != NULL) {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL) {
            *positionEntree = '\0';
        } else {
            viderBuffer();
        }
        return 1;
    } else {
        viderBuffer();
        return 0;
    }
}

void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

long lireLong() {
    char nombreTexte[100] = {0};
    if (lire(nombreTexte, 100)) {
        return strtol(nombreTexte, NULL, 10);
    } else {
        return 0;
    }
}

double lireDouble() {
    char nombreTexte[100] = {0};
    if (lire(nombreTexte, 100)) {
        return strtod(nombreTexte, NULL);
    } else {
        return 0.0;
    }
}