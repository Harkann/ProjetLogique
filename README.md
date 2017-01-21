# ProjetLogique
Projet logique ENS Cachan 2016-2017

# Format des formules propositionelles :
p cnf N:2 M:3 
1 -1 0
2 1 3
-1 0
N : nombre de clauses
M : nombre de vraiables 
0 : fin d'une clause
Une clause peut s'étaler sur plusieurs lignes.

on malloc un tableau de taille N
il pointe vers N tableaux de taille ???
On parcourt la liste des arguments et on crée des tableaux de taille nombre d'arguments de chaque clause. (on a donc ici : [[1,-1],[2,1,3,-1]]).




On parcourt le tableau des clauses.
Pour chaque sous tableau on checke les possibilités.
