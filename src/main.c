#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>

#include "Grammar.h"
#include "Extensions.h"




int main(int argc, char *argv[])
{

	char* filename = argv[1];
	FILE* gram_file;
	Grammar grammar;

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
		printf("nome di file errato\n");
	
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
	//fprintf(stdout, "is Monotonic?: %s\n", IsRightLinear(&grammar) ? "True" : "False");

	system("PAUSE");
	return 0;
}