# Compte rendu de la réunion du 24.03.2016

## Sujets et notions abordées

### Smartforce

Il est maintenant interessant, avec les chiffres actuels, d'envisager une transition vers la smartforce

#### SmartForce de niveau 1 (SF1)

Le but de cette méthode, est de modifier le comportement lors de la verification de la *placabilité* d'une pièce.

Le fonctionnement est simple :

A chaque fois qu'une pièce est placée, tous les tableaux sont mis à jour.

##### donnees :
    
1. tableau des pièces
1. matrice 2D (plateau)
1. une matrice (booléenne) cases x pièces. (vrai si la pièce est placable sur cette case, met a jour le tableau des comptes)
1. deux tableaux de comptes
    - nombre de case où une pièce peut etre posée
    - nombre de pièces placable sur une case donnée
1. deux tableaux de disponibilités (~peut devenir une liste chainée de pointeurs vers la pièce ou la case)
    - si la case est occupée
    - si la pièce est posée


#### SmartForce de niveau 2 (SF2)

C'est une approche encore plus fine que *SF1* car une case et la pièce est définie par sa frontière (bord colorés).

A chaque fois qu'une pièce est posée, on met a jour les cases adjacentes (récursivement) en mettant à jour les pieces placables sur les cases adjacentes, et donc les couleurs possible de ces cases la (propagation sur le plateau)

##### données

1. tableau des pieces
1. matrice 2D (plateau) (nécessaire pour tester les possibilités)
1. deux tableaux de disponibilités (~peut devenir une liste chainée de pointeurs vers la pièce ou la case ) [~peut-etre possible de simplifier avec le plateau]
    - si la case est occupée
    - si la pièce est posée
1. une matrice (booléenne) cases x pièces. (vrai si la pièce est placable sur cette case, met a jour le tableau des comptes)
1. deux tableaux de comptes
    - nombre de case où une pièce peut etre posée
    - nombre de pièces placable sur une case donnée
1. 4 matrices de comptes pour chaque case (correspondant à chaque bord)
    - chaque bord de chaque case compte le nombre d'occurences possibles de chaque couleur suivant les pièces placable à cette case (et met a jour la matrice booléenne dans le cas où une couleur tombe à zero)


## A faire

-[ ] Finir les parcours bruteforce
-[ ] Finir calcul des corolle
-[ ] Finir les parcours Comptage des occurences
-[ ] Commencer SF2