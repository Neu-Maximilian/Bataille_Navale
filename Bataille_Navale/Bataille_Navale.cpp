#include <iostream>
#include <array>
#include <string>
#include "graphics.h"
#include "bataille_navale.h"

using namespace std;

const int HEIGHT = 720;
const int WIDTH = 1280;

void dessinerBouton(const Bouton& B)
{
	setfillstyle(SOLID_FILL, B.couleur);
	bar(B.x1, B.y1, B.x2, B.y2);
	setcolor(BLACK);
	settextstyle(1, 0, 5);
	outtextxy(B.x1, B.y1, B.texte);
};

void menu()
{
	opengraphsize(WIDTH, HEIGHT);
	setbkcolor(WHITE);
	cleardevice();
	Bouton B_Jouer{WIDTH/2-50, HEIGHT/2-50, WIDTH/2+50, HEIGHT/2+50, BLUE, "Jouer"};
	dessinerBouton(B_Jouer);
	getch();
}

int main()
{
	menu();
	return 0;
}
