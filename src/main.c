/********************************************************************
	created:	2014/06/19
	created:	19:6:2014   12:32
	filename: 	C:\Users\NexusJ\Documents\GitHub\GrammarReader\src\main.c
	file path:	C:\Users\NexusJ\Documents\GitHub\GrammarReader\src
	file base:	main
	file ext:	c
	author:		Vito Palumbo (aka NexusJ)
	
	purpose:	Questo è un progetto universitario per l'esame di teoria dei linguaggi formali.
				Esso fornisce un GrammarReader con le seguenti caratteristiche:
				-Verificare a quale gerarchia di Chomsky appartiene la grammatica;
				-Unire,concatenare e iterare le grammatiche;
				-Convertire le produzioni da monotone a CS;
				-ErrorManager (ti mostra gli errori contenuti in ogni produzione);
				-Controllo dell'esistenza dell'init symbol e dei NT nella parte sinistra
*********************************************************************/


#define _CRT_SECURE_NO_WARNINGS 

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
	
	
	
	//1 punto
	/*fprintf(stdout, "Inserire nome della  grammatica : ");
	gets(filename);
	sprintf(filename, "%s.txt", filename);

	LoadGrammar(filename, &grammar1, true);
	fprintf(stdout, "Are there NT in left production?: %s\n", CheckNonTerminal(&grammar1.productions[0]) ? "True" : "False"); */

/*************************************************************************/
	//2 punto
	/*fprintf(stdout, "Inserire nome della  grammatica : ");
	gets(filename);
	sprintf(filename, "%s.txt", filename);

	LoadGrammar(filename, &grammar1, true);
	fprintf(stdout, "is there InitSymbol?: %s\n", CheckInitSymbol(&grammar1) ? "True" : "False");*/

/*************************************************************************/

	//3 punto
	/*fprintf(stdout, "Inserire nome della  grammatica : ");
	gets(filename);
	sprintf(filename, "%s.txt", filename);

	LoadGrammar(filename, &grammar1, true);
	fprintf(stdout, "is CF?: %s\n", GrammarCF(&grammar1) ? "True" : "False");*/

/*************************************************************************/
	//4 punto
	/*fprintf(stdout, "Inserire nome della  grammatica : ");
	gets(filename);
	sprintf(filename, "%s.txt", filename);

	LoadGrammar(filename, &grammar1, true);
	fprintf(stdout, "is Monotonic?: %s\n", IsMonotonic(&grammar1) ? "True" : "False");*/

/*************************************************************************/

	//5 punto
	/*fprintf(stdout, "Inserire nome della  grammatica : ");
	gets(filename);
	sprintf(filename, "%s.txt", filename);

	LoadGrammar(filename, &grammar1, true);
	fprintf(stdout, "is RightLinear?: %s\n", IsRightLinear(&grammar1) ? "True" : "False");*/

/*************************************************************************/

	//6 punto
	/*fprintf(stdout, "Inserire nome della  grammatica : ");
	gets(filename);
	sprintf(filename, "%s.txt", filename);

	LoadGrammar(filename, &grammar1, true);

	fprintf(stdout,"Inserire numero della produzione da eliminare : ");
	scanf("%d",&choice);
	DeleteProduction(&grammar,choice);
	print_grammar(&grammar1); */

/*************************************************************************/
	//7 punto
	/*fprintf(stdout, "Inserire nome della  grammatica : ");
	gets(filename);
	sprintf(filename, "%s.txt", filename);

	LoadGrammar(filename, &grammar1, true);
	fprintf(stdout, "Inserire le nuove produzioni (Premere CTRL-Z ed INVIO per fermarsi) : \n");
	print_grammar(load_grammar(stdin,&grammar1));*/

/*************************************************************************/

	//8 punto
	/*fprintf(stdout, "Inserire nome della prima grammatica : ");
	gets(filename);
	sprintf(filename, "%s.txt", filename);

	LoadGrammar(filename, &grammar1, true);
	print_grammar( ConvertToCS(&grammar1,&grammar3));
	*/

/*************************************************************************/

	//9 punto
	/*fprintf(stdout, "Inserire nome della prima grammatica : ");
	gets(filename);
	sprintf(filename, "%s.txt", filename);

	LoadGrammar(filename, &grammar1, true);
	print_grammar( IterateGrammar(&grammar1,&grammar3));
	*/

/*************************************************************************/

	//10 punto
	/*fprintf(stdout, "Inserire nome della prima grammatica : ");
	gets(filename);
	sprintf(filename, "%s.txt", filename);

	LoadGrammar(filename, &grammar1, true); 

	fprintf(stdout, "Inserire nome della seconda grammatica : ");
	gets(filename);
	sprintf(filename, "%s.txt", filename);

	LoadGrammar(filename, &grammar2, true);

	
	print_grammar(JoinGrammar(&grammar1,&grammar2,&grammar3)); */

/*************************************************************************/
	//11 punto
	/*fprintf(stdout, "Inserire nome della prima grammatica : ");
	gets(filename);
	sprintf(filename, "%s.txt", filename);

	LoadGrammar(filename, &grammar1, true);

	fprintf(stdout, "Inserire nome della seconda grammatica : ");
	gets(filename);
	sprintf(filename, "%s.txt", filename);

	LoadGrammar(filename, &grammar2, true);


	print_grammar(ConcatenateGrammar(&grammar1,&grammar2,&grammar3)); */

	system("PAUSE");
	return 0;
}