#include <iostream>
#include <array>
#include <string>
#include <iomanip>
#include "graphics.h"
#include "bataille_navale.h"

using namespace std;

int debugLevel = 0;

void verbose(string message, int level)
{
    if (level <= debugLevel)
    {
        cout << message << endl;
    }
}

int aleat(int a, int b)
{
    return a + (b - a + 1) * (rand() / ((double)RAND_MAX + 1));
}

void lireSouris(int &x, int &y)
{
    buttonhit();
    getmouse(x, y);
}

void dessinerBouton(const Bouton &B) // Works
{
    setcolor(B.couleur);
    setfillstyle(SOLID_FILL, B.couleur);
    bar(B.x1, B.y1, B.x2, B.y2);
    setbkcolor(B.couleur);
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(B.x1 + 10, B.y1 + 10, B.texte);
    verbose("Bouton dessine" + to_string(B.x1) + " " + to_string(B.y1) + " " + to_string(B.x2) + " " + to_string(B.y2) + " " + to_string(B.couleur) + " " + B.texte, DEBUG);
}

void dessinerGrille(const Grille &G) // Works + TODO
{
    setfillstyle(SOLID_FILL, WHITE);
    bar(G.x - G.cellWidth, G.y - G.cellWidth, G.x + G.width + 2, G.y + G.width + 2);
    setbkcolor(LIGHTGRAY);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    for (int i = 0; i < CASES; i++)
    {
        line(G.x, G.y + i * G.cellHeight, G.x + G.width, G.y + i * G.cellHeight);
        line(G.x + i * G.cellWidth, G.y, G.x + i * G.cellWidth, G.y + G.height);
        outtextxy(G.x + i * G.cellWidth + G.cellWidth / 2 - 5, G.y - G.cellHeight / 2, "A");
        outtextxy(G.x - G.cellWidth / 2, G.y + i * G.cellHeight + G.cellHeight / 2 - 5, "1");
    }
    setfillstyle(SOLID_FILL, BLUE);
    bar(G.x, G.y, G.x + G.width, G.y + G.height);
    setfillstyle(SOLID_FILL, BLACK);
    setbkcolor(BLACK);
    for (int i = 0; i <= CASES; i++)
    {
        line(G.x, G.y + i * G.cellHeight, G.x + G.width, G.y + i * G.cellHeight);
        line(G.x + i * G.cellWidth, G.y, G.x + i * G.cellWidth, G.y + G.height);
    }
    verbose("Grille dessinee" + to_string(G.x) + " " + to_string(G.y) + " " + to_string(G.width) + " " + to_string(G.height) + " " + to_string(G.cellWidth) + " " + to_string(G.cellHeight), DEBUG);
}

// void dessinerBateau(const Bateau &B, const Grille &G) // Works
// {
//     setcolor(DARKGRAY);
//     setfillstyle(SOLID_FILL, DARKGRAY);
//     if (B.orientation == HORIZ_DIR)
//     {
//         bar(G.x + B.x * G.cellWidth + 1, G.y + B.y * G.cellHeight + 1, G.x + (B.x + B.taille) * G.cellWidth, G.y + (B.y + 1) * G.cellHeight);
//     }
//     else if (B.orientation == VERT_DIR)
//     {
//         bar(G.x + B.x * G.cellWidth + 1, G.y + B.y * G.cellHeight + 1, G.x + (B.x + 1) * G.cellWidth, G.y + (B.y + B.taille) * G.cellHeight);
//     }
//     verbose("Bateau dessine" + to_string(B.x) + " " + to_string(B.y) + " " + to_string(B.taille) + " " + to_string(B.orientation), DEBUG);
// }

