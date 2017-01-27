#solveur1 : solveur1.c
#	gcc -Wall -o solveur1 solveur1.c

solveur2 : solveur2.c parseur.c parseur.h
	gcc -Wall -o solveur2 solveur2.c parseur.c
