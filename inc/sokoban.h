/**
 * # Nom ..........: AYOUB
 * # Prénom .......: Pierre
 * # N° étudiant ..: 21501002
 *
 * Ce fichier contient la fonction main, appelant toutes les
 * fonctions nécéssaires aux grandes étapes de gestion du jeu,
 * ainsi que quelques fonctions globales au jeu et à l'éditeur.
 */

#ifndef __SOKOBAN_H
#define __SOKOBAN_H

#include "structs.h"
#include "consts.h"
#include "action.h"
#include "game.h"
#include "display.h"
#include "editor.h"
#include "historic.h"

/**
 * # Gestion des arguments ....................................................:
 */

/** checkArgs
 * -----------------------------------------------------------------------------
 * Vérifie le nombre d'argument de la ligne de commande, appel les fonctions
 * d'initialiation du mode, du numéro du niveau et du nom du fichier cible.
 * -----------------------------------------------------------------------------
 * Renvoie un SOKOBAN S prêt à être initialisé.
 */

SOKOBAN checkArgs(int argc, char** argv);

/**
 * ## Contrôles et tests  .....................................................:
 */

/** isResolvable
 * -----------------------------------------------------------------------------
 * Vérifie si le niveau L est correct et résoluble.
 * -----------------------------------------------------------------------------
 * Retourne TRUE si le niveau est correct, FALSE s'il ne l'est pas.
 */

int isResolvable(LEVEL L);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** isClose
 * -----------------------------------------------------------------------------
 * Parcours récursivement toutes les cases où le personnage peut se déplacer
 * à partir de sa position pour savoir si le niveau L est fermé ou non.
 * -----------------------------------------------------------------------------
 * Renvoie TRUE si le niveau L est fermer, FALSE s'il ne l'est pas.
 */

int isClose(LEVEL L, POINT P);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** initChecking
 * -----------------------------------------------------------------------------
 * Initialise les variables du niveau L vérifiant qu'une case à été testée
 * à FALSE.
 * -----------------------------------------------------------------------------
 * Renvoie le niveau L prêt à être testé.
 */

LEVEL initChecking(LEVEL L);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** findCharac
 * -----------------------------------------------------------------------------
 * Cherche la case dans la map de largeur w et de hauteur h qui contient le
 * personnage.
 * -----------------------------------------------------------------------------
 * Renvoie un point comportant les indices en largeur et en hauteur de la case 
 * qui contient le personnage.
 */

POINT findCharac(CASE** map, int w, int h);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** isSaveable
 * -----------------------------------------------------------------------------
 * Permet de savoir si le niveau peut être sauvegardé ou pas. Si le niveau
 * arrive à cette fonction, c'est qu'il n'y à déjà qu'un personnage, au moins
 * une caisse sur son emplacement et que la map est fermée. Il ne reste qu'à
 * tester si l'utilisateur à déplacer la caisse de son emplacement.
 * -----------------------------------------------------------------------------
 * Renvoie TRUE si le niveau peut-être sauvegarder, sinon FALSE.
 */

int isSaveable(LEVEL L);

/**
 * # Gestion de la mémoire ....................................................:
 */

/** mallocMap
 * -----------------------------------------------------------------------------
 * Alloue dynamiquement la mémoire pour une map d'un niveau de largeur int w et
 * de hauteur int h.
 * -----------------------------------------------------------------------------
 * Renvoie un tableau à double dimensions CASE** map alloué et non-initialisé.
 */

CASE** mallocMap(int w, int h);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** freeMap
 * -----------------------------------------------------------------------------
 * Libère la mémoire d'une map d'un niveau de Sokoban.
 * -----------------------------------------------------------------------------
 * Renvoie un pointeur NULL après avoir libérée la mémoire.
 */

CASE** freeMap(CASE** map, int w, int h);

/**
 * ## Gestion de l'aléatoire ..................................................:
 */

/** rand_a_b
 * -----------------------------------------------------------------------------
 * Génère un nombre pseudo-aléatoire compris entre les bornes [a, b[.
 * -----------------------------------------------------------------------------
 * Renvoie l'entier généré.
 */

int rand_a_b(int a, int b);

#endif
