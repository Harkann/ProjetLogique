#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parseur.h"
#include "solveur.h"

int next_env(int* tab_var, int nvariables){
	int retenue = 1;
	for (int i = nvariables-1 ; i > -1 ; --i){
		if (tab_var[i] != 2){
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
			printf("%d",tab_var[i]);
		}
	}
	printf("\n");
	return retenue;
}

// Solveur naïf
int S_naif(cnf* formuleCNF, int* valueVars){
	int sat = 0;
	int retenue = 0;
	int sommeClauses = 0;
	clause* currentClause;
	printf("plip1\n");
	while( retenue == 0){
		if (formuleCNF != NULL){
			currentClause = P_getclse(formuleCNF);
//			printf("plip2\n");
		}
		else {
			printf("plip3\n");
			return 0;
		}
		sommeClauses = 0;
		
		while (currentClause != NULL){
			//printf("plip4\n");
			int valueClausei = 0 ;
			litteral* currentLit = P_getlit(currentClause);
			//printf("plip4.5\n");
			while(currentLit != NULL){
			//	printf("plip5\n");
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
		retenue = next_env(valueVars, P_nlit(formuleCNF));
		printf("plip7\n");
	}
	return sat;
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

//Check si la clause est vide.
int isEmpty(clause* currentClause){
	printf("\t isEmptyStart\n");
	if (P_getval(P_getlit(currentClause)) == 0){
		printf("\t isEmptyEnd\n");
		return 1;
	}
	else {
		printf("\t isNOTEmptyEnd\n");
		return 0;
	}
}

//initialise les valeurs des litteraux à 0.
int* setVarsDPLL(char(*appVars)[2], cnf* formuleCNF){
	printf("\t setVarsDPLLStart\n");
	int* valueVars = malloc(P_nlit(formuleCNF)*sizeof(int));
	for (int i = 0; i < P_nlit(formuleCNF); ++i)
	{
		valueVars[i] = 0;
		// le litteral est au moins une fois negatif si [0] = 1
		appVars[i][0] = 0;
		// le litteral est au moins une fois positif si [1] =1
		appVars[i][1] = 0;
	}
	printf("\t setVarsDPLLEnd\n");
	return valueVars;
}

//Check si le litteral est seul dans la clause.
void isAlone(int * valueVars, litteral* currentLit){
	printf("\t isAloneStart\n");
	if (P_getval(currentLit) > 0){
		valueVars[P_getval(currentLit)-1] = 2;
	}
	else{
		valueVars[-P_getval(currentLit)-1] = 2;
	}
	printf("\t isAloneEnd\n");
}

//Check if the litteral apparait positivement ou négativement.
void isPosNeg(char(*appVars)[2], litteral* currentLit){
	printf("\t isPosNegStart\n");
	while (currentLit != NULL){

		if (P_getval(currentLit) < 0)
		{
			printf("\t \tnegatif\n");
			appVars[abs(P_getval(currentLit))-1][0] = 1;
		}
		else if (P_getval(currentLit) > 0){
			printf("\t \tpositif\n");
			appVars[P_getval(currentLit)-1][1] = 1;
		}
		printf("\t \t Litteral : %d\n", P_getval(currentLit));
		currentLit = P_nextlit(currentLit);
	}
	printf("\t isPosNegEnd\n");
}


//Solveur DPLL
int S_DPLL(cnf* formuleCNF){
	char appVars[P_nlit(formuleCNF)][2];
	int* valueVars = setVarsDPLL(appVars, formuleCNF);
	clause* currentClause = P_getclse(formuleCNF);
	litteral* currentLit = P_getlit(currentClause);
	
	while (currentClause != NULL){
		printf("Check Clause\n");
		if (isEmpty(currentClause)) {
			return 1;
		}
		
		else if (P_nextlit(currentLit) == NULL){
			isAlone(valueVars, currentLit);
		}

		else{
			isPosNeg(appVars, currentLit);
		}
		currentClause = P_nextclse(currentClause);
		if (currentClause != NULL){
			currentLit = P_getlit(currentClause);
		}
	}

	currentClause = P_getclse(formuleCNF);
	while (currentClause != NULL && P_nclse(formuleCNF)){
		printf("%d\n", P_nclse(formuleCNF));
		printf("Check SupressionClause\n");
		currentLit = P_getlit(currentClause);

		while (currentLit != NULL && P_nclse(formuleCNF)){
			printf("\t Litteral %d\n", P_getval(currentLit));
			printf("appVars : %d, %d\n", appVars[abs(P_getval(currentLit))-1][0], appVars[abs(P_getval(currentLit))-1][1]);
			printf("%d\n", P_nclse(formuleCNF));
			if (appVars[abs(P_getval(currentLit))-1][0]+appVars[abs(P_getval(currentLit))-1][1] == 1){
				printf("\t SupressionStart\n");
				P_remclse(formuleCNF, currentClause);
				printf("\t SupressionEnd\n");
				break;
			}

			if (currentLit != NULL){
				if (P_nextlit(currentLit) != NULL)
				printf("\t NextLit\n");
				currentLit = P_nextlit(currentLit);
			}
		}
		if (currentClause != NULL && P_nclse(formuleCNF)){
			printf("\t NextClause\n");
			currentClause = P_nextclse(currentClause);
			if (currentClause != NULL){
				printf("\t NextLitClause\n");
				currentLit = P_getlit(currentClause);
			}

			else{
				break;
			}
		}
		printf("Check SupressionEnd\n");
		
	}
	int isSat = S_naif(formuleCNF, valueVars);
	printf("SAT ? %d\n",isSat );
	return isSat;
}
