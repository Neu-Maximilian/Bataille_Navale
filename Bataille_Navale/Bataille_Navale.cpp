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

void dessinerBateauCoule(const Bateau &B, const Grille &G)
{
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    if (B.orientation == 0)
    {
        bar(B.x * 40 + G.x, B.y * 40 + G.y, B.x * 40 + G.x + B.taille * 40, B.y * 40 + G.y + 40);
    }
    else
    {
        bar(B.x * 40 + G.x, B.y * 40 + G.y, B.x * 40 + G.x + 40, B.y * 40 + G.y + B.taille * 40);
    }
}

void dessinerBouton(const Bouton &B) // ok
{
    setcolor(B.couleur);
    setfillstyle(SOLID_FILL, B.couleur);
    bar(B.x1, B.y1, B.x2, B.y2);
    setbkcolor(B.couleur);
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, B.texte_taille);
    outtextxy(B.tx1, B.ty1, B.texte);
    verbose("Bouton dessine" + to_string(B.x1) + " " + to_string(B.y1) + " " + to_string(B.x2) + " " + to_string(B.y2) + " " + to_string(B.couleur) + " " + B.texte, DEBUG);
}

void dessinerContour(const Bouton &B, int Couleur) // ok
{
    setcolor(Couleur);
    setbkcolor(Couleur);
    setlinestyle(SOLID_LINE, 0, 5);
    rectangle(B.x1 - 2, B.y1 - 2, B.x2 + 2, B.y2 + 2);
    verbose("Contour dessine" + to_string(B.x1) + " " + to_string(B.y1) + " " + to_string(B.x2) + " " + to_string(B.y2) + " " + to_string(B.couleur), DEBUG);
}

void dessinerCroix(const Bouton &B, int Couleur) // ok
{
    setcolor(Couleur);
    setbkcolor(Couleur);
    setlinestyle(SOLID_LINE, 0, 1);
    line(B.x1, B.y1, B.x2, B.y2);
    line(B.x1, B.y2, B.x2, B.y1);
}

void dessinerGrille(const Grille &G) // ok
{

    setfillstyle(SOLID_FILL, WHITE);
    setlinestyle(SOLID_LINE, 0, 1);
    bar(G.x - G.cellWidth, G.y - G.cellWidth, G.x + G.width + 2, G.y + G.width + 2);
    setbkcolor(LIGHTGRAY);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    for (int i = 0; i < CASES; i++)
    {
        line(G.x, G.y + i * G.cellHeight, G.x + G.width, G.y + i * G.cellHeight);
        line(G.x + i * G.cellWidth, G.y, G.x + i * G.cellWidth, G.y + G.height);
    }

    setcolor(DARKGRAY);
    setbkcolor(WHITE);
    outtextxy(G.x + 0 * G.cellWidth + G.cellWidth / 2 - 7, G.y - G.cellHeight / 2 - 8, "A");
    outtextxy(G.x - G.cellWidth / 2 - 8, G.y + 0 * G.cellHeight + G.cellHeight / 2 - 7, "1");
    outtextxy(G.x + 1 * G.cellWidth + G.cellWidth / 2 - 7, G.y - G.cellHeight / 2 - 8, "B");
    outtextxy(G.x - G.cellWidth / 2 - 8, G.y + 1 * G.cellHeight + G.cellHeight / 2 - 7, "2");
    outtextxy(G.x + 2 * G.cellWidth + G.cellWidth / 2 - 7, G.y - G.cellHeight / 2 - 8, "C");
    outtextxy(G.x - G.cellWidth / 2 - 8, G.y + 2 * G.cellHeight + G.cellHeight / 2 - 7, "3");
    outtextxy(G.x + 3 * G.cellWidth + G.cellWidth / 2 - 7, G.y - G.cellHeight / 2 - 8, "D");
    outtextxy(G.x - G.cellWidth / 2 - 8, G.y + 3 * G.cellHeight + G.cellHeight / 2 - 7, "4");
    outtextxy(G.x + 4 * G.cellWidth + G.cellWidth / 2 - 7, G.y - G.cellHeight / 2 - 8, "E");
    outtextxy(G.x - G.cellWidth / 2 - 8, G.y + 4 * G.cellHeight + G.cellHeight / 2 - 7, "5");
    outtextxy(G.x + 5 * G.cellWidth + G.cellWidth / 2 - 7, G.y - G.cellHeight / 2 - 8, "F");
    outtextxy(G.x - G.cellWidth / 2 - 8, G.y + 5 * G.cellHeight + G.cellHeight / 2 - 7, "6");
    outtextxy(G.x + 6 * G.cellWidth + G.cellWidth / 2 - 7, G.y - G.cellHeight / 2 - 8, "G");
    outtextxy(G.x - G.cellWidth / 2 - 8, G.y + 6 * G.cellHeight + G.cellHeight / 2 - 7, "7");
    outtextxy(G.x + 7 * G.cellWidth + G.cellWidth / 2 - 7, G.y - G.cellHeight / 2 - 8, "H");
    outtextxy(G.x - G.cellWidth / 2 - 8, G.y + 7 * G.cellHeight + G.cellHeight / 2 - 7, "8");
    outtextxy(G.x + 8 * G.cellWidth + G.cellWidth / 2 - 7, G.y - G.cellHeight / 2 - 8, "I");
    outtextxy(G.x - G.cellWidth / 2 - 8, G.y + 8 * G.cellHeight + G.cellHeight / 2 - 7, "9");
    outtextxy(G.x + 9 * G.cellWidth + G.cellWidth / 2 - 7, G.y - G.cellHeight / 2 - 8, "J");
    outtextxy(G.x - G.cellWidth / 2 - 16, G.y + 9 * G.cellHeight + G.cellHeight / 2 - 7, "10");

    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLUE);
    bar(G.x, G.y, G.x + G.width, G.y + G.height);
    setfillstyle(SOLID_FILL, BLACK);
    setbkcolor(BLACK);
    for (int i = 0; i <= CASES; i++)
    {
        line(G.x, G.y + i * G.cellHeight, G.x + G.width, G.y + i * G.cellHeight);
        line(G.x + i * G.cellWidth, G.y, G.x + i * G.cellWidth, G.y + G.height);
    }

    setcolor(LIGHTGRAY);
    for (int i = 0; i < CASES; i++)
    {
        line(G.x + i * G.cellHeight, G.y - 40, G.x + i * G.cellHeight, G.y);
        line(G.x - 40, G.y + i * G.cellWidth, G.x, G.y + i * G.cellWidth);
    }

    verbose("Grille dessinee" + to_string(G.x) + " " + to_string(G.y) + " " + to_string(G.width) + " " + to_string(G.height) + " " + to_string(G.cellWidth) + " " + to_string(G.cellHeight), DEBUG);
}

void afficherCacheEcran(const int &numero_joueur) // ok
{
    setcolor(DARKGRAY);
    setbkcolor(LIGHTGRAY);
    cleardevice();
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 6);
    if (numero_joueur == 1)
    {
        outtextxy(345, 310, "Tour du joueur 1");
    }
    else
    {
        outtextxy(345, 310, "Tour du joueur 2");
    }
}

