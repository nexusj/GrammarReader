#ifndef _GRAMMAR_H_
#define _GRAMMAR_H_
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <ctype.h>



#define MAX_WORD_LENGTH 100
#define MAX_PRODUCTIONS 100

#pragma region Structures
typedef char Symbol;

enum States { START, LEFT, RIGHT, NO_INITSYM, NO_NT, NO_PRODSYM, INDEX_OUT_RANGE};
/*   START  = Scansione di una nuova produzione [F]
LEFT   = Scansione della parte sinistra
RIGHT  = Scansione della parte destra [F]
ERROR  = Errore di scansione
*/
typedef struct
{
	Symbol word[MAX_WORD_LENGTH];
	unsigned length;
} Word;

typedef struct
{
	Word left;
	Word right;
} Production;

typedef struct
{
	Production productions[MAX_PRODUCTIONS];
	unsigned numprod;
} Grammar;
#pragma endregion





int is_terminal(Symbol s);
int is_nonterminal(Symbol s);
int is_prodsym(Symbol s);
int is_prodsep(Symbol s);



Symbol read_sym(FILE* file);

Production* add_new_production(Grammar *g);

Grammar* load_grammar(FILE* file, Grammar* g);

void add_symbol(Word *w, Symbol s);
void print_sym(Symbol s);
void print_word(Word* w);
void print_production(Production* p);
void print_grammar(Grammar* g);
#endif // !_GRAMMAR_H_