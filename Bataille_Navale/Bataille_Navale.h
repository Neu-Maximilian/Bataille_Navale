#pragma once
#include <iostream>
#include <array>
#include <string>

using namespace std;

typedef TAB_GRILLE = array<array<int, 10>, 10>;
typedef TAB_BATEAUX = array<Bateau, 7>;

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

struct Bateaux
{
	int n;
	TAB_BATEAUX tab;
};

struct Button
{
	string text;
	int x;
	int y;
	int width;
	int height;
	int color;
};