void afficherDeuxGrilles(Joueur &Joueur_POV, Joueur &J2) // ok
{
    setbkcolor(LIGHTGRAY);
    cleardevice();
    dessinerGrille(J2.grille);
    dessinerGrille(Joueur_POV.grille);
    int laCase;
    for (int i = 0; i < CASES; i++)
    {
        for (int k = 0; k < CASES; k++)
        {
            laCase = Joueur_POV.grille.tabGrille[i][k];
            if (laCase != VIDE && laCase != CEV_INTACTE || (1 <= laCase && laCase <= Joueur_POV.grille.nbBateaux))
            {
                dessinerCase(i, k, Joueur_POV.grille);
            }
        }
        for (int i = 0; i < Joueur_POV.grille.nbBateaux; i++)
        {
            if (Joueur_POV.grille.tabBateaux[i].state == COULE)
            {
                dessinerBateauCoule(Joueur_POV.grille.tabBateaux[i], Joueur_POV.grille);
            }
        }
    }

    for (int i = 0; i < CASES; i++)
    {
        for (int k = 0; k < CASES; k++)
        {
            laCase = J2.grille.tabGrille[i][k];
            if (!(1 <= laCase && laCase <= J2.grille.nbBateaux))
            {
                if (laCase != VIDE && laCase != CEV_INTACTE)
                {
                    dessinerCase(i, k, J2.grille);
                }
            }
        }
        for (int i = 0; i < J2.grille.nbBateaux; i++)
        {
            if (J2.grille.tabBateaux[i].state == COULE)
            {
                dessinerBateauCoule(J2.grille.tabBateaux[i], J2.grille);
            }
        }
    }
    setcolor(DARKGRAY);
    setbkcolor(LIGHTGRAY);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(Joueur_POV.grille.x + Joueur_POV.grille.height / 2 - 170, Joueur_POV.grille.y + Joueur_POV.grille.height + 5, "Votre grille de jeu");
    outtextxy(J2.grille.x + J2.grille.height / 2 - 195, J2.grille.y + J2.grille.height + 5, "Grille de l'adversaire");
}

void modifCEV(const Bateau &B, Grille &G)
{
    int ligne = B.x;
    int colonne = B.y;
    if (B.orientation == VERT_DIR)
    {
        for (int l = -1; l < 2; l++)
        {
            for (int c = 0; c < B.taille; c++)
            {
                if (ligne + l >= 0 && ligne + l < CASES && colonne + c >= 0 && colonne + c < CASES && G.tabGrille[ligne + l][colonne + c] == VIDE)
                {
                    G.tabGrille[ligne + l][colonne + c] = CEV_INTACTE;
                }
            }
        }
        if (colonne - 1 >= 0)
        {
            G.tabGrille[ligne][colonne - 1] = CEV_INTACTE;
        }
        if (colonne + B.taille < CASES)
        {
            G.tabGrille[ligne][colonne + B.taille] = CEV_INTACTE;
        }
    }
    else if (B.orientation == HORIZ_DIR)
    {
        for (int l = 0; l < B.taille; l++)
        {
            for (int c = -1; c < 2; c++)
            {
                if (ligne + l >= 0 && ligne + l < CASES && colonne + c >= 0 && colonne + c < CASES && G.tabGrille[ligne + l][colonne + c] == VIDE)
                {
                    G.tabGrille[ligne + l][colonne + c] = CEV_INTACTE;
                }
            }
        }
        if (ligne - 1 >= 0)
        {
            G.tabGrille[ligne - 1][colonne] = CEV_INTACTE;
        }
        if (ligne + B.taille < CASES)
        {
            G.tabGrille[ligne + B.taille][colonne] = CEV_INTACTE;
        }
    }
}

bool placerBateau(Bateau &B, Grille &G) // NOT Working
{
    bool libre = true;
    if (B.orientation == HORIZ_DIR)
    {
        for (int i = 0; i < B.taille; i++)
        {
            if (G.tabGrille[B.x + i][B.y] != VIDE || B.x + i >= CASES || B.x + i < 0)
            {
                libre = false;
            }
        }
        if (libre)
        {
            for (int i = 0; i < B.taille; i++)
            {
                G.tabGrille[B.x + i][B.y] = B.id;
            }
            modifCEV(B, G);
        }
    }
    else if (B.orientation == VERT_DIR)
    {
        for (int i = 0; i < B.taille; i++)
        {
            if (G.tabGrille[B.x][B.y + i] != VIDE || B.y + i >= CASES || B.y + i < 0)
            {
                libre = false;
            }
        }
        if (libre)
        {
            for (int i = 0; i < B.taille; i++)
            {
                G.tabGrille[B.x][B.y + i] = B.id;
            }
            modifCEV(B, G);
        }
    }
    return libre;
}

void placerBateauxAleat(TAB_BATEAUX &T, Grille &G)
{
    for (int i = 0; i < G.nbBateaux; i++)
    {
        do
        {
            T[i].x = aleat(0, CASES - 1);
            T[i].y = aleat(0, CASES - 1);
            T[i].orientation = aleat(0, 1);
        } while (!placerBateau(T[i], G));
    }
    for (int i = 0; i < CASES; i++)
    {
        for (int j = 0; j < CASES; j++)
        {
            dessinerCase(i, j, G);
        }
    }
}

void afficherPlacementInvalide(const int &i, TAB_BATEAUX &T) // affiche le texte placement invalide d'un bateau
{
    setcolor(LIGHTGRAY);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(WIDTH / 2 - 550, HEIGHT - 110, WIDTH / 2 + 550, HEIGHT + 100);

    setcolor(DARKGRAY);
    setbkcolor(LIGHTGRAY);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    string str = "Placement du bateau invalide : " + T[i].nom + " (" + to_string(T[i].taille) + " cases)";
    const char *c = str.c_str();
    outtextxy(WIDTH / 2 - 450, HEIGHT - 80, c);
}

void placerBateauxJoueur(TAB_BATEAUX &T, Grille &G) // To test
{
    for (int i = 0; i < G.nbBateaux; i++)
    {
        bool placee = false;
        int k = 0;
        do
        {
            if (!placee && k != 0)
            {
                afficherPlacementInvalide(i, T);
            }
            else
            {
                setcolor(LIGHTGRAY);
                setfillstyle(SOLID_FILL, LIGHTGRAY);
                bar(WIDTH / 2 - 550, HEIGHT - 110, WIDTH / 2 + 550, HEIGHT + 100);

                setcolor(DARKGRAY);
                setbkcolor(LIGHTGRAY);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
                string str = "Placement du " + T[i].nom + " (" + to_string(T[i].taille) + " cases)";
                const char *c = str.c_str();
                outtextxy(WIDTH / 2 - 300, HEIGHT - 80, c);
            }

            int x1, y1, x2, y2;
            lireSouris(x1, y1);
            lireSouris(x2, y2);
            T[i].x = (int)(min(x1, x2) - G.x) / G.cellWidth;
            T[i].y = (int)(min(y1, y2) - G.y) / G.cellHeight;
            T[i].orientation = (abs(x1 - x2) < abs(y1 - y2)) ? VERT_DIR : HORIZ_DIR;
            placee = placerBateau(T[i], G);

            if (!placee)
            {
                afficherPlacementInvalide(i, T);
                k++;
            }
        } while (!placee);
        for (int i = 0; i < CASES; i++)
        {
            for (int j = 0; j < CASES; j++)
            {
                dessinerCase(i, j, G);
            }
        }
    }
}

