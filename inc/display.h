/**
 * # Nom ..........: AYOUB
 * # Prénom .......: Pierre
 * # N° étudiant ..: 21501002
 *
 * Ce fichier contient les fonctions d'affichage du programme.
 */

#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "structs.h"
#include "consts.h"

/**
 * 1. Variables externes ......................................................:
 */

/* Surface de notre fenêtre définie dans graphics.c */
extern SDL_Surface* SDL_screen;

/**
 * 2. Fonctions d'interface ...................................................:
 */

/**
 * 2.1 Initialisation de l'affichage ..........................................:
 */

/** initDisplay
 * =============================================================================
 * Initialise et lance l'affichage de S.
 * =============================================================================
 * N.B. : Fuites de mémoires détectées avec Valgrind à partir de 
 * l'initialisation de la SDL. Après recherches sur internet, c'est normal.
 */

void initDisplay(SOKOBAN S);

/**
 * 2.2 Affichage ..............................................................:
 */

/** displaySokoban
 * =============================================================================
 * Organise l'affichage de la fenêtre du Sokoban S.
 * =============================================================================
 * N.B. : Nouvelles fuites de mémoire supplémentaires détéctées avec 
 * l'utlisation de cette fonction. Cause : Pas de SDL_FreeSurface dans la 
 * fonction "affiche_image" définie dans "graphics.c".
 */

void displaySokoban(SOKOBAN S);

/* -------------------------------------------------------------------------- */

/** initButtons
 * =============================================================================
 * Initialise les coordonnées des boutons du Sokoban S, leur taille en pixel 
 * et appel le reste de l'initialisation.
 * =============================================================================
 * Renvoie un Sokoban S avec des boutons initialisés et prêt à être afficher.
 */

SOKOBAN initButtons(SOKOBAN S);

/* -------------------------------------------------------------------------- */

/** displayMessage
 * =============================================================================
 * Affiche la chaîne de caractère pointée par text en bas de l'écran, et attends
 * le nombre de secondes spécifié par WAIT_TIME_MESSAGE.
 * =============================================================================
 */

void displayMessage(char* text);

/**
 * 2.3 Fermeture de l'affichage ...............................................:
 */

/** quitDisplay
 * =============================================================================
 * Libère la mémoire de la surface de la fenêtre et ferme proprement la SDL.
 * =============================================================================
 */

void quitDisplay();

/**
 * 3. Fonctions locales .......................................................:
 */

/** initSpecificButton
 * =============================================================================
 * Initialise le boutton B de manière individuel (nom, action) en fonction du
 * mode M du programme et de son numéro i.
 * =============================================================================
 * Renvoie un bouton B entièrement initialisé.
 */

BUTTON initSpecificButton(BUTTON B, int i, MODE M);

/* -------------------------------------------------------------------------- */

/** displayButtons
 * =============================================================================
 * Affiche le fond, les séparateurs et le noms des boutons du tableau B en
 * fonction du mode M.
 * =============================================================================
 */

void displayButtons(BUTTON B[], float W, float H, MODE M);

/* -------------------------------------------------------------------------- */

/** displayLevel
 * =============================================================================
 * Affiche le niveau L en fonction du type de chaque case.
 * =============================================================================
 */

void displayLevel(LEVEL L);

/* -------------------------------------------------------------------------- */

/** displayInfosLevel
 * =============================================================================
 * Affiche les informations concernant le niveau L à l'écran.
 * =============================================================================
 */

void displayInfosLevel(LEVEL L, int h_but);

#endif
