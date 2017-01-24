#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// on doit forcément spécifier n ? 
// uttiliser calloc plutot que malloc ?
// 
// retirer éléments à la fin du tableau (réduire ) -> realloc

//Renvoie la valeur binaire incrémentée de 1
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
int solve(int n, int(*tab_clauses)[n] , int nclauses, int nvariables, int valueVars[nvariables]){
	int sat = 0;
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
int DPLL(int n, int(*tab_clauses)[n], int nclauses, int nvariables){
	int valueVars[nvariables];
	int appVars[nvariables][2];
	for (int i = 0; i < nvariables; ++i)
	{
		valueVars[i] = 0;
		appVars[i][0] = 0;
		appVars[i][1] = 0;
	}
	for (int i = 0; i < nvariables; i++){
		if (sizeof(tab_clauses[i]) == 0){
			printf("clause %d vide\n",i);
			printf("UNSAT\n");
			return 0;
		}
		else if (sizeof(tab_clauses)/sizeof(int) == 1){
			valueVars[i] = 2;
		}
		else{
			for (int j = 0; j < sizeof(tab_clauses[i])/sizeof(int); ++j){
				if (tab_clauses[i][j] < 0)
				{
					appVars[(tab_clauses[i][j])][1] = 1;
				}
				else if (tab_clauses[i][j] > 0){
					appVars[tab_clauses[i][j]][1] = 1;
				}
			}
		}
	}
	int sautElem = 0;
	for (int i = 0; i < nvariables; i++){
		for (int j = 0; j < sizeof(tab_clauses[i])/sizeof(int); ++j){
			{
				if ((appVars[tab_clauses[i][j]][1] == 1 && appVars[tab_clauses[i][j]][1] == 0) || (appVars[tab_clauses[i][j]][1] == 0 && appVars[tab_clauses[i][j]][1] == 1)){
					sautElem++;

				}
				if (j != sizeof(tab_clauses[i])/sizeof(int)-sautElem-1){
						*tab_clauses[j] = *tab_clauses[j+sautElem];
					}
				// réduire la taille du tableau de sautElem
			}
		}
	}
	solve(n, tab_clauses, nclauses, nvariables, valueVars);
	return 0;
}	

int parse(int** clauses, int nbarg, char* args[]){
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
					clauses = malloc(nclauses);
					printf("%d litteraux et %d clauses\n",nlitteraux,nclauses);
					int * clausek_tmp = NULL;
					int * clausek = NULL;
					int k = 0;
					int size_max = 0;
					int sizek = 0;
					for (int i = 5; i < nbarg; ++i)
					{
						if (atoi(args[i]) == 0) {
							printf("plop %d\n", atoi(args[i]));
							clauses[k] = clausek;
							k++;
							//free(clausek);
							clausek = NULL;
							if (sizek > size_max){
								size_max = sizek;
							}
							sizek = 0;
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




int main (int argc, char* argv[]){
	//int cnf[][2] = {{1, 1}};
	//int n = 2;
	//solve(n, cnf, 1, 1);
	int** argparsed;
	parse(argparsed, argc, argv);
	printf("plap %lu\n",sizeof(argparsed));
	for (int i = 0; i < sizeof(argparsed)/sizeof(int); ++i)
	{
		//printf("plop %d\n",argparsed[i]);
		printf("plup %lu\n",sizeof(argparsed[i]));
		printf("argi %d\n", argparsed[i][0] );
		/*for (int j = 0; j < sizeof(argparsed[i])/sizeof(int); ++j){
			printf("%d\n",argparsed[i][j] );
		}*/
	}
	return 0;



}

