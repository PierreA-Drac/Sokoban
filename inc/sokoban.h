/**
 * # Nom ..........: AYOUB
 * # Prénom .......: Pierre
 * # N° étudiant ..: 21501002
 *
 * Ce fichier contient la fonction main, appelant toutes les
 * fonctions nécessaires aux grandes étapes de gestion du jeu.
 */

#ifndef __SOKOBAN_H
#define __SOKOBAN_H

#include "structs.h"
#include "consts.h"

/**
 * 1. Fonctions du MAIN .......................................................:
 */

/** preInitStarting
 * =============================================================================
 * Organise la pré-initialisation du Sokoban S en récupérant les informations
 * depuis la ligne de commande, et en initialisant la fonction rand par le temps
 * actuel pour la gestion de l'aléatoire.
 * =============================================================================
 * Renvoie un Sokoban S prêt à être initialisé.
 */

SOKOBAN preInitStarting(SOKOBAN S, int argc, char** argv);

/* -------------------------------------------------------------------------- */

/** initSokoban
 * =============================================================================
 * Lance l'initialisation du Sokoban S en fonction de si le mode est à jouer ou
 * éditeur, et initialise ensuite l'affichage.
 * =============================================================================
 * Renvoie le Sokoban S prêt à être afficher.
 */

SOKOBAN initSokoban(SOKOBAN S);

/* -------------------------------------------------------------------------- */

/** handlingGame
 * =============================================================================
 * Gère le déroulement d'une partie sur un niveau d'un Sokoban S en initialisant
 * l'action A, en affichant le Sokoban, en récupérant l'action de l'utilisateur
 * et en modifiant le Sokoban en fonction de cette action. Test à chaque coup 
 * si l'utilisateur à gagner la partie. Modifie par effet de bord l'action A 
 * pour le cas où l'on veut quitter.
 * =============================================================================
 * Revnvoie le Sokoban S modifié par l'utilisateur.
 */

SOKOBAN handlingGame(SOKOBAN S, ACTION* A);

/* -------------------------------------------------------------------------- */

/** handlingWin
 * =============================================================================
 * Test si l'utilisateur à gagner, si oui, gère l'écran de fin, libère la
 * mémoier et fait passer le Sokoban S au niveau suivant.
 * =============================================================================
 * Renvoie le Sokoban S au niveau suivant si le niveau est terminé.
 */

SOKOBAN handlingWin(SOKOBAN S);

/* -------------------------------------------------------------------------- */

/** handlingEditor
 * =============================================================================
 * Gère le déroulement de l'édition d'un niveau du Sokoban S en affichant le
 * Sokoban, en récupérant l'action de l'utilisateur et en modifiant le 
 * Sokoban en conséquence. Modifie l'action A par effet de bord pour le cas
 * où l'on veut quitter.
 * =============================================================================
 * Renvoie le Sokoban S modifié par l'utilisateur.
 */

SOKOBAN handlingEditor(SOKOBAN S, ACTION* A);

/* -------------------------------------------------------------------------- */

/** quitSokoban
 * =============================================================================
 * Gère la fermeture du Sokoban en libérant proprement toute la mémoire alloué.
 * =============================================================================
 * Renvoie le Sokoban S avec un historique et un niveau désalloué de la mémoire.
 */

SOKOBAN quitSokoban(SOKOBAN S);

#endif
