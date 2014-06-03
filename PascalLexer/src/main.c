#include "scanner.h"

int main(int argc, char* argv[])
{
	char* filename = argv[1];
	FILE* source;
	Token token;

	source = fopen("test.pas", "r");

	while (getToken(source, &token))
	{
		if (token.type == ERROR)
			printf("Lexical Error (%s)\n", token.value);
		else

			printf("Tipo = %d, Valore = %s\n", token.type, token.value);
	}

	fclose(source);

	system("PAUSE");

	return 0;
}