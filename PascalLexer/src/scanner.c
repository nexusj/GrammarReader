#include "scanner.h"

char* keywords[] =
{
	"begin", "boolean", "char", "do", "else", "end",
	"false", "for", "if", "integer", "program", "real", "repeat",
	"then", "to", "true", "until", "var", "while", NULL
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
		BR_COM,         /* Parentesi o commento */
		START_COM,      /* All'interno di un commento */
		AST_IN_COM,     /* Asterisco in commento*/
		G_GE,           /* Maggiore o maggiore-uguale*/
		L_LE_D,         /* Minore, minore-uguale, o diverso*/
		COL_ASS,        /* Due punti o assegnamento*/
		NUM,            /* Numero intero o reale*/
		NUM_R,          /* Numero reale */
		IN_STR,         /* Stringa*/
		APEX            /* Apice in stringa*/
	} current_state = S;


	int i = 0;
	int eot = 0;    /*end of token*/

	tkn->type = ERROR;

	while (!eot && i<MAX_STRING_LENGTH)
	{
		if (!lookahead)
			c = fgetc(src);
		else
			lookahead = 0;

		if (c == EOF)
			break;
		else switch (current_state)
		{
		case S:
			if (isalpha(c) || c == '_')
			{
				current_state = ID_KW;
				tkn->value[i++] = c;
				tkn->type = IDENTIFIER;
			}
			else if (isspace(c))
				current_state = S;
			else if (isdigit(c))
			{
				current_state = NUM;
				tkn->value[i++] = c;
				tkn->type = INTEGER;
			}
			else switch (c)
			{
			case '+':
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
				tkn->type = SLASH;
				tkn->value[i++] = c;
				eot = 1;
				break;
			case '=':
				tkn->type = EQUAL;
				tkn->value[i++] = c;
				eot = 1;
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
			case '(':
				current_state = BR_COM;
				tkn->value[i++] = c;
				break;
			case ')':
				tkn->type = RIGHT_PAR;
				tkn->value[i++] = c;
				eot = 1;
				break;
			case '{':
				current_state = START_COM;
				break;
			case '>':
				break;
				current_state = G_GE;
				tkn->value[i++] = c;
				break;
			case '<':
				current_state = L_LE_D;
				tkn->value[i++] = c;
				break;
			case ':':
				current_state = COL_ASS;
				tkn->value[i++] = c;
				break;
			case '\'':
				current_state = IN_STR;
				break;
			case '$':
				current_state = NUM;
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
				current_state = ID_KW;
				tkn->value[i++] = c;
			}
			else
			{
				lookahead = 1;
				eot = 1;
			}
			break;
		case BR_COM:
			if (c == '*')
			{
				current_state = START_COM;
				i--;
			}
			else
			{
				lookahead = 1;
				eot = 1;
				tkn->type = LEFT_PAR;
			}
			break;
		case START_COM:
			if (c == '*')
				current_state = AST_IN_COM;
			else if (c == '}')
				current_state = S;
			break;
		case AST_IN_COM:
			if (c == ')')
			{
				current_state = S;
			}
			else
				current_state = START_COM;
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
		case L_LE_D:
			if (c == '=')
			{
				tkn->type = LESS_OR_EQUAL;
				tkn->value[i++] = c;
				eot = 1;
			}
			else if (c == '>')
			{
				tkn->type = DIFFERENT;
				tkn->value[i++] = c;
				eot = 1;
			}
			else
			{
				tkn->type = LESS;
				eot = lookahead = 1;
			}
			break;
		case COL_ASS:
			if (c == '=')
			{
				tkn->type = ASSIGNMENT;
				tkn->value[i++] = c;
				eot = 1;
			}
			else
			{
				tkn->type = COLON;
				eot = lookahead = 1;
			}
			break;
		case NUM:
			if (isalnum(c))
				tkn->value[i++] = c;
			else if (c == '.' )
			{
				current_state = NUM_R;
				tkn->value[i++] = c;
			}
			else
			{
				tkn->type = INTEGER;
				eot = lookahead = 1;
			}
			break;
		case NUM_R:
			if (isdigit(c) || c == 'E')
				tkn->value[i++] = c;
			else
			{
				tkn->type = REAL;
				eot = lookahead = 1;
			}
			break;
		case IN_STR:
			if (c == '\'')
				current_state = APEX;
			else
			{
				tkn->value[i++] = c;
			}
			break;
		case APEX:
			if (c == '\'')
			{
				current_state = IN_STR;
				tkn->value[i++] = c;
			}
			else
			{
				eot = lookahead = 1;
				tkn->type = STRING;
			}
			break;
		}

	}

	tkn->value[i++] = '\0';

	if (isKeyword(tkn->value)) 
		tkn->type = KEYWORD;

	return (c != EOF);
}