bool placerBateau(Bateau &B, Grille &G) // NOT Working
{
    bool libre = true;
    bool dirHorizontal = B.orientation == HORIZ_DIR;
    bool dirVertical = B.orientation == VERT_DIR;
    for (int i = 0; i < B.taille; i++)
    {
        if (G.tabGrille[B.x + i * dirVertical][B.y + i * dirHorizontal] != VIDE)
        {
            libre = false;
        }
    }
    if (libre)
    {
        for (int i = 0; i < B.taille; i++)
        {
            G.tabGrille[B.x + i * dirVertical][B.y + i * dirHorizontal] = B.id;
        }
        for (int i = -1; i <= B.taille * dirVertical + 1; i++)
        {
            for (int j = -1; j <= B.taille * dirHorizontal + 1; j++)
            {
                if (G.tabGrille[B.x + i][B.y + j] == VIDE && (B.x + i >= 0 && B.x + i < CASES) || (B.y + j >= 0 && B.y + j < CASES))
                {
                    G.tabGrille[B.x + i][B.y + j] = CEV_INTACTE;
                }
            }
        }
        if (G.tabGrille[B.x + B.taille * dirVertical][B.y + B.taille * dirHorizontal] == VIDE && B.x + B.taille * dirVertical < CASES)
        {
            G.tabGrille[B.x + B.taille * dirVertical][B.y + B.taille * dirHorizontal] = CEV_INTACTE;
        }
        if (G.tabGrille[B.x - 1 * dirVertical][B.y - 1 * dirHorizontal] == VIDE && B.x - 1 >= 0 && B.y - 1 >= 0)
        {
            G.tabGrille[B.x - 1 * dirVertical][B.y - 1 * dirHorizontal] = CEV_INTACTE;
        }
    }
    return libre;
}

void placerBateauxAleat(TAB_BATEAUX &T, Grille &G) // Works
{
    for (int i = 0; i < NB_BATEAUX_MAX; i++)
    {
        do
        {
            T[i].x = aleat(0, CASES - 1 - T[i].taille);
            T[i].y = aleat(0, CASES - 1 - T[i].taille);
            T[i].orientation = aleat(0, 1);
            verbose("Bateau " + to_string(i) + " : " + to_string(T[i].x) + " " + to_string(T[i].y) + " " + to_string(T[i].orientation), DEBUG);
        } while (!placerBateau(T[i], G));
    }
}

void placerBateauxJoueur(TAB_BATEAUX &T, Grille &G) // To test
{
    for (int i = 0; i < G.nbBateaux; i++)
    {
        do
        {
            Point p1, p2;
            lireSouris(p1.x, p1.y);
            lireSouris(p2.x, p2.y);
            T[i].x = min(p1.x, p2.x) / G.cellWidth;
            T[i].y = min(p1.y, p2.y) / G.cellHeight;
            T[i].orientation = (p1.x < p2.x) ? HORIZ_DIR : VERT_DIR;
            verbose("Bateau " + to_string(i) + " : " + to_string(T[i].x) + " " + to_string(T[i].y) + " " + to_string(T[i].orientation), DEBUG);
        } while (!placerBateau(T[i], G));
    }
}

void dessinerCase(int x, int y, const Grille &G) // Works
{
    int id = G.tabGrille[x][y];
    switch (id)
    {
    case VIDE:
        setcolor(BLUE);
        setfillstyle(SOLID_FILL, BLUE);
        bar(G.x + x * G.cellWidth + 1, G.y + y * G.cellHeight + 1, G.x + (x + 1) * G.cellWidth, G.y + (y + 1) * G.cellHeight);
        break;

    case CEV_TOUCHE:
        setcolor(WHITE);
        setbkcolor(BLUE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        outtextxy(G.x + x * G.cellWidth + G.cellWidth / 2, G.y + y * G.cellHeight + G.cellHeight / 1.5, "V");
        break;

    case RATE:
        setcolor(WHITE);
        setfillstyle(SOLID_FILL, WHITE);
        setbkcolor(WHITE);
        fillellipse(G.x + x * G.cellWidth + G.cellWidth / 2, G.y + y * G.cellHeight + G.cellHeight / 2, G.cellWidth / 7, G.cellHeight / 7);
        break;

    case TOUCHE:
        setcolor(LIGHTRED);
        setfillstyle(SOLID_FILL, LIGHTRED);
        bar(G.x + x * G.cellWidth + 1, G.y + y * G.cellHeight + 1, G.x + (x + 1) * G.cellWidth, G.y + (y + 1) * G.cellHeight);
        break;

    case COULE:
        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        bar(G.x + x * G.cellWidth + 1, G.y + y * G.cellHeight + 1, G.x + (x + 1) * G.cellWidth, G.y + (y + 1) * G.cellHeight);
        break;

    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        setcolor(LIGHTGRAY);
        setfillstyle(SOLID_FILL, LIGHTGRAY);
        bar(G.x + x * G.cellWidth + 1, G.y + y * G.cellHeight + 1, G.x + (x + 1) * G.cellWidth, G.y + (y + 1) * G.cellHeight);
        break;

    default:
        break;
    }
}

int tirer(int x, int y, Grille &G) // To test
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
    else if (id == CEV_INTACTE)
    {
        G.tabGrille[x][y] = CEV_TOUCHE;
    }
    return id;
}

