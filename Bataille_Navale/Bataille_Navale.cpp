#include <iostream>
#include <array>
#include <string>
#include <iomanip>
#include "graphics.h"
#include "bataille_navale.h"

using namespace std;

int aleat(int a, int b)
{
    return a + (b - a + 1) * (rand() / ((double)RAND_MAX + 1));
}

void lireSouris(int &x, int &y)
{
    buttonhit();
    getmouse(x, y);
}

void dessinerBouton(const Bouton &B)
{
    setcolor(B.couleur);
    setfillstyle(SOLID_FILL, B.couleur);
    bar(B.x1, B.y1, B.x2, B.y2);
    setbkcolor(B.couleur);
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(B.x1 + 10, B.y1 + 10, B.texte);
}

void dessinerGrille(const Grille &G)
{
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    bar(G.x, G.y, G.x + G.width, G.y + G.height);
    setcolor(BLACK);
    for (int i = 0; i < CASES; i++)
    {
        line(G.x + i * G.cellWidth, G.y, G.x + i * G.cellWidth, G.y + G.height);
        line(G.x, G.y + i * G.cellHeight, G.x + G.width, G.y + i * G.cellHeight);
    }
}

void dessinerBateau(const Bateau &B, const Grille &G)
{
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    if (B.orientation == HORIZ_DIR)
    {
        bar(G.x + B.x * G.cellWidth, G.y + B.y * G.cellHeight, G.x + (B.x + B.taille - 1) * G.cellWidth, G.y + (B.y + 1) * G.cellHeight);
    }
    else
    {
        bar(G.x + B.x * G.cellWidth, G.y + B.y * G.cellHeight, G.x + (B.x + 1) * G.cellWidth, G.y + (B.y + B.taille - 1) * G.cellHeight);
    }
}

bool placerBateau(Bateau &B, Grille &G)
{
    bool libre = true;
    bool estVertical = B.orientation == VERT_DIR;
    bool estHorizontal = B.orientation == HORIZ_DIR;
    for (int i = 0; i < B.taille; i++)
    {
        if (G.tabGrille[B.x + i * estHorizontal][B.y + i * estVertical] != VIDE)
        {
            libre = false;
        }
    }
    if (libre)
    {
        for (int i = 0; i < B.taille; i++)
        {
            G.tabGrille[B.x + i * estHorizontal][B.y + i * estVertical] = B.id;
        }
        for (int i = -1; i <= B.taille * estHorizontal; i++)
        {
            for (int j = -1; j <= B.taille * estVertical; j++)
            {
                if (G.tabGrille[B.x + i][B.y + j] == VIDE && (B.x + i >= 0 && B.x + i < CASES) || (B.y + j >= 0 && B.y + j < CASES))
                {
                    G.tabGrille[B.x + i][B.y + j] = CASE_EN_VUE;
                }
            }
        }
        if (G.tabGrille[B.x + B.taille * estHorizontal][B.y + B.taille * estVertical] == VIDE && B.x + B.taille * estHorizontal < CASES)
        {
            G.tabGrille[B.x + B.taille * estHorizontal][B.y + B.taille * estVertical] = CASE_EN_VUE;
        }
        if (G.tabGrille[B.x - 1 * estHorizontal][B.y - 1 * estVertical] == VIDE && B.x - 1 >= 0 && B.y - 1 >= 0)
        {
            G.tabGrille[B.x - 1 * estHorizontal][B.y - 1 * estVertical] = CASE_EN_VUE;
        }
    }
    return libre;
}

void placerBateauxAleat(TAB_BATEAUX &T, Grille &G)
{
    for (int i = 0; i < NB_BATEAUX_MAX; i++)
    {
        while (!placerBateau(T[i], G))
        {
            T[i].x = aleat(0, CASES - 1);
            T[i].y = aleat(0, CASES - 1);
            T[i].orientation = aleat(0, 1);
        }
    }
}

void placerBateauxJoueur(TAB_BATEAUX &T, Grille &G)
{
    for (int i = 0; i < NB_BATEAUX_MAX; i++)
    {
        while (!placerBateau(T[i], G))
        {
            Point p1, p2;
            lireSouris(p1.x, p1.y);
            lireSouris(p2.x, p2.y);
            T[i].x = min(p1.x, p2.x) / G.cellWidth;
            T[i].y = min(p1.y, p2.y) / G.cellHeight;
            T[i].orientation = (p1.x < p2.x) ? HORIZ_DIR : VERT_DIR;
        }
    }
}

