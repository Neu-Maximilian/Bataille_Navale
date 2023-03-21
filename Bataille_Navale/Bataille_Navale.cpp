#include <iostream>
#include <array>
#include <string>
#include "graphics.h"
#include "bataille_navale.h"

using namespace std;

const int HEIGHT = 720;
const int WIDTH = 1280;

int main()
{
	cout << "Hello, World!" << endl;
	opengraphsize(HEIGHT,WIDTH);
	setbkcolor(RED);
	cleardevice();
	setcolor(WHITE);
	settextstyle(0, 0, 1);
	outtextxy(10, 10, "Hello, World!");
	getch();
	return 0;
}
