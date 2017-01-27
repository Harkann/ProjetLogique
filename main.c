#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parseur.h"
#include "solveur.h"


int main(int argc, char* argv[]){
	cnf* formule;
	int* res;
	formule = P_parse(argc, argv);
	res = malloc(P_nlit(formule)*sizeof(int));
	int isSat = S_naif(formule, res);
	if (isSat == 0){
		printf("SAT\n"); 
		for (int i = 0; i < P_nlit(formule); ++i)
		{
			printf("%d ", res[i]);
		}
		printf("\n");
	}
	else{
		printf("UNSAT\n");
	}
}