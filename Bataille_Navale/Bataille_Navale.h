#pragma once
#include <iostream>
#include <array>
#include <string>

using namespace std;

/* Constante */

const int HEIGHT = 720;
const int WIDTH = 1280;

/* Donnees */

using TAB_GRILLE = array<array<int, 10>, 10>;

struct Grille
{
	int x = 50;
	int y = 50;
	int width = 400;
	int height = 400;
	int cellWidth = width / 10;
	int cellHeight = height / 10;
	// flags : 0 = vide, [1-6] = bateau, -1 = case en vue, -2 = rate, -3 = touche, -4 = coule
	TAB_GRILLE tab;
};

struct Bateau
{
	string id;
	int x;
	int y;
	int size;
	int state; // 1 = intact, 2 = touche, 3 = coule
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
	Bateaux B;
};

struct Bouton
{
	int x1, y1, x2, y2;
	int couleur;
	const char* texte;
};


//Ajouté
struct point
{
	int x, y;
};

/* Fonctions et procedures */

void menu();
void dessinerBouton(const Bouton& B);
void dessinerGrille(const Grille& G);
void dessinerBateaux(const Bateaux& B);
void lireSouris(int& px, int& py);