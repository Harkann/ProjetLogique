#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parseur.h"

int next_env(int* tab_var, int nvariables){
	int retenue = 1;
	for (int i = nvariables-1 ; i > -1 ; --i){
		if ((tab_var[i] + retenue) == 1){
			tab_var[i] = 1;
			retenue = 0;
		}
		else if ((tab_var[i] + retenue) == 2){
			tab_var[i] = 0;
			retenue = 1;
		}
		else {
			tab_var[i] = 0;
			retenue = 0;
		}
	}
	return retenue;
}

// Solveur naïf
int solve(cnf* formuleCNF, int* valueVars){
	int sat = 0;
	//valueVars = malloc(P_nlit(formuleCNF)*sizeof(int));
	for (int i = 0; i < P_nlit(formuleCNF); ++i)
	{
		valueVars[i] = 0;
	}
	int retenue = 0;
	int sommeClauses = 0;

	while( retenue == 0){
		printf("\n");
		for (int i = 0; i < P_nlit(formuleCNF); ++i)
		{
			printf("%d, ", valueVars[i]);
		}
		printf("\n");
		clause* currentClause = P_getclse(formuleCNF);
		sommeClauses = 0;
		while (currentClause != NULL){
			int valueClausei = 0 ;
			litteral* currentLit = P_getlit(currentClause);
			
			while(currentLit != NULL){
				int litteral = P_getval(currentLit);
				printf("%d\n", litteral );
				if (litteral < 0){
					valueClausei = (valueClausei || !(valueVars[-litteral-1]));
				}
				else {
					valueClausei = (valueClausei || (valueVars[litteral-1])) ;
				}
				currentLit = P_nextlit(currentLit);			
			}
			if (valueClausei == 1){
				sommeClauses++;
			}
			currentClause = P_nextclse(currentClause);
		}
		if (sommeClauses == P_nclse(formuleCNF)){
			sat = 1;
			break;
		}
		retenue = next_env(valueVars, P_nlit(formuleCNF));

	}
	if (sat){
		return 0;
	}
	else {
		free(valueVars);
		return 1;
	}
}


int main(int argc, char* argv[]){
	cnf* formule;
	int* res;
	formule = P_parse(argc, argv);
	res = malloc(P_nlit(formule)*sizeof(int));
	int isSat = solve(formule, res);
	if (isSat == 0){
		printf("SAT\n"); 
		for (int i = 0; i < P_nlit(formule); ++i)
		{
			printf("%d, ", res[i]);
		}
	}
	else{
		printf("UNSAT\n");
	}
}