void dessinerCase(int x, int y, const Grille &G)
{
    int id = G.tabGrille[x][y];
    switch (id)
    {
    case VIDE:
        setcolor(BLUE);
        setfillstyle(SOLID_FILL, BLUE);
        bar(G.x + x * G.cellWidth + 1, G.y + y * G.cellHeight + 1, G.x + (x + 1) * G.cellWidth - 1, G.y + (y + 1) * G.cellHeight - 1);
        break;

    case CASE_EN_VUE:
        setcolor(BLUE);
        setfillstyle(SOLID_FILL, BLUE);
        bar(G.x + x * G.cellWidth + 1, G.y + y * G.cellHeight + 1, G.x + (x + 1) * G.cellWidth - 1, G.y + (y + 1) * G.cellHeight - 1);
        setcolor(BLACK);
        setbkcolor(BLUE);
        settextstyle(SMALL_FONT, HORIZ_DIR, 2);
        outtextxy(G.x + x * G.cellWidth + 10, G.y + y * G.cellHeight + 10, "V");
        break;

    case RATE:
        setcolor(BLUE);
        setfillstyle(SOLID_FILL, BLUE);
        bar(G.x + x * G.cellWidth + 1, G.y + y * G.cellHeight + 1, G.x + (x + 1) * G.cellWidth - 1, G.y + (y + 1) * G.cellHeight - 1);
        setcolor(BLACK);
        setfillstyle(SOLID_FILL, BLACK);
        fillellipse(G.x + x * G.cellWidth + G.cellWidth / 2, G.y + y * G.cellHeight + G.cellHeight / 2, G.cellWidth / 4, G.cellHeight / 4);
        break;

    case TOUCHE:
        setcolor(LIGHTRED);
        setfillstyle(SOLID_FILL, LIGHTRED);
        bar(G.x + x * G.cellWidth + 1, G.y + y * G.cellHeight + 1, G.x + (x + 1) * G.cellWidth - 1, G.y + (y + 1) * G.cellHeight - 1);
        break;

    case COULE:
        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        bar(G.x + x * G.cellWidth + 1, G.y + y * G.cellHeight + 1, G.x + (x + 1) * G.cellWidth - 1, G.y + (y + 1) * G.cellHeight - 1);
        break;

    default:
        break;
    }
}

int tirer(int x, int y, Grille &G)
{
    int id = G.tabGrille[x][y];
    if (id > 0)
    {
        G.tabGrille[x][y] = TOUCHE;
        G.tabBateaux[id].state = TOUCHE;
        bool coule = true;
        bool estVertical = G.tabBateaux[id].orientation == VERT_DIR;
        bool estHorizontal = G.tabBateaux[id].orientation == HORIZ_DIR;
        for (int i = 0; i < G.tabBateaux[id].taille; i++)
        {
            if (G.tabGrille[G.tabBateaux[id].x + i * estHorizontal][G.tabBateaux[id].y + i * estVertical] != TOUCHE)
            {
                coule = false;
            }
        }
        if (coule)
        {
            G.tabBateaux[id].state = COULE;
        }
    }
    else if (id == VIDE)
    {
        G.tabGrille[x][y] = RATE;
    }
    return id;
}

void tirerJoueur(int &x, int &y, Grille &G)
{
    do
    {
        lireSouris(x, y);
        x = (int)(x - G.x) / G.cellWidth;
        y = (int)(y - G.y) / G.cellHeight;
    } while (x < 0 || x >= CASES || y < 0 || y >= CASES || !tirer(x, y, G) == VIDE || !tirer(x, y, G) == CASE_EN_VUE);
}

void tirerOrdi(int &x, int &y, bool modeDifficile, Grille &G)
{
    // Mode facile
    if (!modeDifficile)
    {
        bool modeHunter = true;
        // Tire une case sur deux de la grille tant que tout les bateaux ne sont pas touchés
        for (int i = 0; i < G.nbBateaux; i++)
        {
            if (G.tabBateaux[i].state != TOUCHE || G.tabBateaux[i].state != COULE)
            {
                modeHunter = false;
                // Mode Hunter
                // Tire autour des bateaux touchés
            }
        }
        // TODO
    }
    else
    {
        // TODO
    }
}

void initFenetre()
{
    opengraphsize(WIDTH, HEIGHT);
    setbkcolor(WHITE);
    cleardevice();
}

void initBouton(Bouton &B, int x1, int y1, int x2, int y2, int couleur, const char *texte)
{
    B = {x1, y1, x2, y2, couleur, texte};
}

void menu(bool &choixMultiJoueur, bool &choixDifficile, bool &choixTirSalves, bool &choixCaseEnVue, bool &choix6Bateaux)
{
    int x, y;
    Bouton boutonMultiJoueur, boutonSolo, boutonFacile, boutonDifficile, boutonTirSalves, boutonTirParCase, boutonCaseEnVue, bouton6Bateaux, bouton5Bateaux, boutonSuivant;
    // TODO
}

void initBateau(Bateau &B, int id, int x, int y, int size, int orientation)
{
    B = {id, x, y, size, orientation, VIDE};
}

void initTabGrille(TAB_GRILLE &T)
{
    for (int i = 0; i < CASES; i++)
    {
        for (int j = 0; j < CASES; j++)
        {
            T[i][j] = VIDE;
        }
    }
}

void initGrille(Grille& G, int x, int y, TAB_GRILLE tabGrille)
{
    G = {x, y, tabGrille, 0};
}

void initJoueur(Joueur& J, string nom, Grille grille, int nbBateaux, TAB_BATEAUX tabBateaux)
{
    J = {nom, grille, nbBateaux, tabBateaux};
}

void jeu(Joueur& J1, Joueur& J2, bool choixMultiJoueur, bool choixDifficile, bool choixTirSalves, bool choixCaseEnVue, bool choix6Bateaux)
{
    // TODO
}

void finPartie(Joueur& J1, Joueur& J2)
{
    // TODO
}
