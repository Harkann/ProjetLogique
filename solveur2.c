#include <string.h>
#include <stdio.h>

struct nodeClause {
	int litt;
	struct nodeClause * nextClause;
} clause;

struct nodeCNF {
	nodeClause clause;
	struct nodeCNF * nextCNF;
} cnf;


void addclause(cnf * currentCNF, clause * currentClause){
	//on va au dernier élément de la liste (celui dont le next est NULL)
	cnf * current = currentCNF;
	while(current->nextCNF != NULL){
		current = current->nextCNF;
	}
	//on alloue de l'espace pour le next elément.
	current->nextCNF = malloc(sizeof(cnf));
	//on lui donne sa valeur
	current->nextCNF->clause = clause;
	current->nextCNF->nextCNF = NULL;
}

void addlitteral(clause * currentClause, int litteral){
	clause * current = currentClause;
	while(current->nextClause != NULL){
		current = current->nextClause;
	}
	current->nextClause = malloc(sizeof(clause));
	current->nextClause->litt = litteral;
	current->nextClause->nextClause = NULL;
}

// TODO
clause* parse(int nbarg, char* args[]){
	int nlitteraux ;
	int nclauses ;
	if (nbarg > 1){
		if (strcmp(args[1],"p") == 0){
			printf("P\n");
			if (nbarg>4){
				if (strcmp(args[2],"cnf") == 0){
					printf("CNF\n");
					nlitteraux = atoi(args[3]);
					nclauses = atoi(args[4]);
					clause tab_clauses[nclauses];
					printf("%d litteraux et %d clauses\n",nlitteraux,nclauses);
					for (int i = 5; i < nbarg; ++i)
					{
						if (atoi(args[i]) == 0) {
							printf("plop %d\n", atoi(args[i]));
							
						}
						else {
							printf("plop2 %d\n", atoi(args[i]));
							sizek++;
							printf("plop3\n");
							clausek_tmp = malloc((sizek-1)*sizeof(int));
							printf("plop3\n");
							for (int j = 0; j < sizek-2; ++j)
							{
								printf("plopboucle\n");
								clausek_tmp[j] = clausek[j];
							}
							printf("plop3\n");
							if (clausek != NULL){
								printf("plopfree\n");
								//free(clausek);
							}
							printf("plop3\n");
							clausek = malloc(sizek*sizeof(int));
							for (int j = 0; j < sizek-2; ++j)
							{
								clausek[j] = clausek_tmp[j];
							}
							printf("plop3\n");
							clausek[sizek-1] = atoi(args[i]);
							free(clausek_tmp);
						}
						
					}
					printf("%d\n",size_max);
				}
			}
			else {
				printf("Pas CNF");
			}

		}
		else if (strcmp(args[1],"c") == 0){
			printf("Commentaire");
		}
	}
	else {
		printf("Pas d'arguments");
	}
	return 0;
}