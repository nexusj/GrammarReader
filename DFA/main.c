#include "DFA.h"

int main(int argc, char* argv[])
{
	char buffer[MAX_LENGTH + 1];
	char* filename = argv[1];
	FILE* file;

	file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("file inesistente");
		system("PAUSE");
		return -1;
	}


	while (!feof(file))
	{
		if (fgets(buffer, MAX_LENGTH, file))
			if (scan(buffer))
				printf("%s RICONOSCIUTO\n", buffer);
			else
				printf("%s NON RICONOSCIUTO\n", buffer);
	}

	fclose(file);
	system("PAUSE");
	return 0;
}