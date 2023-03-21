
# Projet de Programmation 2022-2023 Bataille Navale

## Readme

### Introduction

Le projet de programmation consiste à réaliser un jeu de bataille navale. Le jeu sera développé en C++ et utilisera la bibliothèque graphique WinBGIm. Le jeu sera développé en binôme (Maximilian NEU et Tieu Han TRAN).

### Description du projet

Le jeu comporte deux modes de jeu : un mode solo et un mode multijoueur. Le mode solo permet de jouer contre l'ordinateur. Le mode multijoueur permet de jouer contre un autre joueur. Le jeu se joue sur une grille de 10x10 cases. Chaque joueur dispose de 5 bateaux de tailles différentes. Le but du jeu est de couler tous les bateaux de l'adversaire. Le joueur qui coule tous les bateaux de l'adversaire gagne la partie.

#### Structure du projet

Le projet est composé des fichiers suivants :

* `main.cpp` : fichier principal du projet
* `bataille_navale.h` : fichier d'en-tête du projet
* `bataille_navale.cpp` : fichier source du projet
* `README.md` : fichier de description du projet
* `lib\graphics.h` : fichier d'en-tête de la bibliothèque graphique
* `lib\winbgim.h` : fichier source de la bibliothèque graphique
* `docs\Cahier_Des_Charges.*` : Cahier des charges du projet
* `build\*` : Dossier de build du projet

#### Fonctionnalités

Le jeu comporte les fonctionnalités suivantes :

* Mode solo ou multijoueur
* Mode de tir
* Placement des bateaux
* Tir sur les bateaux
* Affichage des bateaux

#### Interface graphique

L'interface graphique du jeu est composée de 2 grilles de 10x10 cases. Chaque case est représentée par un carré de 50x50 pixels. Chaque case est colorée en fonction de l'état du bateau :

* Vert : bateau non touché
* Rouge : bateau touché
* Gris : bateau coulé
* Blanc : mer

### Ressources

* [WinBGIm](http://winbgim.codecutter.org/)
