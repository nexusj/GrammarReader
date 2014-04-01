#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "Grammar.h"
#include "Extensions.h"




int main(int argc, char *argv[])
{

	char* filename = argv[1];
	FILE* gram_file;
	Grammar grammar;
	int choice = 0;
	// controlla se è stato inserito il nome del file

	if (filename == 0)
	{
		filename = malloc(25);
		printf("nome file non specificato \n");
		fprintf(stdout, "Inserire il nome del file: ");
		scanf("%s", filename);
		sprintf(filename, "%s.txt", filename);
	}

	// apertura del file contenente la grammatica

	gram_file = fopen(filename, "r");
	if (gram_file == NULL)
	{
		fprintf(stderr, "Errore durante il caricamento della grammatica: %s \n", strerror(errno));
	
		system("PAUSE");
		return -1;
	}

	print_grammar(load_grammar(gram_file, &grammar));
	
	fclose(gram_file);

	//1 punto
	//fprintf(stdout, "Are there NT in left production?: %s\n", CheckNonTerminal(&grammar.productions[0]) ? "True" : "False");

	//2 punto
	//fprintf(stdout, "is there InitSymbol?: %s\n", CheckInitSymbol(&grammar) ? "True" : "False");

	//3 punto
	//fprintf(stdout, "is CF?: %s\n", GrammarCF(&grammar) ? "True" : "False");

	//4 punto
	//fprintf(stdout, "is Monotonic?: %s\n", IsMonotonic(&grammar) ? "True" : "False");

	//5 punto
	//fprintf(stdout, "is RightLinear?: %s\n", IsRightLinear(&grammar) ? "True" : "False");

	//6 punto
	/*fprintf(stdout,"Inserire numero della produzione da eliminare : ");
	scanf("%d",&choice);
	DeleteProduction(&grammar,choice);
	print_grammar(&grammar);*/

	//print_grammar(load_grammar(stdin,&grammar));
	system("PAUSE");
	return 0;
}