#include <iostream>
#include <array>
#include <string>
#include <iomanip> //ajouté
#include "graphics.h"
#include "Bataille_Navale.h"

using namespace std;

void dessinerBouton(const Bouton& B)
{
    setfillstyle(SOLID_FILL, B.couleur);
    bar(B.x1, B.y1, B.x2, B.y2);
    setcolor(BLACK);
    outtextxy(B.x1 + 10, B.y1 + 10, B.texte);
}

void dessinerGrille(const Grille& G)
{
    setcolor(BLACK);
    rectangle(G.x, G.y, G.x + G.width, G.y + G.height);
    for (int i = 0; i < 10; i++)
    {
        setcolor(BLACK);
        setlinestyle(SOLID_LINE, 0, 1);
        line(G.x, G.y + i * G.cellHeight, G.x + G.width, G.y + i * G.cellHeight);
        line(G.x + i * G.cellWidth, G.y, G.x + i * G.cellWidth, G.y + G.height);
    }
}

void dessinerBateaux(const Bateaux& B) //dessine tous les bateaux
{
    for (int i = 0; i < B.n; i++)
    {
        setcolor(LIGHTBLUE);
        if (B.tab[i].orientation == 0)
        {
            bar(B.tab[i].x, B.tab[i].y, B.tab[i].x + B.tab[i].size * 40, B.tab[i].y + 40);
        }
        else
        {
            bar(B.tab[i].x, B.tab[i].y, B.tab[i].x + 40, B.tab[i].y + B.tab[i].size * 40);
        }
    }
}

void lireSouris(int& x, int& y)
{
    buttonhit();
    getmouse(x, y);
}

void menu()
{
}

//Ajouté----------------------------------------------------------------------------------------------------------------------------------

////Initialisation & procedure d'affichage
void init_bateaux(const int& nb_bateau, Bateaux& B) // initialisation des donnees bateaux selon choix nombre de bateaux
{
    B.n = nb_bateau;
    if (B.n == 5)
    {
        B.tab[0].id = "Porte-avions";
        B.tab[0].size = 5;
        B.tab[0].state = 1;
        B.tab[1].id = "Croiseur";
        B.tab[1].size = 4;
        B.tab[1].state = 1;
        B.tab[2].id = "Contre-torpilleurs";
        B.tab[2].size = 3;
        B.tab[2].state = 1;
        B.tab[3].id = "Contre-torpilleurs";
        B.tab[3].size = 3;
        B.tab[3].state = 1;
        B.tab[4].id = "Torpilleurs";
        B.tab[4].size = 2;
        B.tab[4].state = 1;
    }
    else
    {
        B.tab[0].id = "Porte-avions";
        B.tab[0].size = 5;
        B.tab[0].state = 1;
        B.tab[1].id = "Croiseur";
        B.tab[1].size = 4;
        B.tab[1].state = 1;
        B.tab[2].id = "Contre-torpilleurs";
        B.tab[2].size = 3;
        B.tab[2].state = 1;
        B.tab[3].id = "Contre-torpilleurs";
        B.tab[3].size = 3;
        B.tab[3].state = 1;
        B.tab[4].id = "Torpilleurs";
        B.tab[4].size = 2;
        B.tab[4].state = 1;
        B.tab[5].id = "Torpilleurs";
        B.tab[5].size = 2;
        B.tab[5].state = 1;
    }
}

void init_matrice(Joueur& J) //initialise la matrice du joueur à 0 (= case vide)
{
    for (int i = 0; i < 10; i++)
    {
        for (int k = 0; k < 10; k++)
        {
            J.grille.tab[i][k] = 0;
        }
    }
}

void afficher_matrice(const Joueur& J) //utile pour les tests
{
    for (int i = 0; i < 10; i++)
    {
        for (int k = 0; k < 10; k++)
        {
            cout << J.grille.tab[i][k] << " ";
        }
        cout << endl;
    }
}


////Fonctions/procedures utilisées pour le placement des bateaux