void tirerJoueur(int &x, int &y, Grille &G) // To test
{
    do
    {
        lireSouris(x, y);
        x = (int)(x - G.x) / G.cellWidth;
        y = (int)(y - G.y) / G.cellHeight;
    } while (x < 0 || x >= CASES || y < 0 || y >= CASES || !tirer(x, y, G) > -1);
}

void tirerOrdi(int &x, int &y, bool modeDifficile, Grille &G) // TODO
{
    // Mode facile
    if (!modeDifficile)
    {
        bool modeHunter = true;
        // Tire une case sur deux de la grille tant que tout les bateaux ne sont pas touch�s
        for (int i = 0; i < G.nbBateaux; i++)
        {
            if (G.tabBateaux[i].state != TOUCHE || G.tabBateaux[i].state != COULE)
            {
                modeHunter = false;
                // Mode Hunter
                // Tire autour des bateaux touch�s
            }
        }
        // TODO
    }
    else
    {
        // TODO
    }
}

void initFenetre() // Works
{
    opengraphsize(WIDTH, HEIGHT);
    setbkcolor(WHITE);
    cleardevice();
}

void initBouton(Bouton &B, int x1, int y1, int x2, int y2, int couleur, const char *texte) // Works
{
    B = {x1, y1, x2, y2, couleur, texte};
}

void menu(bool &choixMultiJoueur, bool &choixDifficile, bool &choixTirSalves, bool &choixCaseEnVue, bool &choix6Bateaux) // TODO
{
    int x, y;
    Bouton boutonMultiJoueur, boutonSolo, boutonFacile, boutonDifficile, boutonTirSalves, boutonTirParCase, boutonCaseEnVue, bouton6Bateaux, bouton5Bateaux, boutonSuivant;
    // TODO
}

void initBateau(Bateau &B, int id, int size) // Works
{
    B.id = id;
    B.taille = size;
}

void initTabGrille(TAB_GRILLE &T) // Works
{
    for (int i = 0; i < CASES; i++)
    {
        for (int j = 0; j < CASES; j++)
        {
            T[i][j] = VIDE;
        }
    }
}

void initGrille(Grille &G, int x, int y, int nbBateaux, TAB_BATEAUX tabBateaux) // Works
{
    G.x = x;
    G.y = y;
    initTabGrille(G.tabGrille);
    G.nbBateaux = nbBateaux;
    G.tabBateaux = tabBateaux;
}

void initJoueur(Joueur &J, string nom, Grille grille) // Works
{
    J.nom = nom;
    J.grille = grille;
}

bool jeu(Joueur &J1, Joueur &J2, bool choixMultiJoueur, bool choixDifficile, bool choixTirSalves, bool choixCaseEnVue, bool choix6Bateaux) // TODO
{
    // TODO
}

void finPartie(Joueur &J1, Joueur &J2, bool victoireJ1) // TODO
{
    // TODO
}

