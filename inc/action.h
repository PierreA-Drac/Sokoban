/**
 * # Nom ..........: AYOUB
 * # Prénom .......: Pierre
 * # N° étudiant ..: 21501002
 *
 * Ce fichier contient les fonctions qui gère la récupération et les
 * applications des différentes actions du jeu.
 */

#ifndef __ACTION_H
#define __ACTION_H

#include "structs.h"
#include "consts.h"
#include "historic.h"

/**
 * # Détermination de l'action ...............................................:
 */

/** waitAction
 * -----------------------------------------------------------------------------
 * Récupère un clic ou une touche du clavier, et organise le traitement de
 * l'action en fonction du mode.
 * -----------------------------------------------------------------------------
 * Renvoie une action prête à être traitée.
 */

ACTION waitAction(BUTTON B[], int ButtonHeight, int ButtonWidth, MODE M);

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
 * Réupère la touche key du clavier appuyer, et initialise l'action en fonction.
 * -----------------------------------------------------------------------------
 * Renvoie une action correspondant à la touche du clavier.
 */

ACTION getKeyAction(char key, MODE M);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** getMouseAction
 * -----------------------------------------------------------------------------
 * Récupère le point cliqué A.p, les bouttons B ainsi que leurs hauteurs
 * ButtonHeight et leur largeurs ButtonWidth pour initaliser l'action
 * en fonction du mode.
 * -----------------------------------------------------------------------------
 * Renvoie une action correspondant à un bouton cliqué ou à une case du niveau
 * à changer d'état (pour l'éditeur seulement).
 */

ACTION getMouseAction(ACTION A, BUTTON B[], int ButtonHeight, 
					    int ButtonWidth, MODE M);

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
 * # Modification par l'action ................................................:
 */

/**
 * ## Déplacement du personnage par action de l'utilisateur ...................:
 */

/** handlingMovement
 * -----------------------------------------------------------------------------
 * Gère le déplacement du personnage et des caisses sur le niveau L en fonction
 * de l'action A, et met à jours l'historique.
 * -----------------------------------------------------------------------------
 * Renvoie le niveau L mis à jour avec les déplacements et l'historique.
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

POINT getEditCases(ACTION_TYPE A, LEVEL L, CASE** dest, CASE** dest_box);

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
 * Si on à modifié une caisse, renvoie un pointeur vers la case de destination
 * de la caisse. Sinon, renvoie NULL. Cela permet de mettre à jour l'historique.
 */

CASE* moveCharac(CASE* src, CASE* dest, CASE* dest_box);

/**
 * ## Déplacement du personnage par Undo .....................................:
 */

/** undo
 * -----------------------------------------------------------------------------
 * Gère l'annulation de la dernière action en déplacant le personnage
 * et éventuellement la caisse poussée sur le niveau L.
 * -----------------------------------------------------------------------------
 * Renvoie le niveau L avec la dernière action annulée.
 */

LEVEL undo(LEVEL L);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** undo_getEditCases
 * -----------------------------------------------------------------------------
 * Gestion des pointeurs des cases à modifié src et dest sur le niveau L en
 * fonction de l'action A.
 * -----------------------------------------------------------------------------
 * Retourne le point contenant les indices du nouvel emplacement du personnage.
 */

POINT undo_getEditCases(ACTION_TYPE A, LEVEL L, CASE** src, CASE** dest);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** undo_moveCharac
 * -----------------------------------------------------------------------------
 * Déplace le personnage entre les cases pointées par src et dest, et
 * éventuellement une caisse avec les informations contenu dans E.
 * -----------------------------------------------------------------------------
 */

void undo_moveCharac(HISTOELEM* E, CASE* src, CASE* dest);

/**
 * ## Déplacement du personnage par Redo ......................................:
 */

/** redo
 * -----------------------------------------------------------------------------
 * Gère l'annulation de l'annulation de la dernière action en déplacant le 
 * personnage et éventuellement la caisse poussée sur le niveau L.
 * -----------------------------------------------------------------------------
 * Renvoie le niveau L avec la dernière action dé-annulée.
 * -----------------------------------------------------------------------------
 */

LEVEL redo(LEVEL L);

/**
 * ## Ré-initialisation du niveau .............................................:
 */

/** reInitGame
 * -----------------------------------------------------------------------------
 * Ré-initilise le niveau sans réinitialiser l'historique.
 * -----------------------------------------------------------------------------
 * Renvoie le niveau L à la position initial.
 */

LEVEL reInitGame(LEVEL L);

#endif
