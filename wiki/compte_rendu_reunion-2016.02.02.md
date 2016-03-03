# Compte rendu de la réunion du 02.02.2016

## A faire:

- [ ] Effectuer la transition vers le C++
- [ ] Générer les fichier corolles : 
    - structure souhaitée : `output/[taille_du_plateau]/[hamming]_[coordonnees de la piece]_[n°piece]_[rotation].txt` <a name="convention"></a>
    - exemple : `output/4/1_0_0_0.txt` est le fichier pour un 
        - plateau de taille 4, 
        - la corolle générée est de hamming 1, 
        - triangle, 
        - Origine : piece 1
        - non tournée

- [ ] analyser les données 
    - nombre de possibilités
    - Pièces les plus présentes
    - ratio de perte entre le hamming 1 et hamming x
    - ...

## Sujet et notions abordés 

### Smart force : 

Le but de la smart force va etre d'optimiser l'arbre de parcours. Pour ce faire, il faut mettre en place un système de tables qui permettent de prévoir les pièces potentiellement placables grace au corolles générées par le programme de génération des fichiers de corolle. Afin de completer savoir le plus rapidement possible si la pièce a placer permettra de trouver la solution.

Pour faire cela, il est nécessaire de définir plusieurs tableaux :

- Pour chaque corolle :
    1. Un tableau des pieces de la corolle à chaque position [de la corolle]
        - taille: (taille de la corolle) * (nombre de pièces dans la corolle)
    1. 4 tableau des maillages (exemple : le meme triangle orientée pour chaque coin)
        - taille: (nombre de solution générés) * (nombre de pièces de la corolle)
        - remarque : replique du fichier corolle en lien dansant
    1. **Possibility matrix**
        - *taille* : (taille du tableau (`true` la où elle peut etre posée))*(nombre de pièces)
    1. matrice de la posabilité de la corolle sur le plateau
    1. matrice du nombre de pièces placable qui compte le nombre d'occurence de la pièce dans la corolle ( la meme que le 1 ?)

A chaque pièce posée, il est nécessaire de mettre a jour toutes les corolles et leur tables, afin de réduire le nombre de cas possible de manière drastique. Il est possible de les mettre à jour avec le GPU car la mise à jour est identique et indépendante pour chaque corolle.