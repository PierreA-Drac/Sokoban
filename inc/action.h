/**
 * # Nom ..........: AYOUB
 * # Prénom .......: Pierre
 * # N° étudiant ..: 21501002
 *
 * Ce fichier contient les fonctions qui gère la récupération des différentes
 * actions du jeu.
 */

#ifndef __ACTION_H
#define __ACTION_H

#include "structs.h"
#include "consts.h"

/**
 * ####  -----------------------------------------------------------------  ####
 * ##	  Fonctions =====================================================     ##
 * ####  -----------------------------------------------------------------  ####
 */

/** waitAction
 * -----------------------------------------------------------------------------
 * Récupère un clic ou une touche du clavier, et organise le traitement de
 * l'action.
 * -----------------------------------------------------------------------------
 *  Renvoie une action prête à être utilisée.
 */

ACTION waitAction(BUTTON B[], int ButtonHeight, int ButtonWidth);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** getArrowAction
 * -----------------------------------------------------------------------------
 * Récupère la flèche arrow du clavier appuyer, et initialise l'action 
 * en fonction.
 * -----------------------------------------------------------------------------
 * Renvoie une action correspondant à une flèche du clavier.
 */

ACTION getArrowAction(int arrow);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** getKeyAction
 * -----------------------------------------------------------------------------
 * Réupère la touche key du clavier appuyer, et initalise l'action en fonction.
 * -----------------------------------------------------------------------------
 * Renvoie une action correspondant à la touche du clavier.
 */

ACTION getKeyAction(char key);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** getMouseAction
 * -----------------------------------------------------------------------------
 * Récupère le point cliqué A.p, les bouttons B ainsi que leurs hauteurs
 * ButtonHeight et leur largeurs ButtonWidth pour initaliser l'action
 * en fonction.
 * -----------------------------------------------------------------------------
 * Renvoie une action correspondant à un bouton cliqué ou à une case du niveau
 * à changer d'état (pour l'éditeur seulement).
 */

ACTION getMouseAction(ACTION A, BUTTON B[], int ButtonHeight, int ButtonWidth);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** wait_key_arrow_clic_v2
 * -----------------------------------------------------------------------------
 * Fonction bloquante : attends que l'on appuie sur une touche, une flèche du
 * clavier ou un clic sur l'écran. Modifie par effet de bord le point, la touche
 * ou la flèche par le premier évènement qui arrive.
 * -----------------------------------------------------------------------------
 * Renvoie le type d'évènement arrivé : EST_FLECHE, EST_TOUCHE, EST_CLIC,
 * ou EST_RIEN si l'évènement ne correspond à rien.
 * -----------------------------------------------------------------------------
 * N.B. : Remplacement des SDL_KEYDOWN par SDL_KEYUP pour que les actions ne se 
 * font que lorsque l'on relâche la touche, sinon ça va trop vite et un seul 
 * appuie sur la touche enregistre plusieurs action. L'utilisation de la 
 * fonction sleep(1) après la fonction original nous fait attendre un temps trop
 * long par rapport au rythme du jeu.
 */

int wait_key_arrow_clic_v2(char *touche, int *fleche, POINT *P);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** handlingMovement
 * -----------------------------------------------------------------------------
 * Gère le déplacement du personnage et des caisses sur le niveau L en fonction
 * de l'action A.
 * -----------------------------------------------------------------------------
 * Renvoie le niveau L mis à jour avec les déplacements.
 */

LEVEL handlingMovement(LEVEL L, ACTION A);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** getEditCases
 * -----------------------------------------------------------------------------
 * Permet de récupérer les cases dest et dest_box qui doivent être modifiées par
 * la fonction handlingMovement en fonction de l'action A et de la position
 * du personnage L.charac.
 * -----------------------------------------------------------------------------
 * Renvoie le point L.charac contenant les indices de la nouvelle case
 * contenant le personnage.
 */

POINT getEditCases(ACTION A, LEVEL L, CASE** dest, CASE** dest_box);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** isCollision
 * -----------------------------------------------------------------------------
 * Permet de savoir si le personnage peut se déplacer ou s'il rentre en
 * collision en fonction des cases dest et dest_box pour la fonction
 * handlingMovement.
 * -----------------------------------------------------------------------------
 * Renvoie TRUE si le personnage rentre en collision et ne peut donc pas se
 * déplacer, et FALSE si le personnage peut se déplacer.
 */

int isCollision(CASE* dest, CASE* dest_box);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** moveCharac
 * -----------------------------------------------------------------------------
 * Effectue le déplacement du personnage entre les cases src et dest, et
 * modifie la case dest_box si besoin.
 * -----------------------------------------------------------------------------
 */

void moveCharac(CASE* src, CASE* dest, CASE* dest_box);

#endif
