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
    setcolor(LIGHTGRAY);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, B.texte_taille);
    outtextxy(B.tx1, B.ty1, B.texte);
    verbose("Bouton dessine" + to_string(B.x1) + " " + to_string(B.y1) + " " + to_string(B.x2) + " " + to_string(B.y2) + " " + to_string(B.couleur) + " " + B.texte, DEBUG);
}

void dessinerContour(const Bouton &B, int Couleur) // Works
{
    setbkcolor(Couleur);
    setlinestyle(SOLID_LINE, 0, 10);
    rectangle(B.x1 - 5, B.y1 - 5, B.x2 + 5, B.y2 + 5);
    verbose("Contour dessine" + to_string(B.x1) + " " + to_string(B.y1) + " " + to_string(B.x2) + " " + to_string(B.y2) + " " + to_string(B.couleur), DEBUG);
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
            if (G.tabGrille[B.x + i][B.y] != VIDE)
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
            if (G.tabGrille[B.x][B.y + i] != VIDE)
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
    for (int i = 0; i < CASES; i++)
    {
        for (int j = 0; j < CASES; j++)
        {
            dessinerCase(i, j, G);
        }
    }
}

void placerBateauxJoueur(TAB_BATEAUX &T, Grille &G) // To test
{
    for (int i = 0; i < G.nbBateaux; i++)
    {
        bool placee = false;
        do
        {
            Point p1, p2;
            lireSouris(p1.x, p1.y);
            lireSouris(p2.x, p2.y);
            T[i].x = (int)(min(p1.x, p2.x) - G.x) / G.cellWidth;
            T[i].y = (int)(min(p1.y, p2.y) - G.y) / G.cellHeight;
            T[i].orientation = (abs(p1.x - p2.x) < abs(p1.y - p2.y)) ? VERT_DIR : HORIZ_DIR;
            placee = placerBateau(T[i], G);
            if (!placee)
            {
                setcolor(RED);
                setbkcolor(WHITE);
                string str = "Bateau " + to_string(i) + " : " + to_string(T[i].x) + " " + to_string(T[i].y) + " " + to_string(T[i].orientation);
                const char *c = str.c_str();
                outtextxy(0, 0, c);
            }
            else
            {
                setcolor(GREEN);
                setbkcolor(WHITE);
                string str = "Bateau " + to_string(i) + " : " + to_string(T[i].x) + " " + to_string(T[i].y) + " " + to_string(T[i].orientation);
                const char *c = str.c_str();
                outtextxy(0, 0, c);
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
        setcolor(GREEN);
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

void dessinerBateauCoule(const Bateau &B, const Grille &G) // dessine un bateau
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

int tirer(const int &x, const int &y, Grille &G) // To test
{
    int id = G.tabGrille[x][y];
    cout << G.tabGrille[x][y];
    if (id > 0)
    {
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
        }
        else
        {
            dessinerCase(x, y, G);
        }
    }
    else if (id == VIDE)
    {
        G.tabGrille[x][y] = RATE;
        dessinerCase(x, y, G);
    }
    else if (id == CEV_INTACTE)
    {
        G.tabGrille[x][y] = CEV_TOUCHE;
        dessinerCase(x, y, G);
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
    } while (x < 0 || x >= CASES || y < 0 || y >= CASES || tirer(x, y, G) < CEV_INTACTE);
}

void tirerOrdi(bool modeDifficile, Grille &G) // TODO
{
    static int x = 0;
    static int y = 0;
    static bool bateauxDecouverts = false;

    if (!bateauxDecouverts)
    {
        do
        {
            x += 2;
            if (x >= CASES)
            {
                x = (y + 1) % 2;
                y++;
            }
            if (y >= CASES)
            {
                y = 0;
            }
        } while (tirer(x, y, G) < CEV_TOUCHE);

        int i = 0;
        while (i < G.nbBateaux && G.tabBateaux[i].state < VIDE)
        {
            i++;
        }
        bateauxDecouverts = i == (G.nbBateaux - 1);
    }
    else
    {
        if (modeDifficile)
        {
            // TODO
        }
        else
        {
            do
            {
                x = rand() % CASES;
                y = rand() % CASES;
            } while (tirer(x, y, G) < CEV_TOUCHE);
        }
    }
}

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

void menu(bool &choixMultiJoueur, bool &choixDifficile, bool &choixTirSalves, bool &choixCaseEnVue, bool &choix6Bateaux) // TODO
{
    setbkcolor(WHITE);
    cleardevice();
    int x, y;
    int longueurB = 200 / 2;
    int hauteurB = 60;
    int taille_texte = 2;
    Bouton boutonMultiJoueur, boutonSolo, boutonFacile, boutonDifficile, boutonTirSalves, boutonTirParCase, boutonCaseEnVue, bouton6Bateaux, bouton5Bateaux, boutonSuivant;
    initBouton(boutonMultiJoueur, WIDTH / 2 - longueurB, 270, WIDTH / 2 + longueurB, 270 + hauteurB, BLUE, 552, 283, taille_texte, "Multijoueur");
    dessinerBouton(boutonMultiJoueur);
    dessinerContour(boutonMultiJoueur, BLACK);
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

bool jeu_fini(Joueur &J1, Joueur &J2) // TODO
{
}

void jeu(Joueur &J1, Joueur &J2, bool choixMultiJoueur, bool choixDifficile, bool choixTirSalves, bool choixCaseEnVue, bool choix6Bateaux) // TODO
{
    setbkcolor(LIGHTGRAY);
    cleardevice();
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

    // bool choixMultiJoueur, choixDifficile, choixTirSalves, choixCaseEnVue, choix6Bateaux;
    // menu(choixMultiJoueur, choixDifficile, choixTirSalves, choixCaseEnVue, choix6Bateaux);

    // Test dessinerGrille
    dessinerGrille(G1);
    dessinerGrille(G2);

    // Test placerBateau
    placerBateauxJoueur(G1.tabBateaux, G1);
    placerBateauxAleat(G2.tabBateaux, G2);

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
    int x, y;
    for (int i = 0; i < 10; i++)
    {
        tirerJoueur(x, y, G1);
    }

    // Test tirerOrdi simple
    for (int i = 0; i < 70; i++)
    {
        tirerOrdi(false, G2);
    }

    // Fin tieu

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