void affecter_clic_cases(const Joueur& J, int& x_s, int& y_s, int& x_b, int& y_b) //affecte les coordonnees des clics du joueur à de nouvelles coordonnees adaptées pour la suite
//x_s et y_s coordonnees du bateau, x_b et y_b coordonnees du 2e clic
{
    x_s = ((x_s - J.grille.x) / J.grille.cellHeight) * J.grille.cellHeight + J.grille.x;
    y_s = ((y_s - J.grille.y) / J.grille.cellHeight) * J.grille.cellHeight + J.grille.y;
    x_b = ((x_b - J.grille.x) / J.grille.cellHeight) * J.grille.cellHeight + J.grille.x;
    y_b = ((y_b - J.grille.y) / J.grille.cellHeight) * J.grille.cellHeight + J.grille.y;
}

bool hors_grille_bateau_vertical(const Joueur& J, const int& i) //renvoie true si le bateau est en dehors de la grille
{
    return ((J.B.tab[i].x + J.grille.cellHeight >= J.grille.x + J.grille.width + 1) || J.B.tab[i].x <= J.grille.x - 1 || J.B.tab[i].y <= J.grille.y - 1 || (J.B.tab[i].y + J.B.tab[i].size * J.grille.cellHeight) >= (J.grille.y + J.grille.height + 1));
}

bool hors_grille_bateau_horizontal(const Joueur& J, const int& i) //renvoie true si le bateau est en dehors de la grille
{
    return ((J.B.tab[i].x + J.B.tab[i].size * J.grille.cellHeight >= J.grille.x + J.grille.width + 1) || J.B.tab[i].x <= J.grille.x - 1 || J.B.tab[i].y <= J.grille.y - 1 || (J.B.tab[i].y + J.grille.cellHeight >= J.grille.y + J.grille.height + 1));
}

bool est_aligne(int& x_s, int& y_s, int& x_b, int& y_b) //renvoie true si les 2 points sont alignes verticalement ou horizontalement
{
    bool aligne = false;
    if ((x_s == x_b) && (y_s != y_b))
    {
        aligne = true;
    }
    else
    {
        if ((x_s != x_b) && (y_s == y_b))
        {
            aligne = true;
        }
    }
    return aligne;
}

void affect_orientation(Bateau& b, int& x_bout, int& y_bout) //affecte l'orientation au bateau selon les clics (horizontal ou vertical)
{
    if (b.x == x_bout)
    {
        b.orientation = 1;
    }
    else
    {
        if (b.y == y_bout)
        {
            b.orientation = 0;
        }
        else
        {
            b.orientation = -1;
        }
    }

}

void dessinerUnBateau(const Bateau& B) //dessine un bateau
{
    setcolor(LIGHTBLUE);
    if (B.orientation == 0)
    {
        bar(B.x, B.y, B.x + B.size * 40, B.y + 40);
    }
    else
    {
        bar(B.x, B.y, B.x + 40, B.y + B.size * 40);
    }
}

