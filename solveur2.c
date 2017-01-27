#include <stdlib.h>
#include <stdio.h>
#include <string.h>



typedef struct nodeLit {
	int val;
	struct nodeLit * nextLit;
} litteral;

typedef struct nodeClause {
	litteral* lit;
	struct nodeClause * nextClause;
} clause;

typedef struct CNF {
	clause* clse;
	int nblit;
	int nbclse;
} cnf;

void printCNF(cnf* formuleCNF){
	clause* currentClause = formuleCNF->clse;
	while(currentClause != NULL){
		printf("clause\n");
		litteral* currentLit = currentClause->lit;
		while(currentLit != NULL){
			printf("%d\n", currentLit->val);
			currentLit = currentLit->nextLit;
		}
		currentClause = currentClause->nextClause;
	}
	printf("fin\n");
}


/*
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
int solve(cnf* formuleCNF, int nvariables){
	int sat = 0;

	for (int i = 0; i < nvariables; ++i)
	{
		valueVars[i] = 0;
	}
	int retenue = 0;
	int sommeClauses = 0;

	while( retenue == 0){
		cnf* currentCNF = formuleCNF;

		while (currentCNF != NULL){
			int valueClausei = 0 ;
			clause* currentLit = currentCNF->clse;
			
			while(currentLit != NULL){
				int litteral = currentLit->litt;
				printf("%d\n", litteral );
				if (litteral < 0){
					valueClausei = valueClausei || ~(valueVars[-litteral]);
				}
				else {
					valueClausei = valueClausei || (valueVars[litteral-1]) ;
				}				
			}
			if (valueClausei == 1){
				sommeClauses++;
			}
		}
		if (sommeClauses == nclauses){
			sat = 1;
			break;
		}
		retenue = next_env(valueVars, nvariables);
	}
	if (sat){
		printf("SAT\n");
	}
	else {
		printf("UNSAT\n");
	}
	return 0;
}
*/

cnf* parse(int nbarg, char* args[]){
	cnf* formuleCNF;
	formuleCNF = malloc(sizeof(cnf));
	clause* currentClause;
	currentClause = malloc(sizeof(clause));
	formuleCNF->clse = currentClause;
	litteral* currentLit;
	currentLit = malloc(sizeof(litteral));
	currentClause->lit = currentLit;
	if (nbarg > 1){

		if (strcmp(args[1],"p") == 0){
			printf("P\n");

			if (nbarg>4){

				if (strcmp(args[2],"cnf") == 0){
					printf("CNF\n");
					formuleCNF->nblit = atoi(args[3]);
					formuleCNF->nbclse = atoi(args[4]);
					printf("%d litteraux et %d clauses\n",formuleCNF->nblit,formuleCNF->nbclse);

					for (int i = 5; i < nbarg; ++i){

						if (atoi(args[i]) == 0 && i != nbarg-1) {
							printf("plop %d\n", atoi(args[i]));
							currentClause->nextClause = malloc(sizeof(clause));
							currentClause = currentClause->nextClause;
							//free(currentLit);
							currentClause->lit = malloc(sizeof(litteral));
							currentLit = currentClause->lit;
						}

						else if (atoi(args[i]) != 0){
							if (currentLit->val){
								currentLit->nextLit = malloc(sizeof(litteral));
								currentLit = currentLit->nextLit;
							}	
							printf("plop2 %d\n", atoi(args[i]));
							currentLit->val = atoi(args[i]);
							printf("plop3\n");
						}
					}
				}
			}

			else {
				printf("Pas CNF\n");
			}

		}

		else if (strcmp(args[1],"c") == 0){
			printf("Commentaire\n");
		}
	}

	else {
		printf("Pas d'arguments\n");
	}
	printf("%lu\n",sizeof(formuleCNF) );
	return formuleCNF;
}

int main(int argc, char* argv[]){
	
	cnf* formule;
	formule = parse(argc, argv);
	//printf("%d\n",formule->clse->nextClause->litt );
	printCNF(formule);
	//solve(formule);
	/*
	cnf* formule;
	formule = malloc(sizeof(cnf));
	cnf* cformule;
	cformule = formule;
	cformule->clse = malloc(sizeof(clause));
	cformule->clse->litt = 3;
	printf("%d\n",cformule->clse->litt );
	*/
}