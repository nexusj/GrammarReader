#include "Grammar.h"

int is_terminal(Symbol s)
{
	return (islower(s));
	//return (s >= 'a') && (s <= 'z');
}

int is_nonterminal(Symbol s)
{
	return (isupper(s));
	//return (s >= 'A') && (s <= 'Z');
}

int is_prodsym(Symbol s)
{
	return (s == '>');
}

int is_prodsep(Symbol s)
{
	return (s == '\n');
}

/* Lettura di simboli da file ------------------------------------------------*/

Symbol read_sym(FILE* file)
{
	Symbol s;

	// fscanf(file,"%c",&s); 

	//questo ciclo permette di saltare la lettura di spazi tra i simboli
	do
	s = getc(file);
	while (s == ' ');

	return s;
}

Production* add_new_production(Grammar *g)
{
	Production* p;
	p = &(g->productions[g->numprod++]);
	p->left.length = 0;
	p->right.length = 0;

	return p;
}





// Procedura di acquisizione di una grammatica da un file --------------------*/

Grammar* load_grammar(FILE* file, Grammar* g)
{
	
	enum States current_state = START;  // Stato iniziale
	Symbol s;
	Production* p = NULL;
	

	g->numprod = 0; // Inizializza la grammatica

	while ( !feof(file))
	{
		s = read_sym(file);
		if (feof(file)) break;
		switch (current_state)
		{
		case START:
			if (is_terminal(s) || is_nonterminal(s))
			{
				current_state = LEFT;

				//p = &(g->productions[g->numprod++]);
				//p->left.length = 0;
				p = add_new_production(g);
				add_symbol(&p->left, s);
				//L'istruzione precedente corrisponde a p->left.word[p->left.length++] = s;
			}
			else if (is_prodsep(s))
			{
				current_state = START;
			}
			/*else
				NO_NT*/
			break;
		case LEFT:
			if (is_terminal(s) || is_nonterminal(s))
			{
				current_state = LEFT;
				add_symbol(&p->left, s);
			}
			else if (is_prodsym(s))
			{
				current_state = RIGHT;
				if (!CheckNonTerminal(p))
					ErrorManager(NO_NT, p);
			}
			else
			{
				
				ErrorManager(NO_PRODSYM, p);
				current_state = RIGHT;
			}
			break;

		case RIGHT:
			if (is_terminal(s) || is_nonterminal(s))
			{
				current_state = RIGHT;
				add_symbol(&p->right, s);
			}
			else if (is_prodsep(s))
			{
				current_state = START;
			}
			
			break;
		
			
			
		}
		
	}

	if (!CheckInitSymbol(g))
	{
		ErrorManager(NO_INITSYM, NULL);
		g = NULL;
	}
		

		

	return g;
}


void add_symbol(Word *w, Symbol s)
{
	w->word[w->length++] = s;
}
// Procedure di stampa

void print_sym(Symbol s)
{
	printf("%c ", s);
}


void print_word(Word* w)
{
	int i;

	for (i = 0; i < w->length; i++)
		print_sym(w->word[i]);
}

void print_production(Production* p)
{
	print_word(&p->left);
	printf(" --> ");
	print_word(&p->right);
}

void print_grammar(Grammar* g)
{
	int i;

	if (g != NULL)
	{
		printf("Numero di produzioni: %d\n", g->numprod);
		for (i = 0; i < g->numprod; i++)
		{
			print_production(&g->productions[i]);
			printf("\n");
		}
	
	}
	else
		fprintf(stdout, "Grammatica non valida !\n");
}