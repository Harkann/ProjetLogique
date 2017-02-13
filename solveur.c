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
		}
		else {
			printf("plip3\n");
			return 0;
		}
		sommeClauses = 0;
		
		while (currentClause != NULL){
			int valueClausei = 0 ;
			litteral* currentLit = P_getlit(currentClause);
			while(currentLit != NULL){
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

//initialise les valeurs des litteraux à 0.
int* setVarsDPLL(cnf* formuleCNF){
	int* valueVars = malloc(P_nlit(formuleCNF)*sizeof(int));
	for (int i = 0; i < P_nlit(formuleCNF); ++i)
	{
		valueVars[i] = 0;
	}
	return valueVars;
}

//Check si il y a une clause est vide.
int CheckIfEmpty(cnf* formuleCNF, int* valueVars){
	clause* currentClause = P_getclse(formuleCNF);
	while (currentClause != NULL){
		if (P_getlit(currentClause) == NULL) {
			return 1;
		}
		currentClause = P_nextclse(currentClause);
	}
	return 0;
}

int isPureorUnit(cnf* formuleCNF, int* valueVars){
	clause* currentClause = P_getclse(formuleCNF);
	char appVars[P_nlit(formuleCNF)][2];
	for (int i = 0; i < P_nlit(formuleCNF); ++i)
	{
		appVars[i][0] = 0;
		appVars[i][1] = 0;
	}
	int l;
	int tailleClause = 0;
	while (currentClause != NULL){
		litteral* currentLit = P_getlit(currentClause);
		while (currentLit != NULL){
			if (P_getval(currentLit) < 0){
				appVars[abs(P_getval(currentLit))-1][0] = 1;
			}
			else if (P_getval(currentLit) > 0){
				appVars[P_getval(currentLit)-1][1] = 1;
			}
			currentLit = P_nextlit(currentLit);
			tailleClause ++;
		}

		if (tailleClause == 1){
			l = P_getval(P_getlit(currentClause));
			if (valueVars[abs(l)-1] == 0){
				return l;
			}
		}
		currentClause = P_nextclse(currentClause);
	}
	for (int i = 0; i < P_nlit(formuleCNF); ++i)
	{
		if(appVars[i][0]==1 && appVars[i][1] == 0){
			return -(i+1);
		}
		else if (appVars[i][0]==0 && appVars[i][1] == 1){
			return (i+1);
		}
	}
	return 0;
}

void printVal(cnf* formuleCNF, int* valueVars){
	for (int i = 0; i < P_nlit(formuleCNF); ++i)
	{
		printf("%d",valueVars[i]);
	}
	printf("\n");
}

int selectLit(cnf* formuleCNF, int* valueVars){
	int selected = -1;
	for (int i = 0; i < P_nlit(formuleCNF); ++i)
	{
		if (valueVars[i] == 0){
			printf("selected %d\n",i );
			selected =  i;
			break;
		}
	}
	return selected;
}

int isSat(cnf* formuleCNF, int* valueVars){
	printf("FisSat\n");
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
			if (litteral < 0){
				if (-(valueVars[-litteral-1]) >= 1){
					valueClausei = 1;
				}
			}
			else {
				if (valueVars[litteral-1] >= 1){
					valueClausei = 1;
				}
			}
			currentLit = P_nextlit(currentLit);			
		}
		if (valueClausei == 1){
			sommeClauses++;
		}
		currentClause = P_nextclse(currentClause);
	}
	if (sommeClauses == P_nclse(formuleCNF)){
		return 1;
	}
	else {
		return 0;
	}
}

