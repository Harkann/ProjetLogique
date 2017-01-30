#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parseur.h"

void P_printCNF(cnf* formuleCNF){
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

int P_nlit(cnf* formuleCNF){
	return formuleCNF->nblit;
}

int P_nclse(cnf* formuleCNF){
	return formuleCNF->nbclse;
}

clause* P_getclse(cnf* formuleCNF){
	return formuleCNF->clse;
}

clause* P_nextclse(clause* clauseCNF){
	return clauseCNF->nextClause;
}

litteral* P_getlit(clause* clauseCNF){
	return clauseCNF->lit;
}

litteral* P_nextlit(litteral* litteralCNF){
	return litteralCNF->nextLit;
}

int P_getval(litteral* litteralCNF){
	return litteralCNF->val;
}

void P_remclse(cnf* formuleCNF, clause* remClause){
	clause* currentClause = formuleCNF->clse;
	clause* previousClause;
	while (currentClause != NULL){
		if (currentClause == remClause){
			previousClause->nextClause = currentClause->nextClause;
			formuleCNF->nbclse --; 
			free(currentClause);
		}
		previousClause = currentClause;
		currentClause = P_nextclse(currentClause);
	}
}




/*
cnf* P_parse(int nbarg, char* args[]){
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
			//printf("P\n");

			if (nbarg>5){

				if (strcmp(args[2],"cnf") == 0){
					//printf("CNF\n");
					formuleCNF->nblit = atoi(args[3]);
					formuleCNF->nbclse = atoi(args[4]);
					//printf("%d litteraux et %d clauses\n",formuleCNF->nblit,formuleCNF->nbclse);

					for (int i = 5; i < nbarg; ++i){

						if (atoi(args[i]) == 0 && i != nbarg-1) {
							currentClause->nextClause = malloc(sizeof(clause));
							currentClause = currentClause->nextClause;
							currentClause->lit = malloc(sizeof(litteral));
							currentLit = currentClause->lit;
						}

						else if (atoi(args[i]) != 0){
							if (currentLit->val){
								currentLit->nextLit = malloc(sizeof(litteral));
								currentLit = currentLit->nextLit;
							}	
							currentLit->val = atoi(args[i]);
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
	return formuleCNF;
}
*/
cnf* P_parse(int nbarg, char* args[]){
	cnf* formuleCNF;
	formuleCNF = malloc(sizeof(cnf));
	clause* currentClause;
	currentClause = malloc(sizeof(clause));
	formuleCNF->clse = currentClause;
	litteral* currentLit;
	currentLit = malloc(sizeof(litteral));
	currentClause->lit = currentLit;
	int newCount = 0;
	for (int count = 0; count<nbarg; count++){

		if (strcmp(args[count],"p") == 0){
			//printf("P\n");

			if (nbarg-count>5){

				if (strcmp(args[count+1],"cnf") == 0){
					//printf("CNF\n");
					formuleCNF->nblit = atoi(args[count+2]);
					formuleCNF->nbclse = atoi(args[count+3]);
					//printf("%d litteraux et %d clauses\n",formuleCNF->nblit,formuleCNF->nbclse);

					for (int i = count+4; i < nbarg; ++i){

						if (atoi(args[i]) == 0 && i != nbarg-1) {
							currentClause->nextClause = malloc(sizeof(clause));
							currentClause = currentClause->nextClause;
							currentClause->lit = malloc(sizeof(litteral));
							currentLit = currentClause->lit;
						}

						else if (atoi(args[i]) != 0){
							if (currentLit->val){
								currentLit->nextLit = malloc(sizeof(litteral));
								currentLit = currentLit->nextLit;
							}	
							currentLit->val = atoi(args[i]);
						}
						newCount = count+i;
					}
					count = newCount;
					printf("count %d, nbarg %d\n",count, nbarg );
				}
			}

			else {
				printf("Pas CNF\n");
			}

		}

		else if (strcmp(args[count],"c") == 0){
			printf("Commentaire\n");
		}
		else {
			printf("Pas d'arguments\n");
		}
	}
	return formuleCNF;
}