#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parseur.h"
#include "solveur.h"


int main(int argc, char* argv[]){
	if (argc > 0) {
		/*if (strcmp(argv[1], "-f") == 0){
//			int 
//			char** fileContent = P_readFile(argv[2]);

//			cnf* formule = P_parse(fileContent);
			char *file_contents;
			long input_file_size;
			FILE *input_file = fopen(argv[2], "rb");
			fseek(input_file, 0, SEEK_END);
			input_file_size = ftell(input_file);
			rewind(input_file);
			file_contents = malloc(input_file_size * (sizeof(char)));
			fread(file_contents, sizeof(char), input_file_size, input_file);
			fclose(input_file);
			printf("%s\n", file_contents);
			printf("%lu\n", input_file_size);
			cnf* formule  = P_parse(input_file_size, file_contents);
			printf("%d, %d\n", P_nlit(formule), P_nclse(formule) );
		}	
		
		else if (strcmp(argv[1], "-c") == 0){
			cnf* formule  = P_parse(argc, argv);
			printf("%d, %d\n", P_nlit(formule), P_nclse(formule) );
			//int isSat = S_naif(formule);

		}
	} */
		printf("%d\n", argc);
		cnf* formule = P_parse(argc, argv);
		printf("plap1\n");
		int isSat = S_DPLL(formule);
		printf("plap3\n");
		if (isSat){
			printf("SAT\n"); 
		}
		else{
			printf("UNSAT\n");
		}

	}
}