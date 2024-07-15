#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "iBuddyLib.h"

#define NOIR 0
#define ROUGE 1
#define VERT 2
#define JAUNE 3
#define BLEU 4
#define VIOLET 5
#define BLEUROI 6
#define BLEUCLAIR 7

#define monter 8
#define descendre 4

#define droite 2
#define gauche 1

#define stop 0

bool iBuddyCoeur(bool allumer);
bool iBuddyTete(int couleur);
bool iBuddyAiles(int actionAiles);
bool iBuddyRotation(int rotation);

int main()
{

	if(iBuddyOpen())
	{
		printf("Succès lors de l'ouverture de l'interface iBuddy \n");
		int cmd;
		cmd = cmd | 128;
		
		int actionAile = monter;
		int rotation = droite;

		while(!kbhit())
		{

			iBuddyAiles(actionAile);
			iBuddyRotation(rotation);
			actionAile = descendre;
			rotation = gauche;
			iBuddyCoeur(true);
			Sleep(50);
			iBuddyTete(VIOLET);
			Sleep(50);
			iBuddyCoeur(false);
			Sleep(50);
			iBuddyAiles(actionAile);
			iBuddyRotation(rotation);
			actionAile = monter;
			rotation = droite;
			iBuddyCoeur(true);
			Sleep(50);
			iBuddyTete(ROUGE);
			Sleep(50);
			iBuddyCoeur(false);
			Sleep(50);
			
		}
		
		getchar();

	}
	else
	{
		printf("Problème lors de l'ouverture de l'interface iBuddy\n");
		getchar();
		return 0;
	}

	getchar();
	iBuddyClose();

	return 0;

}

bool iBuddyCoeur(bool allumer)
{
		int cmd = iBuddyRead();
		if(allumer == true)
		{
			cmd = cmd & 127;
		}
		else
		{
			cmd = cmd | 128;
		}

		
		return iBuddyWrite(cmd);
}

bool iBuddyTete(int couleur)
{
	int cmd = iBuddyRead();

	if(couleur >= 0 && couleur <= 7)
	{
		cmd = cmd & 143;
		couleur = couleur^7;
		couleur = couleur<<4;
		cmd = cmd | couleur;
		
	}
	else
	{
		
		return false;
	}

	return iBuddyWrite(cmd);
}

bool iBuddyAiles(int actionAiles)
{
	
	int etat = iBuddyEtat();

	do
	{
		etat = iBuddyEtat();

	}while((etat & 8) != 0);

	int cmd = iBuddyRead();

	switch(actionAiles)
	{
	case monter:
		cmd = cmd | descendre;
		cmd = cmd & ~monter;
		break;
	case descendre:
		cmd = cmd | monter;
		cmd = cmd & ~descendre;
		break;
	case stop:
		cmd = cmd | descendre;
		cmd = cmd | monter;
		break;
	}

	return iBuddyWrite(cmd);

}

bool iBuddyRotation(int rotation)
{
	int etat = iBuddyEtat();

	do
	{
		etat = iBuddyEtat();

	}while((etat & 1) != 0);

	int cmd = iBuddyRead();

	switch(rotation)
	{
	case droite:
		cmd = cmd | gauche;
		cmd = cmd & ~droite;
		break;
	case gauche:
		cmd = cmd | droite;
		cmd = cmd & ~gauche;
		break;
	case stop:
		cmd = cmd | gauche;
		cmd = cmd | droite;
		break;
	}

	return iBuddyWrite(cmd);

}
