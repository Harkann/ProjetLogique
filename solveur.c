#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parseur.h"
#include "solveur.h"

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
int S_naif(cnf* formuleCNF, int* valueVars){
	int sat = 0;
	for (int i = 0; i < P_nlit(formuleCNF); ++i)
	{
		valueVars[i] = 0;
	}
	int retenue = 0;
	int sommeClauses = 0;
	clause* currentClause;
	printf("plip1\n");
	while( retenue == 0){
		if (formuleCNF != NULL){
			currentClause = P_getclse(formuleCNF);
			printf("plip2\n");
		}
		else {
			printf("plip3\n");
			return 0;
		}
		sommeClauses = 0;
		
		while (currentClause != NULL){
			printf("plip4\n");
			int valueClausei = 0 ;
			litteral* currentLit = P_getlit(currentClause);
			printf("plip4.5\n");
			while(currentLit != NULL){
				printf("plip5\n");
				int litteral = P_getval(currentLit);
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
		printf("plip6, somme %d\n", sommeClauses);
		if (sommeClauses == P_nclse(formuleCNF)){
			sat = 1;
			printf("plip6.5, sat %d\n", sat);
			break;
		}
		printf("plip7\n");
		retenue = next_env(valueVars, P_nlit(formuleCNF));
	}
	if (sat){
		return 1;
	}
	else {
		free(valueVars);
		return 0;
	}
}


//nextenv pour DPLL
int next_envD(int* tab_var, int nvariables){
	int retenue = 1;
	for (int i = nvariables-1 ; i > -1 ; --i){
		if (tab_var[i] == 2);
		else if ((tab_var[i] + retenue) == 1){
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

//Solveur DPLL
int S_DPLL(cnf* formuleCNF){//, int* valueVars){
	char appVars[P_nlit(formuleCNF)][2];
	int *valueVars = malloc(P_nlit(formuleCNF)*sizeof(int));
	for (int i = 0; i < P_nlit(formuleCNF); ++i)
	{
		valueVars[i] = 0;
		// le litteral est au moins uen fois negatif si [0] = 1
		appVars[i][0] = 0;
		// le litteral est au moins une fois positif si [1] =1
		appVars[i][1] = 0;
	}
	clause* currentClause = P_getclse(formuleCNF);
	litteral* currentLit = P_getlit(currentClause);
	while (currentClause != NULL){
		currentLit = P_getlit(currentClause);
		if (P_getval(currentLit) == 0){
			printf("clause vide\n");
			printf("UNSAT\n");
			return 1;
		}
		else if (P_nextlit(currentLit) == NULL){
			printf("plop1\n");
			if (P_getval(currentLit) > 0){
				valueVars[P_getval(currentLit)-1] = 2;
			}
			else{
				valueVars[-P_getval(currentLit)-1] = 2;
			}
		}
		else{
			printf("plop2\n");
			while (currentLit != NULL){
				printf("plop3\n");
				if (P_getval(currentLit) < 0)
				{
					appVars[-P_getval(currentLit)-1][0] = 1;
				}
				else if (P_getval(currentLit) > 0){
					appVars[P_getval(currentLit)-1][1] = 1;
				}
				printf("plop4 %d\n", P_getval(currentLit));
				currentLit = P_nextlit(currentLit);
				printf("plop5\n");
			}
		}
		currentClause = P_nextclse(currentClause);
		printf("plop6\n");
	}
	printf("plop6.5\n");
	currentClause = P_getclse(formuleCNF);
	printf("plop7\n");
	while (currentClause != NULL){
		currentLit = P_getlit(currentClause);
		printf("plop8\n");
		while (currentLit != NULL){
			{
				if (appVars[abs(P_getval(currentLit))][0]+appVars[abs(P_getval(currentLit))][1] == 1){
					P_remclse(formuleCNF, currentClause);
				}
				currentLit = P_nextlit(currentLit);
				printf("plop9\n");
			}
			if (currentClause != NULL){
				currentClause = P_nextclse(currentClause);
				if (currentClause != NULL){
					currentLit = P_getlit(currentClause);
				}
			}
			printf("plop10\n");
		}
	}
	int isSat = S_naif(formuleCNF, valueVars);
	printf("plop11, isSat %d\n",isSat );
	return isSat;
}
