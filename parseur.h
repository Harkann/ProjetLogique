#ifndef PARSEUR_H
#define PARSEUR_H


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

extern int P_nlit(cnf* formuleCNF);

extern int P_nclse(cnf* formuleCNF);

extern clause* P_getclse(cnf* formuleCNF);

extern clause* P_nextclse(clause* clauseCNF);

extern litteral* P_getlit(clause* clauseCNF);

extern litteral* P_nextlit(litteral* litteralCNF);

extern int P_getval(litteral* litteralCNF);

extern cnf* P_parse(int nbarg, char* args[]);

extern void P_remclse(cnf* formuleCNF, clause* clauseCNF);

extern void P_printCNF(cnf* formuleCNF);

#endif /* PARSEUR_H */