#include "DFA.h"

int main(int argc, char* argv[])
{
	char buffer[MAX_LENGTH + 1];
	char* filename = argv[1];
	FILE* file;

	file = fopen("test.date", "r");
	if (file == NULL)
	{
		printf("file inesistente");
		system("PAUSE");
		return -1;
	}


	while (!feof(file))
	{
		if (fgets(buffer, MAX_LENGTH, file))
			switch (scan(buffer))
		{
			case 0:
				printf("%s RICONOSCIUTO\n", buffer);
			break;

			case 1:
				printf("%s NON RICONOSCIUTO : non raggiunto stato finale !\n", buffer);
			break;

			case 2:
				printf("%s NON RICONOSCIUTO : simbolo esterno all'alfabeto\n", buffer);
			break;

			case 3:
				printf("%s NON RICONOSCIUTO: transizione non definita\n", buffer);
			break;

			
		}
				
			
	}

	fclose(file);
	system("PAUSE");
	return 0;
}