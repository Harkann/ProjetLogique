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

//Check si la clause est vide.
int isEmpty(clause* currentClause, int* valueVars){
	litteral* currentLit = P_getlit(currentClause);
	printf("\t isEmptyStart\n");
	int valueClausei = 0;
	while(currentLit){
			int litteral = P_getval(currentLit);
			printf("\t \t litteral %d\n", litteral);
			if (litteral < 0){
				if (-(valueVars[-litteral-1]) >= 0){
					return 0;
				}
			}
			else {
				if (valueVars[-litteral-1] >= 0 ){
					return 0;
				}
			}
			currentLit = P_nextlit(currentLit);			
			printf("valueClausei, %d\n", valueClausei);
		}
	return 1;
}

//initialise les valeurs des litteraux à 0.
int* setVarsDPLL(cnf* formuleCNF){
	printf("\t setVarsDPLLStart\n");
	int* valueVars = malloc(P_nlit(formuleCNF)*sizeof(int));
	for (int i = 0; i < P_nlit(formuleCNF); ++i)
	{
		valueVars[i] = 0;
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

//Check si le litteral apparait positivement ou négativement.
void isPosNeg(char(*appVars)[2], clause* currentClause){
	litteral* currentLit = P_getlit(currentClause);
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

//Check si il y a une clause est vide.
int CheckIfEmpty(cnf* formuleCNF, int* valueVars){
	clause* currentClause = P_getclse(formuleCNF);
	printf("\t isEmptyStart\n");
	while (currentClause != NULL){
		printf("Check Clause\n");
		if (isEmpty(currentClause, valueVars)) {
			printf("La clause est vide\n");
			return 1;
		}
		currentClause = P_nextclse(currentClause);
	}
	return 0;
}
//check si il y a un litteral pur
int isLitPure(cnf* formuleCNF, int* valueVars){ 
	printf("begin isLitPure\n");
	clause* currentClause = P_getclse(formuleCNF);
	char appVars[P_nlit(formuleCNF)][2];
	while (currentClause){
		isPosNeg(appVars, currentClause);
		currentClause = P_nextclse(currentClause);
	}
	for (int i = 0; i < P_nlit(formuleCNF); ++i)
	{
		if(appVars[i][0]+appVars[i][1] == 1){
			return i;
		}
	}
	return 0;
}

int isUnit(cnf* formuleCNF,int* valueVars){
	return 0;
}

int selectLit(cnf* formuleCNF, int* valueVars){
	printf("selectLit\n");
	for (int i = 0; i < P_nlit(formuleCNF); ++i)
	{
		printf("%d", valueVars[i]);
		if (valueVars[i] == 0){
			return i;
		}
	}
	printf("\n");
	return -1;
}

int isSat(cnf* formuleCNF, int* valueVars){
	printf("begin isSat\n");
	clause* currentClause;
	if (formuleCNF != NULL){
		currentClause = P_getclse(formuleCNF);
	}
	else {
		return 1;
	}
	int sommeClauses = 0;

	while (currentClause != NULL){
		int valueClausei = 0 ;
		litteral* currentLit = P_getlit(currentClause);
		while(currentLit != NULL){
			int litteral = P_getval(currentLit);
			printf("\t \t litteral %d\n", litteral);
			if (litteral < 0){
				if (-(valueVars[-litteral-1]) > 1){
					valueClausei = 1;
				}
			}
			else {
				if (valueVars[-litteral-1] > 1){
					valueClausei = 1;
				}
			}
			currentLit = P_nextlit(currentLit);			
			printf("valueClausei, %d\n", valueClausei);
		}
		if (valueClausei == 1){
			sommeClauses++;
		}
		currentClause = P_nextclse(currentClause);
	}
	printf("sommeClauses, %d\n", sommeClauses );
	if (sommeClauses == P_nclse(formuleCNF)){
		return 1;
	}
	else {
		return 0;
	}
}

void printVal(cnf* formuleCNF, int* valueVars){
	for (int i = 0; i < P_nlit(formuleCNF); ++i)
	{
		printf("%d",valueVars[i]);
	}
	printf("\n");
}

//Solveur DPLL
int DPLL(cnf* formuleCNF, int* valueVars){
	int l;
	if (isSat(formuleCNF, valueVars)) { //si la formule est vide
		return 1;
	}
	else if (CheckIfEmpty(formuleCNF, valueVars)){ //si il y a une clause vide
		return 0;
	}
	else if ((l = isLitPure(formuleCNF,valueVars))){ // un litteral pur l -> l=true
		printf("begin PURE\n");
		valueVars[l] = 1;
		return DPLL(formuleCNF,valueVars);
	}
	else if ((l = isUnit(formuleCNF,valueVars))){ // une clause unitaire [l] -> l=true
		printf("begin UNIT\n");
		valueVars[l] = 1;
		return DPLL(formuleCNF, valueVars);
	}	
	else {
		printf("begin SELECTION\n");
		l = selectLit(formuleCNF,valueVars);// on choisi un l dans F
		printf("l SELECTION : %d\n", l);
		if (l == -1){
			printf("ERREUR SELECTION LITTERAL\n");
			return 0;
		}  
		valueVars[l] = 1; 
		printVal(formuleCNF, valueVars);
		if (DPLL(formuleCNF, valueVars)){ //l=true
			return 1;
		}
		else { // on set l=false
			printf("mauvaise SELECTION\n");
			valueVars[l] = -1;
			return DPLL(formuleCNF, valueVars);
		}
	}
}


//permet d'initialiser les valueVars
int S_initDPLL(cnf* formuleCNF){ 
	int* valueVars = setVarsDPLL(formuleCNF);
	return DPLL(formuleCNF, valueVars);
}