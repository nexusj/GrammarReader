#ifndef _GRAMMAR_H_
#define _GRAMMAR_H_

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS 1
#endif

#include <stdio.h>
#include <ctype.h>



#define MAX_WORD_LENGTH 100
#define MAX_PRODUCTIONS 100

#pragma region Structures
typedef char Symbol;

enum States { START, LEFT, RIGHT,NO_ERROR, NO_INITSYM, NO_NT, NO_PRODSYM, INDEX_OUT_RANGE, INVALID_SYMBOL,NO_CONCT,NO_ITER,NO_TRANSF};
/*   START  = Scansione di una nuova produzione [F]
LEFT   = Scansione della parte sinistra
RIGHT  = Scansione della parte destra [F]
NO_ERROR = Nessun errore rilevato
NO_INITSYM = Nessun simbolo iniziale 
NO_NT = Nessun NT
NO_PRODSYM = Nessun simbolo di produzione
INDEX_OUT_RANGE = Indice fuori dall'intervallo consentito
INVALID_SYMBOL = Simbolo non valido
NO_CONCT = Concatenazione fallita
NO_ITER = Iterazione fallita
NO_TRANSF = Trasformazione da monotona a CS fallita
*/


/* Grandezza massima del buffer che conterrà i tipi di errori rilevati */
#define  BUFFER_ERROR 250
typedef struct
{
	enum States type[BUFFER_ERROR]; //Buffer che contiene i tipi di errori rilevati
	unsigned size;					//Grandezza del buffer
	unsigned lines[BUFFER_ERROR];	//Linea/#produzione in cui compare l'errore
}Errors;

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