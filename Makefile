#solveur1 : solveur1.c
#	gcc -Wall -o solveur1 solveur1.c

all : main.c parseur.c parseur.h solveur.c solveur.h
	gcc -Wall -o SATsolveur main.c solveur.c parseur.c 
