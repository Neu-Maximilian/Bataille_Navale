#include <iostream>
#include <array>
#include <string>
#include "graphics.h"
#include "bataille_navale.h"

using namespace std;

void dessinerBouton(const Bouton& B)
{
	setfillstyle(SOLID_FILL, B.couleur);
	bar(B.x1, B.y1, B.x2, B.y2);
	setcolor(BLACK);
	outtextxy(B.x1+10, B.y1+10, B.texte);
};

void dessinerGrille(const Grille& G)
{
	setcolor(BLACK);
	rectangle(G.x, G.y, G.x+G.width, G.y+G.height);
	for (int i = 0; i < 10; i++)
	{
		line(G.x, G.y+i*G.cellHeight, G.x+G.width, G.y+i*G.cellHeight);
		line(G.x+i*G.cellWidth, G.y, G.x+i*G.cellWidth, G.y+G.height);
	}
};

void dessinerBateaux(const Bateaux& B)
{
	for (int i = 0; i < B.n; i++)
	{
		if (B.tab[i].orientation == 0)
		{
			rectangle(B.tab[i].x, B.tab[i].y, B.tab[i].x+B.tab[i].size*40, B.tab[i].y+40);
		}
		else
		{
			rectangle(B.tab[i].x, B.tab[i].y, B.tab[i].x+40, B.tab[i].y+B.tab[i].size*40);
		}
	}
};

void lireSouris(int& x, int& y)
{
	buttonhit();
	getmouse(x, y);
}

void menu()
{
}

void tests()
{
	opengraphsize(WIDTH, HEIGHT);
	setbkcolor(WHITE);
	setcolor(BLACK);

	getch();
}

int main()
{
	tests();
	return 0;
}