void dessinerCase(int x, int y, const Grille &G) // ok
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
        setcolor(GREEN);
        setbkcolor(BLUE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(G.x + x * G.cellWidth + 12, G.y + y * G.cellHeight + 13, "V");
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

int tirer(const int &x, const int &y, Grille &G, const bool &choixCaseEnVue) // ok
{
    if (x < 0 || x >= CASES || y < 0 || y >= CASES)
        return RATE;
    int id = G.tabGrille[x][y];
    cout << G.tabGrille[x][y];
    setcolor(LIGHTGRAY);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(WIDTH / 2 - 80, G.y + G.height / 2 - 50, WIDTH / 2 + 70, G.y + G.height / 2 + 50);
    if (id > 0)
    {
        if (G.tabBateaux[id - 1].bateauToucheDeuxFois == false && G.tabBateaux[id - 1].state == TOUCHE)
        {
            G.tabBateaux[id - 1].bateauToucheDeuxFois = true;
        }
        G.tabGrille[x][y] = TOUCHE;
        G.tabBateaux[id - 1].state = TOUCHE;
        bool bateau_coule = true;
        int i = 0;
        int taille = G.tabBateaux[id - 1].taille;
        int x_bateau = G.tabBateaux[id - 1].x;
        int y_bateau = G.tabBateaux[id - 1].y;
        if (G.tabBateaux[id - 1].orientation == 0) // si le bateau est horizontal
        {
            while (i < taille && bateau_coule == true)
            {
                if (G.tabGrille[x_bateau + i][y_bateau] != TOUCHE)
                {
                    cout << G.tabGrille[x_bateau + i][y_bateau];
                    bateau_coule = false;
                }
                i++;
            }
        }
        else // si bateau vertical
        {
            while (i < taille && bateau_coule == true)
            {
                if (G.tabGrille[x_bateau][y_bateau + i] != TOUCHE)
                {
                    bateau_coule = false;
                }
                i++;
            }
        }
        if (bateau_coule)
        {
            G.tabBateaux[id - 1].state = COULE;
            if (G.tabBateaux[id - 1].orientation == 0)
            {
                for (int i = x; i < taille; i++)
                {
                    G.tabGrille[i][y] = COULE;
                }
            }
            else
            {
                for (int i = y; i < taille; i++)
                {
                    G.tabGrille[x][i] = COULE;
                }
            }
            dessinerBateauCoule(G.tabBateaux[id - 1], G);
            setcolor(DARKGRAY);
            setbkcolor(LIGHTGRAY);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(WIDTH / 2 - 45, HEIGHT / 2, "Coul�");
        }
        else
        {
            dessinerCase(x, y, G);
            setcolor(DARKGRAY);
            setbkcolor(LIGHTGRAY);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(WIDTH / 2 - 53, HEIGHT / 2, "Touch�");
        }
    }
    else if ((id == VIDE) || (!(choixCaseEnVue) && (id == CEV_INTACTE)))
    {
        G.tabGrille[x][y] = RATE;
        dessinerCase(x, y, G);
        setcolor(DARKGRAY);
        setbkcolor(LIGHTGRAY);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(WIDTH / 2 - 37, HEIGHT / 2, "Rat�");
    }
    else if ((choixCaseEnVue == true) && (id == CEV_INTACTE))
    {
        G.tabGrille[x][y] = CEV_TOUCHE;
        dessinerCase(x, y, G);
        setcolor(DARKGRAY);
        setbkcolor(LIGHTGRAY);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(WIDTH / 2 - 37, HEIGHT / 2 - 10, "Case");
        outtextxy(WIDTH / 2 - 53, HEIGHT / 2 + 10, "en vue");
    }
    return id;
}

void tirerJoueur(int &x, int &y, Grille &G, const bool &choixCaseEnVue) // ok
{
    do
    {
        lireSouris(x, y);
        x = (int)(x - G.x) / G.cellWidth;
        y = (int)(y - G.y) / G.cellHeight;
    } while (x < 0 || x >= CASES || y < 0 || y >= CASES || tirer(x, y, G, choixCaseEnVue) < CEV_INTACTE);
}

// Nouveau 27.05

bool bateauxDecouverts(const Grille &G) // renvoie true si tous les bateaux ont �t� touch�s
{
    bool bateauxTousDecouverts = true;
    int i = 0;
    while (i < G.nbBateaux)
    {
        if (G.tabBateaux[i].state != TOUCHE && G.tabBateaux[i].state != COULE)
        {
            bateauxTousDecouverts = false;
        }
        i++;
    }
    return bateauxTousDecouverts;
}

void coulerUnBateau(int &x, int &y, int &x_touche, int &y_touche, int &n, int &s, int &e, int &o, bool &nord, bool &sud, bool &est, bool &ouest, const int &i, Grille &G, const bool &choixCaseEnVue) // coule un bateau
{
    if (G.tabBateaux[i].directionTrouve == false && G.tabBateaux[i].bateauToucheDeuxFois == false)
    {
        x_touche = G.tabBateaux[i].x;
        y_touche = G.tabBateaux[i].y;
        if (G.tabBateaux[i].orientation == 0) // trouve une case touchee du bateau
        {
            while (x_touche < G.tabBateaux[i].x + G.tabBateaux[i].taille && G.tabGrille[x_touche][y_touche] != TOUCHE)
            {
                x_touche++;
            }

            while (y_touche < G.tabBateaux[i].y + G.tabBateaux[i].taille && G.tabGrille[x_touche][y_touche] != TOUCHE)
            {
                y_touche++;
            }

            n = y_touche - 1;
            s = y_touche + 1;
            e = x_touche + 1;
            o = x_touche - 1;

            if (n < 0 || n >= CASES || G.tabGrille[x_touche][n] < CEV_INTACTE)
            {
                nord = false;
            }
            if (s < 0 || s >= CASES || G.tabGrille[x_touche][s] < CEV_INTACTE)
            {
                sud = false;
            }
            if (e < 0 || e >= CASES || G.tabGrille[e][y_touche] < CEV_INTACTE)
            {
                est = false;
            }
            if (o < 0 || o >= CASES || G.tabGrille[o][y_touche] < CEV_INTACTE)
            {
                ouest = false;
            }

            if (nord == true) // si la case au nord n'est pas hors champ
            {
                tirer(x_touche, n, G, choixCaseEnVue);
                if (G.tabGrille[x_touche][n] == TOUCHE)
                {
                    G.tabBateaux[i].directionTrouve = true;
                }
            }
            else
            {
                if (sud == true)
                {
                    tirer(x_touche, s, G, choixCaseEnVue);
                    if (G.tabGrille[x_touche][s] == TOUCHE)
                    {
                        G.tabBateaux[i].directionTrouve = true;
                    }
                }
                else
                {
                    if (est == true)
                    {
                        tirer(e, y_touche, G, choixCaseEnVue);
                        if (G.tabGrille[e][y_touche] == TOUCHE) // est
                        {
                            G.tabBateaux[i].directionTrouve = true;
                        }
                    }
                    else
                    {
                        if (ouest == true)
                        {
                            tirer(o, y_touche, G, choixCaseEnVue);
                            if (G.tabGrille[o][y_touche] == TOUCHE) // ouest
                            {
                                G.tabBateaux[i].directionTrouve = true;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            x_touche = G.tabBateaux[i].x;
            y_touche = G.tabBateaux[i].y;

            while (y_touche < G.tabBateaux[i].y + G.tabBateaux[i].taille && G.tabGrille[x_touche][y_touche] != TOUCHE)
            {
                y_touche++;
            }

            while (x_touche < G.tabBateaux[i].x + G.tabBateaux[i].taille && G.tabGrille[x_touche][y_touche] != TOUCHE)
            {
                x_touche++;
            }

            n = y_touche - 1;
            s = y_touche + 1;
            e = x_touche + 1;
            o = x_touche - 1;

            if (n < 0 || n >= CASES || G.tabGrille[x_touche][n] < CEV_INTACTE)
            {
                nord = false;
            }
            if (s < 0 || s >= CASES || G.tabGrille[x_touche][s] < CEV_INTACTE)
            {
                sud = false;
            }
            if (e < 0 || e >= CASES || G.tabGrille[e][y_touche] < CEV_INTACTE)
            {
                est = false;
            }
            if (o < 0 || o >= CASES || G.tabGrille[o][y_touche] < CEV_INTACTE)
            {
                ouest = false;
            }

            if (nord == true) // si la case au nord n'est pas hors champ
            {
                tirer(x_touche, n, G, choixCaseEnVue);
                if (G.tabGrille[x_touche][n] == TOUCHE)
                {
                    G.tabBateaux[i].directionTrouve = true;
                }
            }
            else
            {
                if (sud == true)
                {
                    tirer(x_touche, s, G, choixCaseEnVue);
                    if (G.tabGrille[x_touche][s] == TOUCHE)
                    {
                        G.tabBateaux[i].directionTrouve = true;
                    }
                }
                else
                {
                    if (est == true)
                    {
                        tirer(e, y_touche, G, choixCaseEnVue);
                        if (G.tabGrille[e][y_touche] == TOUCHE) // est
                        {
                            G.tabBateaux[i].directionTrouve = true;
                        }
                    }
                    else
                    {
                        if (ouest == true)
                        {
                            tirer(o, y_touche, G, choixCaseEnVue);
                            if (G.tabGrille[o][y_touche] == TOUCHE) // ouest
                            {
                                G.tabBateaux[i].directionTrouve = true;
                            }
                        }
                    }
                }
            }
        }
    }
    else // une fois qu'on a trouv� la direction du bateau
    {
        if (G.tabBateaux[i].orientation == 0)
        {
            y = G.tabBateaux[i].y;
            do
            {
                x = aleat(G.tabBateaux[i].x - 1, G.tabBateaux[i].x + G.tabBateaux[i].taille);
            } while (x < 0 || x >= CASES || tirer(x, y, G, choixCaseEnVue) < CEV_INTACTE);
        }
        else
        {
            x = G.tabBateaux[i].x;
            do
            {
                y = aleat(G.tabBateaux[i].y - 1, G.tabBateaux[i].y + G.tabBateaux[i].taille);
            } while (y < 0 || y >= CASES || tirer(x, y, G, choixCaseEnVue) < CEV_INTACTE);
        }
    }
}

void tirHasard(int &x, int &y, Grille &G, const bool &choixCaseEnVue) // tir au hasard une case sur deux
{
    do
    {
        x = aleat(0, 9);
        if (x % 2 == 0)
        {
            do
            {
                y = aleat(1, 9);
            } while (y % 2 == 0);
        }
        else
        {
            do
            {
                y = aleat(0, 8);
            } while (y % 2 != 0);
        }
    } while (tirer(x, y, G, choixCaseEnVue) < CEV_INTACTE);
}

void trouverUnBateau(int &x, int &y, int &n, int &s, int &e, int &o, bool &nord, bool &sud, bool &est, bool &ouest, Grille &G, bool &trouve, const bool &choixCaseEnVue) // cherche � toucher un bateau � partir d'une case en vue
{
    n = y - 1;
    s = y + 1;
    e = x + 1;
    o = x - 1;

    if (n < 0 || n >= CASES || G.tabGrille[x][n] < CEV_INTACTE)
    {
        nord = false;
    }
    if (s < 0 || s >= CASES || G.tabGrille[x][s] < CEV_INTACTE)
    {
        sud = false;
    }
    if (e < 0 || e >= CASES || G.tabGrille[e][y] < CEV_INTACTE)
    {
        est = false;
    }
    if (o < 0 || o >= CASES || G.tabGrille[o][y] < CEV_INTACTE)
    {
        ouest = false;
    }

    if (nord == true) // si la case au nord n'est pas hors champ
    {
        tirer(x, n, G, choixCaseEnVue);
        if (G.tabGrille[x][n] == TOUCHE)
        {
            trouve = true;
        }
    }
    else
    {
        if (sud == true)
        {
            tirer(x, s, G, choixCaseEnVue);
            if (G.tabGrille[x][s] == TOUCHE)
            {
                trouve = true;
            }
        }
        else
        {
            if (est == true)
            {
                tirer(e, y, G, choixCaseEnVue);
                if (G.tabGrille[e][y] == TOUCHE) // est
                {
                    trouve = true;
                }
            }
            else
            {
                if (ouest == true)
                {
                    tirer(o, y, G, choixCaseEnVue);
                    if (G.tabGrille[o][y] == TOUCHE) // ouest
                    {
                        trouve = true;
                    }
                }
            }
        }
    }
}

void modifenCEV_TOUCHE_INUTILE(const Bateau &B, Grille &G) // modifie les cases en vue autour du bateau coul� pour que l'ordinateur ne tire pas autour du bateau coul� sur ces cases en vue
{
    int ligne = B.x;
    int colonne = B.y;
    if (B.orientation == VERT_DIR)
    {
        for (int l = -1; l < 2; l++)
        {
            for (int c = 0; c < B.taille; c++)
            {
                if (ligne + l >= 0 && ligne + l < CASES && colonne + c >= 0 && colonne + c < CASES && (G.tabGrille[ligne + l][colonne + c] == VIDE || G.tabGrille[ligne + l][colonne + c] == CEV_INTACTE || G.tabGrille[ligne + l][colonne + c] == CEV_TOUCHE))
                {
                    G.tabGrille[ligne + l][colonne + c] = CEV_TOUCHE_INUTILE;
                }
            }
        }
        if (colonne - 1 >= 0)
        {
            G.tabGrille[ligne][colonne - 1] = CEV_TOUCHE_INUTILE;
        }
        if (colonne + B.taille < CASES)
        {
            G.tabGrille[ligne][colonne + B.taille] = CEV_TOUCHE_INUTILE;
        }
    }
    else if (B.orientation == HORIZ_DIR)
    {
        for (int l = 0; l < B.taille; l++)
        {
            for (int c = -1; c < 2; c++)
            {
                if (ligne + l >= 0 && ligne + l < CASES && colonne + c >= 0 && colonne + c < CASES && (G.tabGrille[ligne + l][colonne + c] == VIDE || G.tabGrille[ligne + l][colonne + c] == CEV_INTACTE || G.tabGrille[ligne + l][colonne + c] == CEV_TOUCHE))
                {
                    G.tabGrille[ligne + l][colonne + c] = CEV_TOUCHE_INUTILE;
                }
            }
        }
        if (ligne - 1 >= 0)
        {
            G.tabGrille[ligne - 1][colonne] = CEV_TOUCHE_INUTILE;
        }
        if (ligne + B.taille < CASES)
        {
            G.tabGrille[ligne + B.taille][colonne] = CEV_TOUCHE_INUTILE;
        }
    }
}

void tirerOrdi(int &x, int &y, Grille &G, const bool &modeDifficile, const bool &choixCaseEnVue, bool &bateauTrouve)
{
    int i = 0;
    int x_touche, y_touche;
    int n, s, e, o;
    bool bateauxTousDecouverts = bateauxDecouverts(G);
    bool nord = true, sud = true, est = true, ouest = true;
    if (!modeDifficile) // si on n'est pas en mode difficile
    {
        if (bateauxTousDecouverts == false) // si tous les bateaux n'ont pas �t� touch�
        {
            tirHasard(x, y, G, false);
        }
        else // si tous les bateaux ont �t� touch�s: on essaie de couler un bateau
        {
            while (i < G.nbBateaux && G.tabBateaux[i].state == COULE) // trouve le num�ro du bateau � couler
            {
                i++;
            }
            coulerUnBateau(x, y, x_touche, y_touche, n, s, e, o, nord, sud, est, ouest, i, G, choixCaseEnVue);
        }
    }
    else // si on est en mode difficile
    {
        if (choixCaseEnVue == false)
        {
            i = 0;
            while (i < G.nbBateaux && (G.tabBateaux[i].state == BATEAU_NON_TOUCHE || G.tabBateaux[i].state == COULE))
            {
                i++;
            }
            if (i >= G.nbBateaux)
            {
                tirHasard(x, y, G, choixCaseEnVue);
            }
            else
            {
                coulerUnBateau(x, y, x_touche, y_touche, n, s, e, o, nord, sud, est, ouest, i, G, choixCaseEnVue);
                if (G.tabBateaux[i].state == COULE)
                {
                    modifenCEV_TOUCHE_INUTILE(G.tabBateaux[i], G);
                }
            }
        }
        else
        {
            i = 0;
            while (i < G.nbBateaux && (G.tabBateaux[i].state == BATEAU_NON_TOUCHE || G.tabBateaux[i].state == COULE))
            {
                i++;
            }
            if (i >= G.nbBateaux)
            {
                if (x == 15 && y == 15)
                {
                    tirHasard(x, y, G, choixCaseEnVue);
                }
                else
                {
                    if (G.tabGrille[x][y] == CEV_TOUCHE)
                    {
                        trouverUnBateau(x, y, n, s, e, o, nord, sud, est, ouest, G, bateauTrouve, choixCaseEnVue);
                        if (bateauTrouve)
                        {
                            x = 15;
                            y = 15;
                            bateauTrouve = false;
                        }
                    }
                    else
                    {
                        tirHasard(x, y, G, choixCaseEnVue);
                    }
                }
            }
            else
            {
                coulerUnBateau(x, y, x_touche, y_touche, n, s, e, o, nord, sud, est, ouest, i, G, choixCaseEnVue);
                if (G.tabBateaux[i].state == COULE)
                {
                    modifenCEV_TOUCHE_INUTILE(G.tabBateaux[i], G);
                    x = 15;
                    y = 15;
                }
            }
        }
    }
}

// fin 27.05

void initFenetre() // Works
{
    opengraphsize(WIDTH, HEIGHT);
    setbkcolor(WHITE);
    cleardevice();
}

void initBouton(Bouton &B, int x1, int y1, int x2, int y2, int couleur, int tx1, int ty1, int taille_texte, const char *texte) // Works
{
    B.x1 = x1;
    B.y1 = y1;
    B.x2 = x2;
    B.y2 = y2;
    B.couleur = couleur;
    B.tx1 = tx1;
    B.ty1 = ty1;
    B.texte_taille = taille_texte;
    B.texte = texte;
}

bool clicSurBouton(const Bouton &B, const int &x, const int &y) // ok
{
    return (B.x1 <= x && x <= B.x2) && (B.y1 <= y && y <= B.y2);
}

void choixOption(const Bouton &B1, const Bouton &B2, const Bouton &boutonSuivant, bool &choixOption) // ok
{
    int x, y;
    bool clicB1, clicB2, clicSuivant;
    do
    {
        if (clicB1)
        {
            dessinerContour(B1, WHITE);
        }
        else
        {
            if (clicB2)
                dessinerContour(B2, WHITE);
        }
        do
        {
            lireSouris(x, y);
            clicB1 = clicSurBouton(B1, x, y);
            clicB2 = clicSurBouton(B2, x, y);
        } while (clicB1 == false && clicB2 == false);
        if (clicB1)
        {
            dessinerContour(B1, BLACK);
        }
        else
        {
            if (clicB2)
                dessinerContour(B2, BLACK);
        }
        lireSouris(x, y);
        clicSuivant = clicSurBouton(boutonSuivant, x, y);
    } while ((clicB1 == clicB2) || (clicSuivant == false));
    if (clicB1)
    {
        choixOption = true;
    }
    else
    {
        choixOption = false;
    }
}

void choixOptionModeDeTir(const Bouton &B1, const Bouton &B2, const Bouton &boutonCaseEnVue, const Bouton &boutonSuivant, bool &choixTirSalves, bool &choixCaseEnVue) // ok
{
    int x, y;
    bool clicB1_1, clicB1_2, clicB2_1, clicB2_2, clicCEV_1, clicCEV_2, clicSuivant, clicB1, clicB2, hesitation;
    bool clicB1_F, clicB2_F;
    do
    {
        clicSuivant = false;
        cout << "debut des choix" << endl;
        dessinerContour(B1, WHITE);
        dessinerContour(B2, WHITE);
        dessinerCroix(boutonCaseEnVue, LIGHTBLUE);
        do
        {
            lireSouris(x, y);
            clicB1_1 = clicSurBouton(B1, x, y);
            clicB2_1 = clicSurBouton(B2, x, y);
            clicCEV_1 = clicSurBouton(boutonCaseEnVue, x, y);
        } while (clicB1_1 == false && clicB2_1 == false & clicCEV_1 == false);

        if (clicB1_1)
        {
            dessinerContour(B1, BLACK);
        }
        else
        {
            if (clicB2_1)
            {
                dessinerContour(B2, BLACK);
            }
            else
            {
                if (clicCEV_1)
                {
                    dessinerCroix(boutonCaseEnVue, BLACK);
                }
            }
        }
        do
        {
            hesitation = false;
            lireSouris(x, y);
            clicB1_2 = clicSurBouton(B1, x, y);
            clicB2_2 = clicSurBouton(B2, x, y);
            clicCEV_2 = clicSurBouton(boutonCaseEnVue, x, y);
            clicSuivant = clicSurBouton(boutonSuivant, x, y);
            if (clicB1_2 && clicB2_1 || clicB1_2 && clicCEV_1)
            {
                dessinerContour(B1, BLACK);
                dessinerContour(B2, WHITE);
                if (clicB1_2 && clicB2_1)
                {
                    hesitation = true;
                    clicB2_1 = false;
                }
            }
            else
            {
                if (clicB2_2 && clicB1_1 || clicB2_2 && clicCEV_1)
                {
                    dessinerContour(B2, BLACK);
                    dessinerContour(B1, WHITE);
                    if (clicB2_2 && clicB1_1)
                    {
                        clicB1_1 = false;
                        hesitation = true;
                    }
                }
                else
                {
                    if (clicCEV_2 && clicCEV_1)
                    {
                        dessinerCroix(boutonCaseEnVue, LIGHTBLUE);
                    }
                    else
                    {
                        if (clicCEV_2)
                        {
                            dessinerCroix(boutonCaseEnVue, BLACK);
                        }
                    }
                }
            }
        } while (clicB1_2 == false && clicB2_2 == false && clicCEV_2 == false && clicSuivant == false);

        clicB1 = clicB1_1 || clicB1_2;
        clicB2 = clicB2_1 || clicB2_2;
        if (hesitation == true)
        {
            clicSuivant = false;
        }
        else
        {
            if (clicSuivant == false)
            {
                do
                {
                    hesitation = false;
                    lireSouris(x, y);
                    clicSuivant = clicSurBouton(boutonSuivant, x, y);
                    clicB1_F = clicSurBouton(B1, x, y);
                    clicB2_F = clicSurBouton(B2, x, y);
                    if (clicB2 && clicB1_F)
                    {
                        hesitation = true;
                    }
                    else
                    {
                        if (clicB1 && clicB2_F)
                        {
                            hesitation = true;
                        }
                    }
                } while (clicSuivant == false && clicB1_F == false && clicB2_F == false);
            }
        }
    } while ((clicB1 == clicB2) || (clicSuivant == false));

    if (clicB1_1 || clicB1_2)
    {
        choixTirSalves = false;
    }
    else
    {
        choixTirSalves = true;
    }

    if (clicCEV_1 || clicCEV_2)
    {
        choixCaseEnVue = true;
    }
    else
    {
        choixCaseEnVue = false;
    }
}

void menu(bool &choixMultiJoueur, bool &choixDifficile, bool &choixTirSalves, bool &choixCaseEnVue, bool &choix6Bateaux) // ok
{
    setbkcolor(WHITE);
    cleardevice();
    int x1, y1, x2, y2;
    int longueurB = 250 / 2;
    int hauteurB = 50;
    int taille_texte = 2;

    Bouton boutonMultiJoueur, boutonSolo, boutonFacile, boutonDifficile, boutonTirSalves, boutonTirParCase, boutonCaseEnVue, bouton6Bateaux, bouton5Bateaux, boutonSuivant;

    bool clicMultiJoueur, clicSolo, clicSuivant;

    // Ecran 1 : mode solo ou multi
    setcolor(DARKGRAY);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 6);
    outtextxy(WIDTH / 2 - 258, 135, "Bataille navale");
    initBouton(boutonMultiJoueur, WIDTH / 2 - longueurB, 270, WIDTH / 2 + longueurB, 270 + hauteurB, BLUE, 553, 287, taille_texte, "Multijoueur");
    dessinerBouton(boutonMultiJoueur);
    initBouton(boutonSolo, WIDTH / 2 - longueurB, 400, WIDTH / 2 + longueurB, 400 + hauteurB, CYAN, 607, 417, taille_texte, "Solo");
    dessinerBouton(boutonSolo);
    initBouton(boutonSuivant, WIDTH / 2 - longueurB, 530, WIDTH / 2 + longueurB, 530 + hauteurB, GREEN, 582, 547, taille_texte, "Suivant");
    dessinerBouton(boutonSuivant);
    choixOption(boutonMultiJoueur, boutonSolo, boutonSuivant, choixMultiJoueur);

    // Ecran 1.1 : si mode solo
    if (choixMultiJoueur == false)
    {
        setbkcolor(WHITE);
        cleardevice();
        setcolor(DARKGRAY);
        settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
        outtextxy(WIDTH / 2 - 330, 135, "Niveau de l'ordinateur");
        initBouton(boutonFacile, WIDTH / 2 - longueurB, 270, WIDTH / 2 + longueurB, 270 + hauteurB, BLUE, 592, 287, taille_texte, "Facile");
        dessinerBouton(boutonFacile);
        initBouton(boutonDifficile, WIDTH / 2 - longueurB, 400, WIDTH / 2 + longueurB, 400 + hauteurB, CYAN, 568, 417, taille_texte, "Difficile");
        dessinerBouton(boutonDifficile);
        initBouton(boutonSuivant, WIDTH / 2 - longueurB, 530, WIDTH / 2 + longueurB, 530 + hauteurB, GREEN, 582, 547, taille_texte, "Suivant");
        dessinerBouton(boutonSuivant);
        choixOption(boutonFacile, boutonDifficile, boutonSuivant, choixDifficile);
        choixDifficile = !choixDifficile;
    }

    // Ecran 2 : choix du mode de tir
    setbkcolor(WHITE);
    cleardevice();
    setcolor(DARKGRAY);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
    outtextxy(WIDTH / 2 - 170, 110, "Mode de tir");
    initBouton(boutonTirParCase, WIDTH / 2 - longueurB, 220, WIDTH / 2 + longueurB, 220 + hauteurB, BLUE, 544, 237, taille_texte, "Tir par case");
    dessinerBouton(boutonTirParCase);
    initBouton(boutonTirSalves, WIDTH / 2 - longueurB, 340, WIDTH / 2 + longueurB, 340 + hauteurB, CYAN, 529, 357, taille_texte, "Tir par salves");
    dessinerBouton(boutonTirSalves);

    setcolor(DARKGRAY);
    setbkcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, taille_texte);
    outtextxy(WIDTH / 2 - 142, 450, "Case en vue ?");
    initBouton(boutonCaseEnVue, WIDTH / 2 - 127 + 220, 435, WIDTH / 2 - 127 + 220 + 50, 435 + 50, LIGHTBLUE, 0, 0, 1, "");
    dessinerBouton(boutonCaseEnVue);

    initBouton(boutonSuivant, WIDTH / 2 - longueurB, 530, WIDTH / 2 + longueurB, 530 + hauteurB, GREEN, 582, 547, taille_texte, "Suivant");
    dessinerBouton(boutonSuivant);
    choixOptionModeDeTir(boutonTirParCase, boutonTirSalves, boutonCaseEnVue, boutonSuivant, choixTirSalves, choixCaseEnVue);

    // Ecran 3 : Nombre de bateaux
    setbkcolor(WHITE);
    cleardevice();
    setcolor(DARKGRAY);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
    outtextxy(WIDTH / 2 - 296, 135, "Nombre de bateaux");
    initBouton(bouton5Bateaux, WIDTH / 2 - longueurB, 270, WIDTH / 2 + longueurB, 270 + hauteurB, BLUE, 566, 287, taille_texte, "5 bateaux");
    dessinerBouton(bouton5Bateaux);
    initBouton(bouton6Bateaux, WIDTH / 2 - longueurB, 400, WIDTH / 2 + longueurB, 400 + hauteurB, CYAN, 566, 417, taille_texte, "6 bateaux");
    dessinerBouton(bouton6Bateaux);
    initBouton(boutonSuivant, WIDTH / 2 - longueurB, 530, WIDTH / 2 + longueurB, 530 + hauteurB, GREEN, 582, 547, taille_texte, "Suivant");
    dessinerBouton(boutonSuivant);
    choixOption(bouton5Bateaux, bouton6Bateaux, boutonSuivant, choix6Bateaux);
    choix6Bateaux = !choix6Bateaux;
}

void initBateau(Bateau &B, int id, int size, string nom) // Works
{
    B.id = id;
    B.taille = size;
    B.directionTrouve = false;
    B.bateauToucheDeuxFois = false;
    B.state = BATEAU_NON_TOUCHE;
    B.nom = nom;
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

bool jeu_fini(const Joueur &J1, const Joueur &J2) // ok //joueur 1 qui a tir� sur la grille du J2
{
    bool jeuFini = true;
    int i = 0;
    while (i < J2.grille.nbBateaux && jeuFini)
    {
        if (J2.grille.tabBateaux[i].state != COULE)
        {
            jeuFini = false;
        }
        i++;
    }
    if (jeuFini)
    {
        cout << "Jeu fini" << endl;
    }
    else
    {
        cout << "Jeu pas fini" << endl;
    }
    return jeuFini;
}

bool victoire_J1(const Joueur &J1) // ok
{
    bool victoireJ1 = false;
    int i = 0;
    while (i < J1.grille.nbBateaux && (victoireJ1 == false))
    {
        if (J1.grille.tabBateaux[i].state != COULE)
        {
            victoireJ1 = true;
        }
        i++;
    }
    return victoireJ1;
}

void finPartie(bool victoireJ1, bool choixMultiJoueur_org) // TODO
{
    int longueurB = 250 / 2 + 20;
    int hauteurB = 80;
    if (choixMultiJoueur_org)
    {
        if (victoireJ1)
        {
            cleardevice();
            setcolor(DARKGRAY);
            settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
            outtextxy(WIDTH / 2 - 318, 200, "Le joueur 1 a gagn� !");
        }
        else
        {
            cleardevice();
            setcolor(DARKGRAY);
            settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
            outtextxy(WIDTH / 2 - 318, 200, "Le joueur 2 a gagn� !");
        }
    }
    else
    {
        if (victoireJ1)
        {
            cleardevice();
            setcolor(DARKGRAY);
            settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
            outtextxy(WIDTH / 2 - 280, 200, "Vous avez gagn� !");
        }
        else
        {
            cleardevice();
            setcolor(DARKGRAY);
            settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
            outtextxy(WIDTH / 2 - 250, 200, "Vous avez perdu");
        }
    }
    Bouton boutonRetourMenu;
    initBouton(boutonRetourMenu, WIDTH / 2 - longueurB - 5, 400, WIDTH / 2 + longueurB, 400 + hauteurB, BLUE, 525, 432, 2, "Retour au menu");
    dessinerBouton(boutonRetourMenu);
    int x, y;
    do
    {
        lireSouris(x, y);
    } while (!clicSurBouton(boutonRetourMenu, x, y));
}

void initJeu(Joueur &J1, Joueur &J2, bool choix6Bateaux)
{
    Grille G1;
    Bateau B1_1, B2_1, B3_1, B4_1, B5_1;
    initBateau(B1_1, 1, PORTE_AVION, "porte-avions");
    initBateau(B2_1, 2, CROISEUR, "croiseur");
    initBateau(B3_1, 3, CONTRE_TORPILLEUR, "contre-torpilleur");
    initBateau(B4_1, 4, CONTRE_TORPILLEUR, "contre-torpilleur");
    initBateau(B5_1, 5, TORPILLEUR, "torpilleur");
    TAB_BATEAUX TB1 = {B1_1, B2_1, B3_1, B4_1, B5_1};
    initGrille(G1, 155, 175, 5, TB1);
    initJoueur(J1, "Joueur 1", G1);

    Grille G2;
    Bateau B1_2, B2_2, B3_2, B4_2, B5_2;
    initBateau(B1_2, 1, PORTE_AVION, "porte-avions");
    initBateau(B2_2, 2, CROISEUR, "croiseur");
    initBateau(B3_2, 3, CONTRE_TORPILLEUR, "contre-torpilleur");
    initBateau(B4_2, 4, CONTRE_TORPILLEUR, "contre-torpilleur");
    initBateau(B5_2, 5, TORPILLEUR, "torpilleur");
    TAB_BATEAUX TB2 = {B1_2, B2_2, B3_2, B4_2, B5_2};
    initGrille(G2, 755, 175, 5, TB2);
    initJoueur(J2, "Joueur 2", G2);

    if (choix6Bateaux)
    {
        Bateau B6_1, B6_2;
        initBateau(B6_1, 6, TORPILLEUR, "torpilleur");
        initBateau(B6_2, 6, TORPILLEUR, "torpilleur");
        J1.grille.nbBateaux++;
        J2.grille.nbBateaux++;
        J1.grille.tabBateaux[5] = B6_1;
        J2.grille.tabBateaux[5] = B6_2;
    }
}

void jeu(Joueur &J1, Joueur &J2, bool choixMultiJoueur, bool choixDifficile, bool choixTirSalves, bool choixCaseEnVue, bool choix6Bateaux)
{
    initJeu(J1, J2, choix6Bateaux);
    int x, y, xOrdi, yOrdi;
    setbkcolor(LIGHTGRAY);
    cleardevice();
    bool jeuFini = false;
    if (choixMultiJoueur == true)
    {
        afficherCacheEcran(1);
        getch();
        afficherDeuxGrilles(J1, J2);
        placerBateauxJoueur(J1.grille.tabBateaux, J1.grille);
        afficherCacheEcran(2);
        getch();
        afficherDeuxGrilles(J2, J1);
        placerBateauxJoueur(J2.grille.tabBateaux, J2.grille);

        while (jeuFini == false)
        {
            afficherCacheEcran(1);
            getch();
            setbkcolor(LIGHTGRAY);
            cleardevice();
            afficherDeuxGrilles(J1, J2);
            if (choixTirSalves)
            {
                for (int i = 0; i < 4; i++)
                {
                    tirerJoueur(x, y, J2.grille, choixCaseEnVue);
                }
            }
            tirerJoueur(x, y, J2.grille, choixCaseEnVue);
            for (int i = 0; i < J2.grille.nbBateaux; i++)
            {
                cout << J2.grille.tabBateaux[i].state << endl;
            }
            getch();
            jeuFini = jeu_fini(J1, J2); // verification si le joueur 1 a coul� tous les bateaux du joueur 2
            if (jeuFini == false)
            {
                afficherCacheEcran(2);
                getch();
                afficherDeuxGrilles(J2, J1);
                if (choixTirSalves)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        tirerJoueur(x, y, J1.grille, choixCaseEnVue);
                    }
                }
                tirerJoueur(x, y, J1.grille, choixCaseEnVue);

                for (int i = 0; i < J1.grille.nbBateaux; i++)
                {
                    cout << J1.grille.tabBateaux[i].state << endl;
                }
                getch();
                jeuFini = jeu_fini(J2, J1);
            }
        }
        getch();
    }
    else
    {
        bool choixCaseEnVueOrdi = choixCaseEnVue;
        if (choixDifficile == false) // si on est en mode facile : l'ordinateur ne prend pas en compte les cases en vue m�me si le mode case en vue est activ�
        {
            choixCaseEnVueOrdi = false;
        }
        xOrdi = 15;
        yOrdi = 15;
        bool bateauTrouve = false;
        afficherDeuxGrilles(J1, J2);
        placerBateauxJoueur(J1.grille.tabBateaux, J1.grille);
        setbkcolor(LIGHTGRAY);
        cleardevice();

        placerBateauxAleat(J2.grille.tabBateaux, J2.grille);
        // placerBateauxJoueur(J2.grille.tabBateaux, J2.grille); // NORMALEMENT PLACEMENT BATEAUX PAR LORDINATEUR
        afficherDeuxGrilles(J2, J1); // normalement placement bateau aleat

        setbkcolor(LIGHTGRAY);
        cleardevice();

        afficherDeuxGrilles(J1, J2);
        while (jeuFini == false)
        {
            if (choixTirSalves)
            {
                for (int i = 0; i < 4; i++)
                {
                    tirerJoueur(x, y, J2.grille, choixCaseEnVue);
                }
            }
            tirerJoueur(x, y, J2.grille, choixCaseEnVue);
            for (int i = 0; i < J2.grille.nbBateaux; i++)
            {
                cout << J2.grille.tabBateaux[i].state << endl;
            }
            jeuFini = jeu_fini(J1, J2); // verification si le joueur 1 a coul� tous les bateaux du joueur 2
            if (jeuFini == false)
            {
                if (choixTirSalves)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        tirerOrdi(xOrdi, yOrdi, J1.grille, choixDifficile, choixCaseEnVueOrdi, bateauTrouve);
                    }
                }
                tirerOrdi(xOrdi, yOrdi, J1.grille, choixDifficile, choixCaseEnVueOrdi, bateauTrouve);
                for (int i = 0; i < J1.grille.nbBateaux; i++)
                {
                    cout << J1.grille.tabBateaux[i].state << endl;
                }
                jeuFini = jeu_fini(J2, J1);
            }
        }
        getch();
    }
}

int main()
{
    // debugLevel = 2;
    // initFenetre();
    // verbose("Test", DEBUG);
    // Couleur de fond
    // setbkcolor(LIGHTGRAY);
    // cleardevice();

    // bool choixMultiJoueur, choixDifficile, choixTirSalves, choixCaseEnVue, choix6Bateaux;
    // menu(choixMultiJoueur, choixDifficile, choixTirSalves, choixCaseEnVue, choix6Bateaux);

    // Test dessinerGrille
    // dessinerGrille(G1);
    // dessinerGrille(G2);

    // Test placerBateau
    // placerBateauxAleat(G1.tabBateaux, G1);
    // placerBateauxAleat(G2.tabBateaux, G2);

    // // Test dessinerCase
    // G1.tabGrille = {{{COULE, CEV_INTACTE, CEV_TOUCHE, TOUCHE, RATE, VIDE, VIDE, VIDE, VIDE, VIDE},
    //                  {VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE},
    //                  {VIDE, 1, VIDE, VIDE, VIDE, VIDE, 3, 3, 3, 3},
    //                  {VIDE, 1, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE},
    //                  {VIDE, 1, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE},
    //                  {VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE},
    //                  {VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE},
    //                  {VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE},
    //                  {VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE},
    //                  {VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE}}};

    // for (int i = 0; i < CASES; i++)
    // {
    //     for (int j = 0; j < CASES; j++)
    //     {
    //         dessinerCase(i, j, G1);
    //     }
    // }

    // Tieu
    // Test tirer
    // int x, y;
    // for (int i = 0; i < 10; i++)
    // {
    //     tirerJoueur(x, y, G1, false);
    // }

    // Test tirerOrdi simple
    // for (int i = 0; i < 100; i++)
    // {
    //     tirerOrdi(G2, false, false);
    //     outtextxy(0, 0, "" + i);
    //     getch();
    // }

    // Fin tieu

    /*initTabGrille(TG);
    initGrille(G, 0, 0, TG, 1,TB);
    Joueur J;
    initJoueur(J, "Joueur 1", G);
    dessinerGrille(J.grille);
    dessinerBateau(J.grille.tabBateaux[0], J.grille);*/

    // debut 18.05 tieu *****************************************************************************************************************************************

    // TEST menu ______________________________________________________________________________________________________________________________________
    // bool choixMultiJoueur, choixDifficile, choixTirSalves, choixCaseEnVue, choix6Bateaux;
    // menu(choixMultiJoueur, choixDifficile, choixTirSalves, choixCaseEnVue, choix6Bateaux);
    // if (choixMultiJoueur)
    // {
    //     cout << "Mode multijoueur choisi" << endl;
    // }
    // else
    // {
    //     if (choixDifficile)
    //     {
    //         cout << "Mode solo : difficile" << endl;
    //     }
    //     else
    //     {
    //         cout << "Mode solo : facile" << endl;
    //     }
    // }
    // if (choixTirSalves)
    // {
    //     cout << "Tir par salves" << endl;
    // }
    // else
    // {
    //     cout << "Tir par case" << endl;
    // }
    // if (choixCaseEnVue)
    // {
    //     cout << "Avec cases en vue" << endl;
    // }
    // else
    // {
    //     cout << "Sans cases en vue" << endl;
    // }
    // if (choix6Bateaux)
    // {
    //     cout << "6 bateaux" << endl;
    // }
    // else
    // {
    //     cout << "5 bateaux" << endl;
    // }

    // TEST dessinerContour ______________________________________________________________________________________________________________________________________
    /*
    setbkcolor(WHITE);
    cleardevice();
    Bouton boutonMultiJoueur;
    int longueurB = 250 / 2;
    int hauteurB = 50;
    int taille_texte = 2;
    initBouton(boutonMultiJoueur, WIDTH / 2 - longueurB, 270, WIDTH / 2 + longueurB, 270 + hauteurB, BLUE, 553, 287, taille_texte, "Multijoueur");
    dessinerBouton(boutonMultiJoueur);
    dessinerContour(boutonMultiJoueur, BLACK);
    getch();
    dessinerContour(boutonMultiJoueur, WHITE);*/

    // TEST clicSurBouton ______________________________________________________________________________________________________________________________________
    /*Bouton boutonMultiJoueur;
    int x, y;
    int longueurB = 250 / 2;
    int hauteurB = 50;
    int taille_texte = 2;
    initBouton(boutonMultiJoueur, WIDTH / 2 - longueurB, 270, WIDTH / 2 + longueurB, 270 + hauteurB, BLUE, 553, 287, taille_texte, "Multijoueur");
    dessinerBouton(boutonMultiJoueur);
    for(int i=0; i<10; i++)
    {
        lireSouris(x,y);
        if(clicSurBouton(boutonMultiJoueur, x, y))
        {
            cout<<"clic sur bouton"<<endl;
        }
        else
        {
            cout<<"pas de clic sur bouton"<<endl;
        }
    }*/

    // TEST dessinerCroix sur le bouton carr� Case en vue ______________________________________________________________________________________________________________________________________
    /*Bouton boutonCaseEnVue;
    setcolor(DARKGRAY);
    setbkcolor(WHITE);
    int longueurB = 250 / 2;
    int hauteurB = 50;
    int taille_texte = 2;
    settextstyle(DEFAULT_FONT, HORIZ_DIR, taille_texte);
    outtextxy(WIDTH/2 - 142, 450, "Case en vue ?");
    initBouton(boutonCaseEnVue, WIDTH/2 - 127 + 220, 435, WIDTH/2  - 127 + 220 + 50, 435+50, LIGHTBLUE, 0, 0, 1, "");
    dessinerBouton(boutonCaseEnVue);
    dessinerCroix(boutonCaseEnVue, BLACK);
    getch();
    dessinerCroix(boutonCaseEnVue, LIGHTBLUE);*/

    // TEST afficherDeuxGrilles (selon le point de vue) et afficherCacheEcran ______________________________________________________________________________________________________________________________________
    /*Joueur J1, J2;
    int x, y;
    J1.grille=G2;
    J2.grille=G1;
    bool choixTirSalves = true;
    placerBateauxAleat(J1.grille.tabBateaux, J1.grille);
    placerBateauxAleat(J2.grille.tabBateaux, J2.grille);

    afficherDeuxGrilles(J1, J2);

    getch();
    setbkcolor(LIGHTGRAY);
    cleardevice();

    setbkcolor(LIGHTGRAY);
    afficherCacheEcran(1);
    getch();
    cleardevice();
    afficherDeuxGrilles(J1, J2);

    tirerJoueur(x,y,J2.grille, false, choixTirSalves); //option case en vue pas activ� pour le joueur J1

    getch();
    setbkcolor(LIGHTGRAY);
    cleardevice();

    afficherCacheEcran(2);
    getch();
    setbkcolor(LIGHTGRAY);
    cleardevice();
    afficherDeuxGrilles(J2, J1);

    tirerJoueur(x,y,J1.grille, true, choixTirSalves);

    getch();
    setbkcolor(LIGHTGRAY);
    cleardevice();
    afficherCacheEcran(1);
    getch();
    setbkcolor(LIGHTGRAY);
    cleardevice();
    afficherDeuxGrilles(J1, J2);*/

    // TEST jeu_fini ______________________________________________________________________________________________________________________________________
    /*Joueur J1, J2;
    int x, y;
    bool jeuFini;
    J1.grille=G2;
    J2.grille=G1;
    bool choixTirSalves = true, choixCaseEnVue=true;
    placerBateauxAleat(J1.grille.tabBateaux, J1.grille);
    placerBateauxAleat(J2.grille.tabBateaux, J2.grille);
    afficherDeuxGrilles(J1, J2);
    setbkcolor(LIGHTGRAY);
    cleardevice();

    for(int i=0; i<J1.grille.nbBateaux; i++)
    {
        J1.grille.tabBateaux[i].state=10;
        J2.grille.tabBateaux[i].state=10;
    }

    jeuFini==false;
    while(jeuFini==false)
    {
        afficherCacheEcran(1);
        getch();
        setbkcolor(LIGHTGRAY);
        cleardevice();
        afficherDeuxGrilles(J1, J2);
        tirerJoueur(x, y, J2.grille, choixCaseEnVue, choixTirSalves);
        for(int i=0; i<J2.grille.nbBateaux; i++)
        {
            cout<<J2.grille.tabBateaux[i].state<<endl;
        }
        getch();
        jeuFini=jeu_fini(J1, J2); //verification si le joueur 1 a coul� tous les bateaux du joueur 2

        if(jeuFini==false)
        {
            afficherCacheEcran(2);
            getch();
            afficherDeuxGrilles(J2, J1);
            tirerJoueur(x, y, J1.grille, choixCaseEnVue, choixTirSalves);
            for(int i=0; i<J1.grille.nbBateaux; i++)
            {
                cout<<J1.grille.tabBateaux[i].state<<endl;
            }
            getch();
            jeuFini=jeu_fini(J2, J1);
        }
    }*/

    // TEST victoireJ1 ______________________________________________________________________________________________________________________________________
    /*Joueur J1, J2;
    int x, y;
    bool victoireJ1;
    J1.grille=G2;
    J2.grille=G1;
    for(int i=0; i<J1.grille.nbBateaux; i++)
    {
        J1.grille.tabBateaux[i].state=COULE;
        J2.grille.tabBateaux[i].state=COULE;
    }
    J1.grille.tabBateaux[0].state=TOUCHE;
    victoireJ1 = victoire_J1(J1);
    if(victoireJ1)
    {
        cout<<"Joueur 1 a gagne"<<endl;
    }
    else
    {
        cout<<"Joueur 1 a perdu"<<endl;
    }*/

    // fin 19.05 tieu *****************************************************************************************************************************************

    // debut 25.05*********************************************************************************************************************************************

    // Test initJeu ________________________________________________________________________
    // Joueur Player1, Player2;
    // bool choix6Bateaux = false;
    // initJeu(Player1, Player2, choix6Bateaux);
    // afficherDeuxGrilles(Player1, Player2);
    // placerBateauxJoueur(Player1.grille.tabBateaux, Player1.grille);

    // Test proc�dure jeu (contenant initJeu et la boucle de jeu) __________________________
    // Joueur P1, P2;
    // bool choixMultijoueur = true;
    // bool choixDifficile = false;
    // bool choixTirSalves = true; // ok
    // bool choixCaseEnVue = true; // ok
    // bool choix6Bateaux = false; // ok
    // jeu(P1, P2, choixMultijoueur, choixDifficile, choixTirSalves, choixCaseEnVue, choix6Bateaux);

    // fin 25.05***********************************************************************************************************************************************

    // Test au 27.05********************************************************************************************************************************************

    // Test finPartie ____________________________________________________________________________
    /*initFenetre();
    bool victoireJ1=true;
    bool choixMultijoueur=true;
    Joueur J1, J2;
    initJeu(J1, J2, false);
    finPartie(victoireJ1, choixMultijoueur);
    */

    // Test PlacerBateauAleat______________________________________________________________________
    /*initFenetre();
    Joueur J1, J2;
    bool choix6Bateaux=false;
    initJeu(J1, J2, choix6Bateaux);
    afficherDeuxGrilles(J1,J2);
    placerBateauxAleat(J1.grille.tabBateaux, J1.grille);
    getch();*/

    // Le jeu

    initFenetre();
    while (true)
    {
        cleardevice();
        Joueur P1, P2;
        bool choixMultiJoueur, choixDifficile, choixTirSalves, choixCaseEnVue, choix6Bateaux;
        menu(choixMultiJoueur, choixDifficile, choixTirSalves, choixCaseEnVue, choix6Bateaux);
        setbkcolor(LIGHTGRAY);
        jeu(P1, P2, choixMultiJoueur, choixDifficile, choixTirSalves, choixCaseEnVue, choix6Bateaux);
        finPartie(victoire_J1(P1), choixMultiJoueur);
    }

    return 0;
}
