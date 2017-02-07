#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parseur.h"
#include "solveur.h"


int main(int argc, char* argv[]){
	if (argc > 0) {
		printf("%d\n", argc);
		cnf* formule = P_parse(argc, argv);
		printf("plap1\n");
		/*int isSat = S_DPLL(formule);
		printf("plap3\n");
		if (isSat){
			printf("SAT\n"); 
		}
		else{
			printf("UNSAT\n");
		}*/
		S_DPLL(formule);
		

	}
}