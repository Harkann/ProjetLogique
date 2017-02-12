#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parseur.h"
#include "solveur.h"


int main(int argc, char* argv[]){
	if (argc > 0) {
		cnf* formule = P_parse(argc, argv);
		if (S_initDPLL(formule)){
			printf("SAT\n"); 
		}
		else{
			printf("UNSAT\n");
		}
		

	}
}