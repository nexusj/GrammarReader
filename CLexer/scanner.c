#include "scanner.h"


char* keywords[] =
{
	"break", "case", "char", "const", "do", "double", "else", "enum", "extern", "float", "for", "if",
	"int", "long", "return", "sizeof", "static", "struct", "switch", "typedef", "void", "while"
};

int isKeyword(String s)
{
	int i = 0;
	int ris = 0;

	while (keywords[i])
		if (strcmp(keywords[i++], s) == 0)
			ris = 1;

	return ris;
}

int getToken(FILE* src, Token* tkn)
{
	static char c;
	static int lookahead = 0;

	enum
	{
		S,              /* Stato Iniziale */
		ID_KW,          /* Identificatore o Keyword */
		BRACKET,        /* Parentesi */
		DIV_COM,		/* Divisione o commento*/
		START_COM,      /* All'interno di un commento */
		G_GE,           /* Maggiore o maggiore-uguale*/
		L_LE,			/* Minore o minore-uguale*/
		EQ_ASS,			/* Uguaglianza o Assegnamento*/
		NUM,            /* Numero intero,virgola mobile(singola/doppia precisione)*/
		NUM_R,          /* Numero reale */
		IN_STR,         /* Stringa*/
		PLUS_INC,		/* Più o incremento*/
		NOT_EQ			/* Non uguale*/
		
	} currentState = S;

	int i = 0,
		eot = 0;

	tkn->type = ERROR;

	while (!eot && i < MAX_STRING_LENGTH)
	{
		if (!lookahead)
			c = fgetc(src);
		else
			lookahead = 0;

		if (c == EOF)
			break;
		else switch (currentState)
		{
			case S:
				if (isalpha(c) || c == '_')
				{
					currentState = ID_KW;
					tkn->value[i++] = c;
					tkn->type = IDENTIFIER;
				}
				else if (isspace(c))
					currentState = S;
				else if (isdigit(c))
				{
					currentState = NUM;
					tkn->value[i++] = c;
					tkn->type = INTEGER;
				}
				else switch (c)
				{
					case '+':
						currentState = PLUS_INC;
						tkn->value[i++] = c;
						break;
						tkn->type = PLUS;
						tkn->value[i++] = c;
						eot = 1;
						break;
					case '-':
						tkn->type = MINUS;
						tkn->value[i++] = c;
						eot = 1;
						break;
					case '*':
						tkn->type = ASTERIX;
						tkn->value[i++] = c;
						eot = 1;
						break;
					case '/':
						currentState = DIV_COM;
						tkn->value[i++] = c;
						break;
					case '=':
						currentState = EQ_ASS;
						tkn->value[i++] = c;
						break;
					case ';':
						tkn->type = SEMICOLON;
						tkn->value[i++] = c;
						eot = 1;
						break;
					case '.':
						tkn->type = DOT;
						tkn->value[i++] = c;
						eot = 1;
						break;
					case ',':
						tkn->type = COMMA;
						tkn->value[i++] = c;
						eot = 1;
						break;
					case '(' :
						//currentState = BRACKET;
						tkn->type = LEFT_PAR;
						tkn->value[i++] = c;
						eot = 1;
						break;
					case ')' :
						tkn->type = RIGHT_PAR;
						tkn->value[i++] = c;
						eot = 1;
						break;
					case '[':
						//currentState = BRACKET;
						tkn->type = LEFT_PAR;
						tkn->value[i++] = c;
						eot = 1;
						break;
					case ']':
						tkn->type = RIGHT_PAR;
						tkn->value[i++] = c;
						eot = 1;
						break;
					case '{':
						tkn->type = START_BLOCK;
						tkn->value[i++] = c;
						eot = 1;
						break;
					case '}':
						tkn->type = END_BLOCK;
						tkn->value[i++] = c;
						eot = 1;
						break;
					case '>':
						currentState = G_GE;
						tkn->value[i++] = c;
						break;
					case '<':
						currentState = L_LE;
						tkn->value[i++] = c;
						break;
					case '"':
						currentState = IN_STR;
						tkn->value[i++] = c;
						break;
					case '!':
						currentState = NOT_EQ;
						tkn->type = DIFFERENT;
						tkn->value[i++] = c;
						break;
					default:
						eot = 1;
						tkn->value[i++] = c;
						
				}
				break;
			case ID_KW:
				if (isalnum(c) || c == '_')
				{
					currentState = ID_KW;
					tkn->value[i++] = c;
				}
				else
				{
					lookahead = 1;
					eot = 1;
				}
				break;
			/*case BRACKET:
				if (c == ')')
				{
					currentState = START_COM;
					i--;
				}
				else
				{
					lookahead = 1;
					eot = 1;
					tkn->type = LEFT_PAR;
				}
				break;*/
			case START_COM:
				if (c == '/' || c == '\n')
					currentState = S;
				break;
			case G_GE:
				if (c == '=')
				{
					tkn->type = GREATER_OR_EQUAL;
					tkn->value[i++] = c;
					eot = 1;
				}
				else
				{
					tkn->type = GREATER;
					eot = lookahead = 1;
				}
				break;
			case L_LE:
				if (c == '=')
				{
					tkn->type = LESS_OR_EQUAL;
					tkn->value[i++] = c;
					eot = 1;
				}
				else
				{
					tkn->type = LESS;
					eot = lookahead = 1;
				}
				break;
			case EQ_ASS:
				if (c == '=')
				{
					tkn->type = EQUAL;
					tkn->value[i++] = c;
					eot = 1;
				}
				else
				{
					tkn->type = ASSIGNMENT;
					eot = lookahead = 1;
				}
				break;
			case NUM:
				if (isdigit(c))
					tkn->value[i++] = c;
				else if (c == '.')
				{
					currentState = NUM_R;
					tkn->value[i++] = c;
				}
				else
				{
					tkn->type = INTEGER;
					eot = lookahead = 1;
				}
				break;
			case NUM_R:
				if (isdigit(c))
					tkn->value[i++] = c;
				else if (c == 'f' || c == 'F')
				{
					tkn->type = FLOAT;
					tkn->value[i++] = c;
					eot = 1;
				}
				else if (c == 'l' || c == 'L')
				{
					tkn->type = DOUBLE;
					tkn->value[i++] = c;
					eot =  1;
				}
				else
				{
					tkn->type = DOUBLE;
					eot = lookahead = 1;
				}
				break;
			case IN_STR:
				if (c == '"')
				{
					eot = 1;
					tkn->type = STRING;
					tkn->value[i++] = c;
				}
				else
				{
					tkn->value[i++] = c;
				}
				break;
			case DIV_COM:
				if (c == '*' || c == '/')
				{
					currentState = START_COM;
					i--;
				}
				else
				{
					eot = lookahead = 1;
					tkn->type = SLASH;
				}
				break;
			case PLUS_INC:
				if (c == '+')
				{
					tkn->type = INC;
					tkn->value[i++] = c;
					eot = 1;
				}
				break;
			case NOT_EQ:
				if (c == '=')
				{
					tkn->value[i++] = c;
					eot = 1;
				}
				else
					eot = lookahead = 1;
				break;
		}

	}

	tkn->value[i++] = '\0';

	if (isKeyword(tkn->value))
		tkn->type = KEYWORD;

	return (c != EOF);
}
