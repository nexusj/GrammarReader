#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "Grammar.h"
#include "Extensions.h"




int main(int argc, char *argv[])
{

	char* filename = malloc(30);
	FILE* gram_file;
	Grammar grammar1,
			grammar2,
			grammar3;
	
	
	// controlla se è stato inserito il nome del file
	

	fprintf(stdout, "Inserire nome della prima grammatica : ");
	gets(filename);
	sprintf(filename, "%s.txt", filename);

	LoadGrammar(filename, &grammar1, true);

	//print_grammar(IterateGrammar(&grammar1, &grammar3));
	//fprintf(stdout, "Is CS? : %s\n", GrammarCS(&grammar1) ? "True" : "False");
	/*fprintf(stdout, "Inserire nome della seconda grammatica : ");
	gets(filename);
	sprintf(filename, "%s.txt", filename);

	LoadGrammar(filename, &grammar2, true);*/

	
	 //JoinGrammar(&grammar1,&grammar2,&grammar3);
	print_grammar( ConvertToCS(&grammar1,&grammar3));


	
	//JoinGrammar(&grammar1, &grammar2);
	/* 
	*Andava bene quando si caricava soltanto una grammatica
	*/
	/*if (filename == 0)
	{
		filename = malloc(25);
		printf("nome file non specificato \n");
		fprintf(stdout, "Inserire il nome del file: ");
		scanf("%s", filename);
		sprintf(filename, "%s.txt", filename);
	}*/

	
	// apertura del file contenente la grammatica

	
	
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