#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void next_env(char* tab_var, int nvariables){
	for (int i = 0; i < nvariables; ++i){

	}
}

int solve(char** tab_clauses, int nclauses, int nvariables){
	char* tab_var[nvariables];
	int sat = 0;
	for (int i = 0; i < 2**nvariables; ++i)
	{
	}




	if (sat){
		printf("SAT\n %s\n", tab_var);
	}
	else {
		printf("UNSAT\n");
	}
	return 0;
}






int main (int argc, char* argv[]){
	if (argc > 1){
		if (strcmp(argv[1],"p") == 0){
			if (argc>2 && strcmp(argv[2],"cnf") == 0){
				int nclauses = atoi(argv[3]);
				int nvariables = atoi(argv[4]);
				printf("%d clauses et %d variables\n",nclauses,nvariables);
				char** tab_clauses[nclauses];
				int iclause = 0;
				char* clause; 
				for (int i = 3; i < argc; ++i)
				{
					if (argv[i] != 0){
						char* new_clause;
						new_clause = malloc(strlen(clause)+2);
						strcpy(new_clause, clause);
						strcat(new_clause, argv[i]);
						clause = malloc(strlen(new_clause)+1);
						strcpy(clause, new_clause);
					}
					else if (i != argc-1){
						tab_clauses[iclause] = clause;
						free(clause);
					}
					else {
						tab_clauses[iclause] = clause;
					}
				}
			}
			else {
				printf("Pas CNF");
			}
		}
		else if (strcmp(argv[1],"c") == 0){
			printf("Commentaire");
		}
	}
	else {
		printf("Pas d'arguments");
	}


}