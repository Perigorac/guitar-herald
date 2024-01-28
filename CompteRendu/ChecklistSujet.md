# Petite checklist pour track les attendus du sujet

[v] = complété
[x] = rempli jusqu'à nouvel ordre, à vérifier à chaque commit
[?] = obscur
[] = non rempli

# Les attendus

[] 8 classes
7 pour l'instant

[v] 3 niveaux de hiérarchie
> NormalPuck <- RoundPuck <- FallingObject

[v] 2 fonctions virtuelles différentes et utilisées à bon escient
> FallingObject::draw() et FallingObject::computeScore()

[v] 2 surcharges d’opérateurs
FallingObject& FallingObject::operator+=(float yfall) et float FallingObject::operator>=(float value)

[v] 2 conteneurs différents de la STL
> notepattern est un map, notes est un vector

[] diagrammme de classe UML complet

[] commentaire du code
Pour l'instant uniquement les grandes étapes de la boucle principale de jeu

[?] pas d’erreurs avec Valgrind

[] rendu par dépôt git, adresse à envoyer par mail avec dans le sujet le motif [EISE/MAIN 4 C++ Projet]

[x] pas de méthodes/fonctions de plus de 30 lignes (hors commentaires, lignes vides et assert);

[v] utilisation d’un Makefile avec une règle ”all” et une règle ”clean” ou autre outil de build automatique
CHECK.

[?] utilisation de tests unitaires