void modif_case_en_vue(Joueur& J, const int& i) //modifie les cases en cases en vue
{
    int l, c;
    if (J.B.tab[i].orientation == 0)
    {
        c = J.B.tab[i].x / J.grille.cellHeight - 1;
        l = J.B.tab[i].y / J.grille.cellHeight - 1;
        if (0 < l && l < 9)
        {
            for (int k = 1; k <= J.B.tab[i].size; k++)
            {
                J.grille.tab[l - 1][c] = 4;
                J.grille.tab[l + 1][c] = 4;
                c++;
            }
            c = J.B.tab[i].x / J.grille.cellHeight - 1;
            /*J.grille.tab[l][c-1]=4;
            J.grille.tab[l][c+J.B.tab[i].size]=4;*/
            if (c == 0)
            {
                J.grille.tab[l][c + J.B.tab[i].size] = 4;
            }
            else
            {
                if (c + J.B.tab[i].size == 10)
                {
                    J.grille.tab[l][c - 1] = 4;
                }
                else
                {
                    J.grille.tab[l][c - 1] = 4;
                    J.grille.tab[l][c + J.B.tab[i].size] = 4;
                }
            }
        }
        else
        {
            if (l == 0)
            {
                for (int k = 1; k <= J.B.tab[i].size; k++)
                {
                    J.grille.tab[l + 1][c] = 4;
                    c++;
                }
                c = J.B.tab[i].x / J.grille.cellHeight - 1;
                if (c == 0)
                {
                    J.grille.tab[l][c + J.B.tab[i].size] = 4;
                }
                else
                {
                    if (c + J.B.tab[i].size == 10)
                    {
                        J.grille.tab[l][c - 1] = 4;
                    }
                    else
                    {
                        J.grille.tab[l][c - 1] = 4;
                        J.grille.tab[l][c + J.B.tab[i].size] = 4;
                    }
                }
            }
            else
            {
                for (int k = 1; k <= J.B.tab[i].size; k++)
                {
                    J.grille.tab[l - 1][c] = 4;
                    c++;
                }
                c = J.B.tab[i].x / J.grille.cellHeight - 1;
                if (c == 0)
                {
                    J.grille.tab[l][c + J.B.tab[i].size] = 4;
                }
                else
                {
                    if (c + J.B.tab[i].size == 10)
                    {
                        J.grille.tab[l][c - 1] = 4;
                    }
                    else
                    {
                        J.grille.tab[l][c - 1] = 4;
                        J.grille.tab[l][c + J.B.tab[i].size] = 4;
                    }
                }
            }
        }
    }
    else
    {
        c = J.B.tab[i].x / J.grille.cellHeight - 1;
        l = J.B.tab[i].y / J.grille.cellHeight - 1;
        if (0 < c && c < 9)
        {
            for (int k = 1; k <= J.B.tab[i].size; k++)
            {
                J.grille.tab[l][c - 1] = 4;
                J.grille.tab[l][c + 1] = 4;
                l++;
            }
            l = J.B.tab[i].y / J.grille.cellHeight - 1;
            if (l == 0)
            {
                J.grille.tab[l + J.B.tab[i].size][c] = 4;
            }
            else
            {
                if (l + J.B.tab[i].size == 10)
                {
                    J.grille.tab[l - 1][c] = 4;
                }
                else
                {
                    J.grille.tab[l - 1][c] = 4;
                    J.grille.tab[l + J.B.tab[i].size][c] = 4;
                }
            }
        }
        else
        {
            if (c == 0)
            {
                for (int k = 1; k <= J.B.tab[i].size; k++)
                {
                    J.grille.tab[l][c + 1] = 4;
                    l++;
                }
                l = J.B.tab[i].y / J.grille.cellHeight - 1;
                if (l == 0)
                {
                    J.grille.tab[l + J.B.tab[i].size][c] = 4;
                }
                else
                {
                    if (l + J.B.tab[i].size == 10)
                    {
                        J.grille.tab[l - 1][c] = 4;
                    }
                    else
                    {
                        J.grille.tab[l - 1][c] = 4;
                        J.grille.tab[l + J.B.tab[i].size][c] = 4;
                    }
                }
            }
            else
            {
                for (int k = 1; k <= J.B.tab[i].size; k++)
                {
                    J.grille.tab[l][c - 1] = 4;
                    l++;
                }
                l = J.B.tab[i].y / J.grille.cellHeight - 1;
                if (l == 0)
                {
                    J.grille.tab[l + J.B.tab[i].size][c] = 4;
                }
                else
                {
                    if (l + J.B.tab[i].size == 10)
                    {
                        J.grille.tab[l - 1][c] = 4;
                    }
                    else
                    {
                        J.grille.tab[l - 1][c] = 4;
                        J.grille.tab[l + J.B.tab[i].size][c] = 4;
                    }
                }
            }
        }
    }
}

void modif_grille_apres_placement_un_bateau(Joueur& J, const int& i) //modifie les cases vides en cases bateau
{
    int l, c;
    // modif des états des cases avec bateau
    if (J.B.tab[i].orientation == 0)
    {
        c = J.B.tab[i].x / J.grille.cellHeight - 1;
        l = J.B.tab[i].y / J.grille.cellHeight - 1;
        for (int k = 1; k <= J.B.tab[i].size; k++)
        {
            J.grille.tab[l][c] = 1; // modif des états des cases avec bateau
            c++;
        }
    }
    else
    {
        if (J.B.tab[i].orientation == 1)
        {
            c = J.B.tab[i].x / J.grille.cellHeight - 1;
            l = J.B.tab[i].y / J.grille.cellHeight - 1;
            for (int j = 1; j <= J.B.tab[i].size; j++)
            {
                J.grille.tab[l][c] = 1; // modif des états des cases avec bateau
                l++;
            }
        }
    }
}

