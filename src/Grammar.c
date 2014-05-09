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
	//enum States error = -1;
	Symbol s;
	Production* p = NULL;
	Errors error;
	error.size = 0;

	if(file != stdin)
	g->numprod = 0; // Inizializza la grammatica

	while ( !feof(file) )
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
			else if (ispunct(s) || isgraph(s))
			{ 
				current_state = LEFT;
				p = add_new_production(g);
				add_symbol(&p->left, s);
				error.type[error.size] = INVALID_SYMBOL;
				error.lines[error.size] = g->numprod;
				error.size++;
			}
				
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
				{
					error.type[error.size] = NO_NT;
					error.lines[error.size] = g->numprod;
					error.size++;
					
				}
					
				//ErrorManager(NO_NT, p);
			}
			else if (ispunct(s) || isgraph(s))
			{
				current_state = LEFT;

				add_symbol(&p->left, s);
				error.type[error.size] =  INVALID_SYMBOL;
				error.lines[error.size] = g->numprod;
				error.size++;
			}
				
			
 			else if(is_prodsep(s))
			{
				error.type[error.size] = NO_PRODSYM;
				error.lines[error.size] = g->numprod;
				error.size++;
				//ErrorManager(NO_PRODSYM_MAYBE, p, g->numprod);
				current_state = START;
			}
			else
			{

				error.type[error.size] = NO_PRODSYM;
				error.lines[error.size] = g->numprod;
				error.size++;
				
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
				g->productions[g->numprod-1].left.word[g->productions[g->numprod-1].left.length] = '\0';
				g->productions[g->numprod - 1].right.word[g->productions[g->numprod - 1].right.length] = '\0';
				//ErrorManager(error, p,g->numprod);
				
			}
			else if (ispunct(s) || isgraph(s))
			{
				current_state = RIGHT;

				add_symbol(&p->right, s);
				error.type[error.size] = INVALID_SYMBOL;
				error.lines[error.size] = g->numprod;
				error.size++;
			}
			break;
		
			
			
		}
		
	}

	if (error.size > 0)
	{
		DrawErrors(error, g);
		if (!CheckInitSymbol(g))
			ErrorManager(NO_INITSYM, NULL, 0);
		
		g = NULL;
	}

	if (g)
	if (!CheckInitSymbol(g))
	{
		ErrorManager(NO_INITSYM, NULL,0);
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