/********************************************************************
	created:	2014/06/19
	created:	19:6:2014   12:28
	filename: 	C:\Users\NexusJ\Documents\GitHub\GrammarReader\CLexer\main.c
	file path:	C:\Users\NexusJ\Documents\GitHub\GrammarReader\CLexer
	file base:	main
	file ext:	c
	author:		Vito Palumbo (aka NexusJ)
	
	purpose:	Questo progetto fornisce un lexer per un linguaggio C-like (riconosce quasi tutto del C)
*********************************************************************/
#include "scanner.h"

int main(int argc, char *argv[])
{
	char* filename = argv[1];
	FILE* source;
	Token token;
	
	source = fopen("test.c", "r");

	while (getToken(source, &token))
	{
		if (token.type == ERROR)
			printf("Lexical Error (%s)\n", token.value);
		else

			printf("Tipo = %d, Valore = %s\n", token.type, token.value);
	}

	fclose(source);

	system("pause");
	return 0;
}