bool bateaux_adjacents(Joueur& J, const int& i) //renvoie true si les bateaux se touchent par un côté
{
    bool probleme = false;
    int l, c, n = 1;
    if (J.B.tab[i].orientation == 0)
    {
        c = J.B.tab[i].x / J.grille.cellHeight - 1;
        l = J.B.tab[i].y / J.grille.cellHeight - 1;
        while (n <= J.B.tab[i].size && probleme == false)
        {
            if (J.grille.tab[l][c] == 1 || J.grille.tab[l][c] == 4)
            {
                probleme = true;
            }
            else
            {
                c++;
                n++;
            }
        }
    }
    else
    {
        if (J.B.tab[i].orientation == 1)
        {
            c = J.B.tab[i].x / J.grille.cellHeight - 1;
            l = J.B.tab[i].y / J.grille.cellHeight - 1;
            while (n <= J.B.tab[i].size && probleme == false)
            {
                if (J.grille.tab[l][c] == 1 || J.grille.tab[l][c] == 4)
                {
                    probleme = true;
                }
                else
                {
                    l++;
                    n++;
                }
            }
        }
    }
    return probleme;
}

void PlacerBateauJoueur(const int& nb_bateau, Joueur& J) //cas considere: on place les bateaux de gauche à droite et de haut en bas, à reflechir: pouvoir mettre les bateaux de haut en bas et de droite à gauche
{
    bool placement_valide;
    point bout;  //point correspondant au 2e clic lors du placement d'un bateau
    for (int i = 0; i < nb_bateau; i++)
    {
        placement_valide = false;
        do {
            lireSouris(J.B.tab[i].x, J.B.tab[i].y); //coordonnees du 1er clic
            lireSouris(bout.x, bout.y);            //coordonnees du 2e clic
            affecter_clic_cases(J, J.B.tab[i].x, J.B.tab[i].y, bout.x, bout.y); //affecte de nouvelles valeurs aux clics
            affect_orientation(J.B.tab[i], bout.x, bout.y); //affecte l'orientation au bateau
            if (est_aligne(J.B.tab[i].x, J.B.tab[i].y, bout.x, bout.y)) //si le bateau est bien aligne horizontalement ou verticalement
            {
                if (J.B.tab[i].orientation == 0 && hors_grille_bateau_horizontal(J, i) == false && bateaux_adjacents(J, i) == false) //verifie si le bateau est dans la grille
                {
                    placement_valide = true;
                }
                else
                {
                    if (J.B.tab[i].orientation == 1 && hors_grille_bateau_vertical(J, i) == false && bateaux_adjacents(J, i) == false) //verifie si le bateau est dans la grille
                    {
                        placement_valide = true;
                    }
                }
            }
            if (bateaux_adjacents(J, i))
            {
                placement_valide = false;
            }
            else //on modifie les cases de la grille du joueur si le placement du bateau n'est pas invalide
            {
                modif_case_en_vue(J, i);
                modif_grille_apres_placement_un_bateau(J, i);
            }
        } while (placement_valide == false);
        dessinerUnBateau(J.B.tab[i]);
    }
}

////Placement bateau par un ordinateur

int aleat(int a, int b)
{
    return a + (b - a + 1) * (rand() / ((double)RAND_MAX + 1));
}

