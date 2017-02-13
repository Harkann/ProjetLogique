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

void P_copyCNF(cnf* from, cnf* to){
	if (from == NULL || to == NULL){
		perror("Empty cnf");
		return;
	}
	to->nblit = from->nblit;
	to->nbclse = from->nbclse;
	clause* fromClause = from->clse;
	clause* toClause = malloc(sizeof(clause));
	to->clse = toClause;
	if (fromClause->lit == NULL){
		toClause->lit = NULL;
	}
	litteral* fromLit = fromClause->lit;
	litteral* toLit = malloc(sizeof(litteral));
	toClause->lit = toLit;
	toLit->val = fromLit->val;
	litteral* litt = toLit;
	fromLit = fromLit->nextLit;
	while (fromLit != NULL){
		litt->nextLit = malloc(sizeof(litteral));
		litt = litt->nextLit;
		litt->val = fromLit->val;
		fromLit = fromLit->nextLit;
	}
	litt->nextLit = NULL;
	clause* claus = toClause;
	fromClause = fromClause->nextClause;
	while(fromClause != NULL)
    {
      claus->nextClause = malloc(sizeof(clause));
      claus = claus->nextClause;
      //p->c = fsrc->c;
      if(fromClause->lit == NULL) toClause->lit = NULL;
      fromLit = toClause->lit;
      toLit = malloc(sizeof(litteral));
      claus->lit = toLit;
      toLit->val = fromLit->val;
      litt = toLit;
      fromLit = fromLit->nextLit;	
      while(fromLit != NULL)
        {
          litt->nextLit = malloc(sizeof(litteral));
          litt = litt->nextLit;
          litt->val = fromLit->val;
          fromLit = fromLit->nextLit;
        }
      litt->nextLit = NULL;
      fromClause = fromClause->nextClause;
    }
  claus->nextClause = NULL;
}

void P_setnclse(cnf* formuleCNF, int nclses){
	formuleCNF->nbclse = nclses;
}

void P_setClseForm(cnf* formuleCNF, clause* setClause){
	formuleCNF->clse = setClause;
}
void P_setClseClse(clause* currentClause, clause* setClause){
	currentClause->nextClause = setClause;
}
void P_setLitClse(clause* currentClause, litteral* setLit){
	currentClause->lit = setLit;
}
void P_setLitLit(litteral* currentLit, litteral* setLit){
	currentLit->nextLit = setLit;
}

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
					//printf("count %d, nbarg %d\n",count, nbarg );
				}
			}

			else {
				printf("Pas CNF\n");
			}

		}

		else if (strcmp(args[count],"c") == 0){
		}
		else {
			//printf("%s\n",args[count]);
		}
	}
	return formuleCNF;
}