void simplification(cnf* formuleCNF, int* valueVars){
	printf("Simplify\n");
	clause* currentClause = P_getclse(formuleCNF);
	clause* precedClause = currentClause;
	int skipC;
	int skipL;
	while (currentClause != NULL){
		litteral* currentLit = P_getlit(currentClause);
		litteral* precedLit = currentLit;
		skipC = 0;
		while (currentLit != NULL){
			skipL = 0;
			if (P_getval(currentLit) > 0 && valueVars[P_getval(currentLit)-1] == 1){
				printf("delete clause\n");
				if (currentClause == precedClause){
					P_setClseForm(formuleCNF, P_nextclse(currentClause));
					currentClause = P_getclse(formuleCNF);
					precedClause = currentClause;
				}
				else{
					P_setClseClse(precedClause, P_nextclse(currentClause));
					currentClause = P_nextclse(precedClause);
				}
				P_setnclse(formuleCNF, P_nclse(formuleCNF)-1);
				skipC = 1;
				break;
			}
			else if (P_getval(currentLit) < 0 && valueVars[-P_getval(currentLit)-1] == -1){
				printf("delete clause\n");
				if (currentClause == precedClause){
					P_setClseForm(formuleCNF, P_nextclse(currentClause));
					currentClause = P_getclse(formuleCNF);
					precedClause = currentClause;
				}
				else{
					P_setClseClse(precedClause, P_nextclse(currentClause));
					currentClause = P_nextclse(precedClause);
				}
				P_setnclse(formuleCNF, P_nclse(formuleCNF)-1);
				skipC = 1;
				break;
			}
			if (P_getval(currentLit) > 0 && valueVars[P_getval(currentLit)-1] == -1){
				printf("delete lit\n");
				if (currentLit == precedLit){
					P_setLitClse(currentClause, P_nextlit(currentLit));
					currentLit = P_getlit(currentClause);
					precedLit = currentLit;
					skipL = 1;
				}
				else{
					P_setLitLit(precedLit, P_nextlit(currentLit));
					currentLit = P_nextlit(precedLit);
				}
				
			}
			else if (P_getval(currentLit) < 0 && valueVars[-P_getval(currentLit)-1] == 1){
				printf("delete lit\n");
				if (currentLit == precedLit){
					P_setLitClse(currentClause, P_nextlit(currentLit));
					currentLit = P_getlit(currentClause);
					precedLit = currentLit;
					skipL = 1;
				}
				else{
					P_setLitLit(precedLit, P_nextlit(currentLit));
					currentLit = P_nextlit(precedLit);
				}
				
			}
			precedLit = currentLit;
			if (!skipL){
				if (currentLit != NULL){
					currentLit = P_nextlit(currentLit);
				}
			}
			
		}
		if (!skipC){
			precedClause = currentClause;
			currentClause = P_nextclse(currentClause);
		}
	}
}
//Solveur DPLL
int DPLL(cnf* formuleCNF, int* valueVars){
	int l;
	if (P_getclse(formuleCNF) == NULL){//si formule vide alors satisfiable
		printf("formule vide\n");
		return 1;
	}
	else if (CheckIfEmpty(formuleCNF, valueVars)){ //si il y a une clause vide
		printf("EmptyClause\n");
		return 0;
	}
	else if ((l = isPureorUnit(formuleCNF,valueVars))){ // un litteral pur l -> l=true
		printf("isLitPure\n");
		if (l> 0){
			valueVars[l-1] = 1;
		}
		else{
			valueVars[-l-1] = -1;
		}
		simplification(formuleCNF, valueVars);
		return DPLL(formuleCNF,valueVars);
	}
	else {
		l = selectLit(formuleCNF,valueVars);// on choisi un l dans F
		if (l == -1){
			printf("invalid\n");
			printVal(formuleCNF, valueVars);
			return 0;
		} 
		// on copie la formule et les valeurs pour tester les deux solutions.
		
		int* valueVarsBis = malloc(P_nlit(formuleCNF)*sizeof(int));
		for(int i=0 ; i<P_nlit(formuleCNF) ; i++) {
			valueVarsBis[i] = valueVars[i];
		}
		cnf* formuleCNFBis = malloc(sizeof(cnf)); 
		P_copyCNF(formuleCNF, formuleCNFBis);
		valueVars[l] = 1;
		valueVarsBis[l] = -1;
		simplification(formuleCNF, valueVars);
		printVal(formuleCNF, valueVars);
		if (DPLL(formuleCNF, valueVars)){ //l=true
			return 1;
		}
		else { // on set l=false
			printf("BAD GUESS\n");
			simplification(formuleCNFBis, valueVarsBis);
			printVal(formuleCNFBis, valueVarsBis);
			return DPLL(formuleCNFBis, valueVarsBis);
		}
	}
}


//permet d'initialiser les valueVars
int S_initDPLL(cnf* formuleCNF){ 
	int* valueVars = setVarsDPLL(formuleCNF);
	if (DPLL(formuleCNF, valueVars)){
		FILE *f;
		f = fopen("cnf.solved", "w");
		fprintf(f, "SAT\n");
		for (int i = 0; i < P_nlit(formuleCNF); ++i)
		{
			fprintf(f,"%d",valueVars[i]);
		}
		fprintf(f,"\n");
		fclose(f);
		return 1;
	}
	else {
		FILE *f;
		f = fopen("cnf.solved", "w");
		fprintf(f, "UNSAT\n");
		fclose(f);
		return 0;
	}
}