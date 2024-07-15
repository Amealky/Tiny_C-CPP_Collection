#ifndef PENDU_H
#define PENDU_H

void mode_un_joueur();
void mode_deux_joueurs();
void afficher_scores();
void quitter();

char lirechar();
int comptermot(FILE* fichier);
int longueurmotmystere(FILE* fichier, int ligne);
void piochermot(FILE* fichier, int ligne, char motmystere[], int taille);
char* testlettre(char* motmystere, char lettreEntre, char* motcacher, int taillechaine);
int testerreur(char* motmystere, char lettreEntre, char* motcacher, int taillechaine);

#endif 