void PlacerBateauOrdi(const int& nb_bateau, Joueur& J) //cas considere: on place les bateaux de gauche à droite et de haut en bas, à reflechir: pouvoir mettre les bateaux de haut en bas et de droite à gauche
{
    int un_ou_deux;
    bool placement_valide;
    point bout;  //point correspondant au 2e clic lors du placement d'un bateau
    for (int i = 0; i < nb_bateau; i++)
    {
        placement_valide = false;
        do {
            J.B.tab[i].x = aleat(J.grille.x, J.grille.x + J.grille.width);
            J.B.tab[i].y = aleat(J.grille.y, J.grille.y + J.grille.height);
            un_ou_deux = aleat(1, 2);
            if (un_ou_deux == 1)
            {
                bout.x = J.B.tab[i].x;
                bout.y = J.B.tab[i].y + J.grille.cellWidth;
            }
            else
            {
                bout.y = J.B.tab[i].y;
                bout.x = J.B.tab[i].x + J.grille.cellWidth;
            }
            affecter_clic_cases(J, J.B.tab[i].x, J.B.tab[i].y, bout.x, bout.y); //affecte de nouvelles valeurs aux clics
            affect_orientation(J.B.tab[i], bout.x, bout.y); //affecte l'orientation au bateau
            if (est_aligne(J.B.tab[i].x, J.B.tab[i].y, bout.x, bout.y)) //si le bateau est bien aligne horizontalement ou verticalement
            {
                if (J.B.tab[i].orientation == 0 && hors_grille_bateau_horizontal(J, i) == false && bateaux_adjacents(J, i) == false) //verifie si le bateau est dans la grille
                {
                    placement_valide = true;
                }
                else
                {
                    if (J.B.tab[i].orientation == 1 && hors_grille_bateau_vertical(J, i) == false && bateaux_adjacents(J, i) == false) //verifie si le bateau est dans la grille
                    {
                        placement_valide = true;
                    }
                }
            }
            if (bateaux_adjacents(J, i))
            {
                placement_valide = false;
            }
            else //on modifie les cases de la grille du joueur si le placement du bateau n'est pas invalide
            {
                modif_case_en_vue(J, i);
                modif_grille_apres_placement_un_bateau(J, i);
            }
        } while (placement_valide == false);
        dessinerUnBateau(J.B.tab[i]);
    }
}

////Test tir case touche

void tir_test(const Joueur& J, int& l, int& c)
{
    lireSouris(c, l); //coordonnees du 1er clic
    c = ((c - J.grille.x) / J.grille.cellHeight) * J.grille.cellHeight + J.grille.x;
    l = ((l - J.grille.y) / J.grille.cellHeight) * J.grille.cellHeight + J.grille.y;
}

void actualisation_affichage_case_touche(const int& l, const int& c, Joueur& J) //on aura verifie deja AVANT que le tir est valide
{
    setcolor(RED);
    bar(c, l, c + J.grille.cellHeight, l + J.grille.cellHeight);
}

void test_placer_bateau_joueur() //test placement bateau pour un joueur
{
    int nb_bateaux = 5;
    Joueur J;
    init_matrice(J);
    afficher_matrice(J);
    init_bateaux(nb_bateaux, J.B);
    opengraphsize(WIDTH, HEIGHT);
    setbkcolor(WHITE);
    dessinerGrille(J.grille);
    setbkcolor(YELLOW);
    PlacerBateauJoueur(nb_bateaux, J);
    afficher_matrice(J);
    getch();
}

void test_placer_bateau_ordi()
{
    int nb_bateaux = 5;
    Joueur Ordi;
    init_matrice(Ordi);
    afficher_matrice(Ordi);
    init_bateaux(nb_bateaux, Ordi.B);
    opengraphsize(WIDTH, HEIGHT);
    setbkcolor(WHITE);
    dessinerGrille(Ordi.grille);
    setbkcolor(YELLOW);
    PlacerBateauOrdi(nb_bateaux, Ordi);
    afficher_matrice(Ordi);
    getch();
}

void test_affichage_bateau_touche()
{
    int nb_bateaux = 5, l, c;
    Joueur J;
    init_matrice(J);
    afficher_matrice(J);
    init_bateaux(nb_bateaux, J.B);
    opengraphsize(WIDTH, HEIGHT);
    setbkcolor(WHITE);
    dessinerGrille(J.grille);
    setbkcolor(YELLOW);
    PlacerBateauJoueur(nb_bateaux, J);
    afficher_matrice(J);
    tir_test(J, l, c);
    actualisation_affichage_case_touche(l, c, J);
    getch();
}

void tests()
{
    //Ajouté
    Grille G;


    //Deja la
    opengraphsize(WIDTH, HEIGHT);
    setbkcolor(WHITE);
    setcolor(BLACK);
    dessinerGrille(G);
    getch();
}

int main()
{
    //tests();

    //Ajouté
    //test_affichage_bateau_touche();

    //test_placer_bateau_joueur();
    //test_placer_bateau_ordi();
    return 0;
}