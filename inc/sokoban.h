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
 * # Contrôles ................................................................:
 */

/** whatIsCaseType
 * -----------------------------------------------------------------------------
 * Détermine le type de la case en fonction du char c passé en argument.
 * -----------------------------------------------------------------------------
 * Renvoie le type CASE_TYPE de la case correspondant au caractère.
 */

CASE_TYPE whatIsCaseType(char c);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** isResolvable
 * -----------------------------------------------------------------------------
 * Vérifie si le niveau L est correct et résoluble.
 * -----------------------------------------------------------------------------
 * Retourne TRUE si le niveau est correct, FALSE s'il ne l'est pas.
 */

int isResolvable(LEVEL L);

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

#endif
