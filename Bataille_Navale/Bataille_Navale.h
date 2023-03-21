#pragma once

typedef TAB = array<array<int, 10>, 10>;

struct Grille
{
	int x = 10;
	int y = 10;
	int width = 400;
	int height = 400;
	int cellWidth = width / 10;
	int cellHeight = height / 10;
	TAB tab;
};