int main()
{
    debugLevel = 2;
    initFenetre();
    verbose("Test", DEBUG);
    // Grille 1
    Grille G1;
    Bateau B1_1, B1_2, B1_3, B1_4, B1_5;
    initBateau(B1_1, 1, PORTE_AVION);
    initBateau(B1_2, 2, CROISEUR);
    initBateau(B1_3, 3, CONTRE_TORPILLEUR);
    initBateau(B1_4, 4, TORPILLEUR);
    initBateau(B1_5, 5, TORPILLEUR);
    TAB_BATEAUX TB1 = {B1_1, B1_2, B1_3, B1_4, B1_5};
    initGrille(G1, 200, 200, 5, TB1);
    // Grille 2
    Grille G2;
    Bateau B2_1, B2_2, B2_3, B2_4, B2_5;
    initBateau(B2_1, 1, PORTE_AVION);
    initBateau(B2_2, 2, CROISEUR);
    initBateau(B2_3, 3, CONTRE_TORPILLEUR);
    initBateau(B2_4, 4, TORPILLEUR);
    initBateau(B2_5, 5, TORPILLEUR);
    TAB_BATEAUX TB2 = {B2_1, B2_2, B2_3, B2_4, B2_5};
    initGrille(G2, 800, 200, 5, TB2);
    // Couleur de fond
    setbkcolor(LIGHTGRAY);
    cleardevice();

    /*Test dessinerBouton
    Bouton button;
    button.x1=100;
    button.x2=100;
    button.y1=100;
    button.y2=100;
    button.couleur=GREEN;
    button.texte="Suivant";
    dessinerBouton(button);*/

    // Test dessinerGrille
    dessinerGrille(G1);
    dessinerGrille(G2);

    // Test placerBateau
    // placerBateauxJoueur(G1.tabBateaux, G1);
    placerBateauxAleat(G2.tabBateaux, G2);
    
    for (int i = 0; i < CASES; i++)
    {
        for (int j = 0; j < CASES; j++)
        {
            dessinerCase(i, j, G2);
        }
    }


    // // Test dessinerCase
    G1.tabGrille = {{{COULE, CEV_INTACTE, CEV_TOUCHE, TOUCHE, RATE, VIDE, VIDE, VIDE, VIDE, VIDE},
                     {VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE},
                     {VIDE, 1, VIDE, VIDE, VIDE, VIDE, 3, 3, 3, 3},
                     {VIDE, 1, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE},
                     {VIDE, 1, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE},
                     {VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE},
                     {VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE},
                     {VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE},
                     {VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE},
                     {VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE}}};
    
    for (int i = 0; i < CASES; i++)
    {
        for (int j = 0; j < CASES; j++)
        {
            dessinerCase(i, j, G1);
        }
    }

    // // Test tirer
    // int x, y;
    // tirerJoueur(x, y, G1);
    // dessinerCase(x, y, G1);

    /*initTabGrille(TG);
    initGrille(G, 0, 0, TG, 1,TB);
    Joueur J;
    initJoueur(J, "Joueur 1", G);
    dessinerGrille(J.grille);
    dessinerBateau(J.grille.tabBateaux[0], J.grille);*/

    getch();

    //     bool choixMultiJoueur, choixDifficile, choixTirSalves, choixCaseEnVue, choix6Bateaux;
    //     Joueur J1, J2;
    //     initFenetre();
    //     menu(choixMultiJoueur, choixDifficile, choixTirSalves, choixCaseEnVue, choix6Bateaux);
    //     initJoueur(J1, "Joueur 1", initGrille(0, 0, initTabGrille()), choix6Bateaux ? 6 : 5, initTabBateaux(choix6Bateaux));
    //     initJoueur(J2, "Joueur 2", initGrille(0, 0, initTabGrille()), choix6Bateaux ? 6 : 5, initTabBateaux(choix6Bateaux));
    //     jeu(J1, J2, choixMultiJoueur, choixDifficile, choixTirSalves, choixCaseEnVue, choix6Bateaux);
    //     finPartie(J1, J2);
    return 0;
}
