# Mario Sokoban

## Projet de programmation

### Status :

Ce dépôt contient le projet de programmation **Mario Sokoban**.  
Le projet est actuellement *en cours de développement*.
---
Fonctionnalitées restantes à programmer :
* Éditeur de niveau
* Écriture des niveaux crée dans un fichier
* Vérification de la fermeture des murs d'un niveau

### Fonctionnalitées :

Deux modes pour le programme :  
1. Mode jeu  
2. Mode éditeur
---
Fonctionnalitées :
* Lecture depuis la ligne de commande
* Lecture des niveaux depuis un fichier
* Vérification de la résolubilité d'un niveau
* Tableau dynamique pour un stokage adaptatif des niveaux
* Affichage de sprites pour les niveaux
* Affichage des informations concernant le niveau (nom, numéro, coups joués)
* Affichage de boutons
* Affichage proportionnel et en plusieurs résolutions de cases (32x et 16x)
* Gestion de la souris et du clavier
* Historique pour aller en avant ou en arrière dans notre partie
* Possibilité de parcours les niveaux en avant ou en arrière
* Possibilité de réinitialiser un niveau
---
Utilisation :
* ./sokoban filein.xsb
	* Lance le Sokoban en mode jeu, en lisant le premier niveau contenu dans le fichier filein.xsb.
* ./sokoban -n 8 filein.xsb
	* Lance le Sokoban en mode jeu, en lisant le niveau n°8 contenu dans le fichier filein.xsb.
* ./sokoban -c fileout.xsb
	* Lance le Sokoban en mode éditeur, en écrivant le niveau sauvegarder dans le fichier fileout.xsb.

## Rapport

### Remarques :

1. Les fonctions d'affichages des boutons et des informations sont à améliorer.
2. La gestion des coordonnées et des tailles des éléments est archaïques et à revoir (nombres codés en dur, constantes/define et variables éparpillées et pas forcémment cohérentes).
3. Suppressions des erreurs de fuites de mémoire liées à la SDL et les fonctions d'affichage graphique de la library X11 grâce au fichier SDL.supp.
4. Utiliser une indentation de 8 espaces pour un affichage correct.

### Questions :

1. Mettre le minimum d'include possible (un include inclus tout les autres include nécéssaire) vs. Mettre chaque include dont le fichier aurait besoin même si cela est superflu ?
2. Bonne méthode pour afficher des éléments et des textes proportionnellement à la taille de la fenêtre ?
3. Tabulation vs Espaces ?
