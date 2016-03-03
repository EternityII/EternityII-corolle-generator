# Compte rendu de l'avancée jusqu'au 03.03.2016

## Taches effectués

- [x] Effectuer la transition vers le C++
- [ ] **En Cours** Générer les fichier corolles : 
 
- structure souhaitée : `[taille_du_plateau]/[hamming]_[coordonnees de la piece]_[n°piece]_[rotation].txt`
- exemple : `4/1_0_0_0.txt` est le fichier pour un 
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

### Effectuer la transition vers le C++

Afin de générer au mieux les corolles, plusieurs classes ont été crées :

- `Piece` représente une pièce unique
    - Orientation de la pièce
    - type de piece (bord, coin, interieur)
    - tableau `couleurs` des bords
- `Corolle` qui définit l'objet Corolle avec la taille de la pièce
    - taille de la corolle
    - type de la corolle (Corolle de coin [triangle], ...)
    - Hamming
    - `Piece`s de la corolle 
- `Jeu` contient les données du jeu :
    - les pièces
    - nombre de pieces
    - taille du plateau
- `Generator` s'occupe de la génération récursive des fichiers corolles (construit et demande l'écriture d'une `Corolle` dans le bon fichier).
    - l'instance actuelle `Jeu`
    - tableau des `Piece`s `disponibles` (non posées)
    - le hamming et la taille et le type de la corolle a générer
    - Le `plateau` nécessaire à la génération récursive
    - taille du plateau (redondance depuis `Jeu`);

- `FileIn` et `FileOut` s'occupent respectivement des 
    - import des pièces depuis un fichier
    - export des corolles dans un fichier, avec la convention définie [ici](#convention) 

## Développement futur
 
- [ ] Perfectionner l'ouverture et la fermeture des fichiers d'entrée et sortie
- [ ] import des corolles
- [ ] permettre la génération recursive de tout type de corolle