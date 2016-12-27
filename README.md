# Mario Sokoban

## Projet de programmation

### Status

Ce dépôt contient le projet de programmation **Mario Sokoban**.  
Le projet est actuellement *terminé*.

### Fonctionnement

Deux **modes** pour le programme :  
1. *Mode jeu*.  
2. *Mode éditeur*.

**Fonctionnalitées** :
* Lecture des arguments depuis la ligne de commande.
* Lecture des niveaux depuis un fichier,  vérification du format, tolérance aux sauts de ligne.
* Écriture des niveaux dans un fichier (avec création ou mise à jour du fichier).
* Vérification de la résolubilité d'un niveau.
* Vérification de la fermeture des murs d'un niveau autour du personnage.
* Tableau dynamique pour un stockage et affichage adaptatif des niveaux.
* Affichage de sprites pour les niveaux.
* Affichage des informations concernant le niveau (nom, numéro, coups joués).
* Affichage de boutons.
* Affichage proportionnel et en plusieurs résolutions de cases (32x et 16x).
* Gestion de la souris et du clavier.
* Possiblité d'aller en avant ou en arrière dans la partie graĉe à un historique.
* Possibilité de parcourirs les niveaux en avant ou en arrière.
* Possibilité de réinitialiser un niveau.

**Utilisation** :
* ./sokoban filein.xsb
	* Lance le Sokoban en *mode jeu*, en lisant le premier niveau contenu dans le fichier filein.xsb.
* ./sokoban -n 8 filein.xsb
	* Lance le Sokoban en *mode jeu*, en lisant le niveau n°8 contenu dans le fichier filein.xsb.
* ./sokoban -c fileout.xsb
	* Lance le Sokoban en *mode éditeur*, en écrivant le niveau sauvegarder dans le fichier fileout.xsb.

Déroulement d'une **partie de jeu** :  

L'objectif du jeu est de déplacer toutes les caisses sur les emplacements prévu marqués par des croix afin de résoudre le niveau. Vous pouvez pour cela utiliser les flèches du clavier pour déplacer Mario. Vous pouvez utiliser les boutons affichés dans la partie supérieur de l'écran, soit en cliquant dessus avec la souris, ou en utilisant les touches du clavier (U = Undo, R = Redo, P = Prev, N = Next, I = Init, Q = Quit), pour respectivement annuler la dernière action effectuée, rétablir la dernière action effectuée, revenir au niveau précédent, passer au niveau suivant, réinitialiser le niveau actuel (sans perdre l'historique) et quitter le jeu. Une fois le niveau terminé, vous passez automatiquement au niveau suivant.

Déroulement d'une **création de niveau** :  

1. Dans un premier temps, il faut placer, en cliquant sur les cases à la souris, les différents éléments du niveau (mur, caisse sur un emplacement de stockage, personnage). Une fois les éléments placés, vous pouvez cliquer sur Play Back (ou appuyer sur P) pour passer au deuxième temps. Entre ces deux étapes, le niveau sera vérifié : il doit y avoir un et un seul personnage, au moins une caisse sur son emplacement de stockage, et le personnage doit être entouré de mur.  
2. Le niveau à passé les contrôles avec succès, vous pouvez maintenant déplacer votre personnage afin de modifier la position de départ du personnage et la position de départ des caisses dans le niveau. Vous retrouvez les boutons Undo, Redo, Init comme dans le mode jeu, mais aussi le bouton Alea (= A) qui va faire jouer N coups aléatoirement à l'ordinateur sur le personnage. Une fois que le niveau est comme vous le souhaitez, vous pouvez cliquer sur Save (= S) pour sauvegarder le niveau dans le fichier spécifié sur la ligne de commande.

---

## Rapport

### Remarques

Sur le **code** :  

1. Les fonctions d'affichage des boutons et des informations sont à améliorer.  
2. La gestion des coordonnées et des tailles des éléments est un peu archaïques et à revoir (nombres codés en dur, constantes/define et variables éparpillées et pas forcémment cohérentes).  
3. Il faut utiliser une indentation de 8 espaces pour un affichage correct.  
4. Les noms de quelques variables et fonctions pourraient être revu.  
5. La découpe des structures pourraient peut-être être revu, par exemple eclaté en plusieurs sctructures différentes plutôt que tout rassembler dans une seule variable de type SOKOBAN.  

Sur le **projet** :  

1. Suppressions (ignorer) des erreurs de fuites de mémoire liées à la SDL et les fonctions d'affichage graphique de la library X11 grâce au fichier SDL.supp.  
2. Makefile automatisée au plus possible avec des variables et règles d'inférences.  
3. Organisation en sous-dossier.  
4. Historique Git du projet pas très propre, car servis de projet d'apprentissage des branches, des commits réfléchis, des remotes, des merges/diff/etc.

### Questions

1. Mettre le minimum d'include possible (un include inclus tout les autres include nécéssaire) ou mettre chaque include dont le fichier aurait besoin même si cela est superflu ? (Dans le projet : tout les includes ont été mis même si superflu. Ex. : Lib. standards alors que uvsqgraphics.h les inclus déjà).
2. Mettre les includes des fichiers .c dans leurs fichiers .h respectif ou dans les fichiers .c ? (Dans le projet : consts.h et structs.h dans les fichiers .h car nécéssaire, le reste dans les fichiers .c).
3. Bonne méthode pour afficher des éléments et des textes proportionnellement à la taille de la fenêtre ?
4. Tabulation ou espaces ? (Dans le projet : tabulation).
5. Juste avant un exit(EXIT_FAILURE), sommes-nous supposé libérer la mémoire de tout ce qui à été alloué ?
