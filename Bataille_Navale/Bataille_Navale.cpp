#include <iostream>
#include <array>
#include <string>
#include "graphics.h"
#include "bataille_navale.h"

using namespace std;

void verbose(const string msg) { if (VERBOSE) clog << msg << endl; };

void lireSouris(int& x, int& y)
{
	buttonhit();
	getmouse(x, y);
}

void dessinerBouton(const Bouton& B)
{
	setfillstyle(SOLID_FILL, B.couleur);
	bar(B.x1, B.y1, B.x2, B.y2);
	setcolor(WHITE);
	setbkcolor(B.couleur);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(TRIPLEX_FONT, 0, 3); // fonts, direction, size
	outtextxy((B.x1 + B.x2) / 2, (B.y1 + B.y2) / 2, B.texte);
}

bool lireBoutons(const Scene& S, int action)
{
	int x, y;
	lireSouris(x, y);
	for (auto& B : S.boutons)
	{
		if (x > B.x1 && x < B.x2 && y > B.y1 && y < B.y2)
		{
			return true;
			action = B.id;
		}
	}
}

void menu()
{

}

void tests()
{
	Bouton SOLO = { 640 - 200, 720 - 300 , 640 + 200, 720 - 400, BLUE, "Solo",1 };
	Scene S = { DEBUG, {SOLO} };
	dessinerBouton(S.boutons[0]);
	int action;
	while (!lireBoutons(S, action))
	{
		delay(100);
	}
	verbose("Bouton clique");
	//switch (action.id)
	//{
	//case 1:
	//	verbose("Bouton SOLO");
	//	break;

	//default:
	//	break;
	//}
}

int main()
{
	VERBOSE = true;
	opengraphsize(WIDTH, HEIGHT);
	setbkcolor(LIGHTGRAY);
	cleardevice();
	verbose("Initialisation de la fenetre graphique");
	tests();
	getch();
	return 0;
}
