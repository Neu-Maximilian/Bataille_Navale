#pragma once
#include <iostream>
#include <array>
#include <string>

#define HEIGHT 720
#define WIDTH 1280
#define CASES 10
#define NB_BATEAUX_MAX 7

using namespace std;

enum states
{
	VIDE = 0, CASE_EN_VUE = -1, RATE = -2, TOUCHE = -3, COULE = -4
};

enum bateau_type
{
	PORTE_AVION = 5, CROISEUR = 4, CONTRE_TORPILLEUR = 3, TORPILLEUR = 2
};

struct Point
{
	int x, y;
};

/**
 *Structure pour les boutons contient: les coordonnées (x1,y1) et (x2,y2) du coin supérieur gauche et du coin inférieur droit, la couleur, et le texte a afficher.
 */
struct Bouton
{
	int x1, y1, x2, y2;
	int couleur;
	const char* texte;
};

/**
 *Structure pour les bateaux contient: l'id du bateau [1-6], les coordonnées (x,y) du coin supérieur gauche, la taille, l’état (-1 = intact, -3 = touche, -4 = coule), et l'orientation (0 = horizontal, 1 = vertical).
 */
struct Bateau
{
	int id;
	int x;
	int y;
	int taille;
	int state;
	int orientation; // 0 = horizontal, 1 = vertical
};

using TAB_GRILLE = array<array<int, CASES>, CASES>;
using TAB_BATEAUX = array<Bateau, NB_BATEAUX_MAX>;

/**
 *Structure pour les grilles contient: les coordonnées (x,y) du coin supérieur gauche, la largeur et la hauteur,la largeur et la hauteur d'une case, un tableau de 10x10 cases contenant : 0 = vide, [1-6] = id_bateau, -1 = case en vue, -2 = rate, -3 = touche, -4 = coule , le nombre de bateaux, et un tableau de bateaux.
 */
struct Grille
{
	int x;
	int y;
	int width = 400;
	int height = 400;
	int cellWidth = width / CASES;
	int cellHeight = height / CASES;
	TAB_GRILLE tabGrille;
	int nbBateaux;
	TAB_BATEAUX tabBateaux;
};

/**
 * Structure pour les joueurs contient: le nom du joueur et sa grille.
 */
struct Joueur
{
	string nom;
	Grille grille;
};

// Fonctions et procedures

/**
 * \param a entier minimum
 * \param b entier maximum
 * \return un entier aléatoire entre a et b
 */
int aleat(int a, int b);

/**
 * \param x coordonnée x de la souris
 * \param y coordonnée y de la souris
 * \brief attend que l'utilisateur clique sur la souris et retourne les coordonnées de la souris
 */
void lireSouris(int& x, int& y);

/**
 * Dessine un bouton a la position et de la couleur donnee dans la structure Bouton.
 * \param B un bouton
 */
void dessinerBouton(const Bouton& B);

/**
 * Dessine une grille a la position et de la couleur donnee dans la structure Grille.
 * \param G une grille
 */
void dessinerGrille(const Grille& G);

/**
 * Dessine un bateau a la position et de la couleur donnee dans la structure Bateau.
 * * \param B un bateau
 * */
void dessinerBateau(const Bateau& B);

/**
 * Place un bateau sur la grille. Place aussi les cases en vue autour du bateau.
 * \param B un bateau
 * \param G une grille
 * \return true si le bateau a ete place, false sinon
 */
bool placerBateau(Bateau& B, Grille& G);

/**
 * Place les bateaux aléatoirement sur la grille.
 * \param T un tableau de bateaux
 * \param G une grille
 */
void placerBateauxAleat(TAB_BATEAUX& T, Grille& G);

/**
 * Place les bateaux du joueur sur la grille.
 * \param T un tableau de bateaux
 * \param G une grille
 */
void placerBateauxJoueur(TAB_BATEAUX& T, Grille& G);

