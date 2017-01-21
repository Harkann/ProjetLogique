#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

int solve(int n, int(*tab_clauses)[n] , int nclauses, int nvariables){
	int sat = 0;
	int valueVars[nvariables];
	for (int i = 0; i < nvariables; ++i)
	{
		valueVars[i] = 0;
	}
	int retenue = 0;
	int sommeClauses = 0;
	while( retenue == 0){
		for (int i = 0; i < nclauses; ++i)
		{
			int valueClausei = 0 ;
			for (int j = 0; j < sizeof(tab_clauses[i])/sizeof(int); ++j)
			{

				int litteral = tab_clauses[i][j];
				printf("%d\n", litteral );

				if (tab_clauses[i][j] < 0){
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

int parse(int nbarg, char* args[]){
	int nlitteraux ;
	int nclauses ;
	//int* clauses = NULL;
	if (nbarg > 1){
		if (strcmp(args[1],"p") == 0){
			if (nbarg>4){
				if (strcmp(args[2],"cnf") == 0){
					nlitteraux = atoi(args[3]);
					nclauses = atoi(args[4]);
					//clauses = malloc(nclauses * sizeof(int));
					printf("%d litteraux et %d clauses\n",nlitteraux,nclauses);
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




int main (int argc, char* argv[]){
	int cnf[][2] = {{1, 1}};
	int n = 2;
	solve(n, cnf, 1, 1);
	return 0;
	


}