#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

void clearEcran() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseEcran() {
    std::cout << "Appuyer sur Entrée pour continuer..." << std::endl;
    std::cin.get();
    std::cin.get();
}

void afficherMenu() {
    clearEcran();
    cout << "[--- Menu Pierre Feuille Ciseaux ---]" << endl;
    cout << "[1.           Jouer                 ]" << endl;
    cout << "[2.          Regles                 ]" << endl;
    cout << "[3.          Quitter                ]" << endl;
    cout << endl;
}

void afficherArene(int manche, int nombreManche, int scoreJoueur, int scoreOrdi) {
    cout << "Manche = " << manche << "/" << nombreManche << endl;
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    cout << "@@    ---Bienvenue Choisissez vos arme !---    @@" << endl;
    cout << "@@  [1.]Pierre --- [2.]Feuille --- [3.]Ciseaux @@" << endl;
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    cout << "                                                 " << endl;
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    cout << "@@@@@              @@@@@                    @@@@@" << endl;
    cout << "@@@@@     VOUS     @@@@@     ORDINATEUR     @@@@@" << endl;
    cout << "@@@@@              @@@@@                    @@@@@" << endl;
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    cout << "@                                               @" << endl;
    cout << "@                  Score                        @" << endl;
    cout << "@                                               @" << endl;
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    cout << "                                                 " << endl;
    cout << "Entre le numero de ton arme : ";
}

void afficherResultat(int choixArme, int choixOrdi) {
    cout << "@@@@@     ";
    switch (choixArme) {
        case 1: cout << "Pierre    "; break;
        case 2: cout << "Feuille   "; break;
        case 3: cout << "Ciseaux   "; break;
    }
    cout << "@@@@@     ";
    switch (choixOrdi) {
        case 1: cout << "Pierre    "; break;
        case 2: cout << "Feuille   "; break;
        case 3: cout << "Ciseaux   "; break;
    }
    cout << "    @@@@@" << endl;
    cout << "@@@@@              @@@@@                    @@@@@" << endl;
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
}

void afficherVictoire(const char* resultat) {
    cout << "@                                               @" << endl;
    cout << "@                 " << resultat << "                     @" << endl;
    cout << "@                                               @" << endl;
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
}

int main() {
    int choixMenu;
    bool relance = true;

    do {
        afficherMenu();
        cout << "Quel est votre choix ? ";
        cin >> choixMenu;

        while (choixMenu < 1 || choixMenu > 3) {
            cout << "Votre choix est invalide !!" << endl;
            cout << "Quel est votre choix ? ";
            cin >> choixMenu;
        }

        switch (choixMenu) {
            case 1: {
                int choixArme;
                int choixOrdi;
                int manche = 1;
                int nombreManche;
                int scoreJoueur = 0;
                int scoreOrdi = 0;

                clearEcran();
                cout << "[--- Combien de manche ? ---]" << endl;
                cout << "Nombre de manche = ";
                cin >> nombreManche;

                srand(time(NULL));

                while (manche <= nombreManche) {
                    choixOrdi = rand() % 3 + 1;

                    clearEcran();
                    afficherArene(manche, nombreManche, scoreJoueur, scoreOrdi);
                    cin >> choixArme;

                    while (choixArme < 1 || choixArme > 3) {
                        clearEcran();
                        afficherArene(manche, nombreManche, scoreJoueur, scoreOrdi);
                        cout << "Cette arme n'existe pas ! Entre un numero valide : ";
                        cin >> choixArme;
                    }

                    clearEcran();
                    cout << "Manche = " << manche << "/" << nombreManche << endl;
                    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
                    cout << "@@    ---Bienvenue Choisissez vos arme !---    @@" << endl;
                    cout << "@@  [1.]Pierre --- [2.]Feuille --- [3.]Ciseaux @@" << endl;
                    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
                    cout << "                                                 " << endl;
                    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
                    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
                    afficherResultat(choixArme, choixOrdi);

                    if (choixArme == choixOrdi) {
                        afficherVictoire("Egalite");
                    } else if ((choixArme == 1 && choixOrdi == 3) || (choixArme == 2 && choixOrdi == 1) || (choixArme == 3 && choixOrdi == 2)) {
                        afficherVictoire("<= Victoire");
                        scoreJoueur++;
                    } else {
                        afficherVictoire("Victoire =>");
                        scoreOrdi++;
                    }

                    pauseEcran();
                    manche++;
                }

                clearEcran();
                cout << " [--- Resultat ---] " << endl;
                cout << " Manche = " << nombreManche << endl;
                cout << " Manche Gagnees = " << scoreJoueur << endl;
                cout << " Manche Perdues = " << scoreOrdi << endl;
                cout << " [---   Score   ---] " << endl;

                if (scoreJoueur > scoreOrdi) {
                    cout << " Victoire" << endl;
                } else if (scoreJoueur < scoreOrdi) {
                    cout << " Defaite" << endl;
                } else {
                    cout << " Egalite" << endl;
                }

                pauseEcran();
                break;
            }
            case 2: {
                clearEcran();
                cout << "                  [--- Voici les regles du jeu ---]" << endl;
                cout << "Le jeu se deroule de cette maniere : " << endl;
                cout << "                                  " << endl;
                cout << "Tout d'abord, le joueur choisit le nombre de manches" << endl;
                cout << "auxquelles il veut participer, ensuite il choisit une arme." << endl;
                cout << "                                                       " << endl;
                cout << "- L'ordinateur s'attribue aleatoirement une arme." << endl;
                cout << "                                                       " << endl;
                cout << "Pierre > Ciseaux" << endl;
                cout << "Ciseaux > Feuille" << endl;
                cout << "Feuille > Pierre" << endl;

                pauseEcran();
                break;
            }
            case 3: {
                clearEcran();
                cout << "Merci d'avoir utilise notre programme" << endl;
                cout << "A bientot !" << endl;
                relance = false;
                pauseEcran();
                break;
            }
        }

    } while (relance);

    return 0;
}