/**
 * \param G une grille
 * \param x indice de la ligne de la case
 * \param y indice de la colone de la case
 * \Dessine une case a la position (x,y) de la grille G.
 */
void dessinerCase(int x, int y, const Grille& G);

/**
 * \param G une grille
 * \param x indice de la ligne de la case
 * \param y indice de la colone de la case
 * \return le statut du tir (-1 = case en vue, -2 = rate, -3 = touche, -4 = coule)
 */
int tirer(Grille& G, int x, int y);

/**
 * \param G une grille
 * \param x coordonnée x de la souris
 * \param y coordonnée y de la souris
 */
void tirerJoueur(int& x, int& y, Grille& G);

/**
 * \param G une grille
 * \param x coordonnée x de la souris
 * \param y coordonnée y de la souris
 * \param modeDifficile true si le mode difficile est active, false sinon
 */
void tirerOrdi(int& x, int& y, bool modeDifficile, Grille& G);

// Initialisation du jeu

/**
 * Initialise la fenêtre.
*/
void initFenetre();

/**
 * Initialise le bouton.
 * \param B un bouton
 * \param x1 la coordonnée x du coin supérieur gauche du bouton
 * \param y1 la coordonnée y du coin supérieur gauche du bouton
 * \param x2 la coordonnée x du coin inférieur droit du bouton
 * \param y2 la coordonnée y du coin inférieur droit du bouton
 * \param couleur la couleur du bouton
 * \param texte le texte a afficher dans le bouton
 */
void initBouton(Bouton& B, int x1, int y1, int x2, int y2, int couleur, const char* texte);

/**
 * Affiche le menu.
*/
void menu(bool &choixMultiJoueur, bool &choixDifficile, bool &choixTirSalves, bool &choixCaseEnVue, bool &choix6Bateaux);

/**
 * Initialise le bateau.
 * \param B un bateau
 * \param id l'id du bateau
 * \param x la coordonnée x du bateau
 * \param y la coordonnée y du bateau
 * \param size la taille du bateau
 * \param orientation l'orientation du bateau
 */
void initBateau(Bateau& B, int id, int x, int y, int size, int orientation);

/**
 * Initialise le tableau de la grille.
 * \param T un tableau de la grille
 */
void initTabGrille(TAB_GRILLE& T);

/**
 * Initialise la grille.
 * \param G une grille
 * \param x la coordonnée x de la grille
 * \param y la coordonnée y de la grille
 * \param tabGrille le tableau de la grille
 * \param nbBateaux le nombre de bateaux
 * \param tabBateaux le tableau de bateaux
 */
void initGrille(Grille &G, int x, int y, TAB_GRILLE tabGrille, int nbBateaux, TAB_BATEAUX tabBateaux);

/**
 * Initialise le joueur.
 * \param J un joueur
 * \param nom le nom du joueur
 * \param grille la grille du joueur
 * \param nbBateaux le nombre de bateaux du joueur
 * \param tabBateaux le tableau de bateaux du joueur
 */
void initJoueur(Joueur& J, string nom, Grille grille, int nbBateaux, TAB_BATEAUX tabBateaux);

/**
 * Initialise le jeu.
 * \param J1 le joueur 1
 * \param J2 le joueur 2
 * \param choixMultiJoueur true si le mode multijoueur est active, false sinon
 * \param choixDifficile true si le mode difficile est active, false sinon
 * \param choixTirSalves true si le mode tir salves est active, false sinon
 * \param choixCaseEnVue true si le mode case en vue est active, false sinon
 * \param choix6Bateaux true si le mode 6 bateaux est active, false sinon
 */
void jeu(Joueur& J1, Joueur& J2, bool choixMultiJoueur, bool choixDifficile, bool choixTirSalves, bool choixCaseEnVue, bool choix6Bateaux);

/**
 * Écran de fin de partie.
 * \param J1 le joueur 1
 * \param J2 le joueur 2
*/
void finPartie(Joueur& J1, Joueur& J2);