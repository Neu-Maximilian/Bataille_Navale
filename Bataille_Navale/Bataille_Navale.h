#pragma once
#include <iostream>
#include <array>
#include <string>

using namespace std;

/* Donnes */

using TAB_GRILLE = array<array<int, 10>, 10>;

struct Grille
{
	int x = 10;
	int y = 10;
	int width = 400;
	int height = 400;
	int cellWidth = width / 10;
	int cellHeight = height / 10;
	TAB_GRILLE tab;
};

struct Bateau
{
	string id;
	int x;
	int y;
	int size;
	int orientation; // 0 = horizontal, 1 = vertical
};

using TAB_BATEAUX = array<Bateau, 7>;

struct Bateaux
{
	int n;
	TAB_BATEAUX tab;
};

struct Joueur
{
	string name;
	Grille grille;
	Bateaux bateaux;
};

struct Bouton
{
	int x1, y1, x2, y2;
	int couleur;
	const char* texte;
};

/* Fonctions et procedures */

void menu();
void dessinerBouton(const Bouton &B);