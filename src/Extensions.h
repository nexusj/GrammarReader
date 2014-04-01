#ifndef _EXTENSIONS_H_
#define  _EXTENSIONS_H_
#include "Grammar.h"

#define INIT_SYMBOL 'S'

int CheckNonTerminal(Production* p);
int CheckInitSymbol(Grammar* g);
int GrammarCF(Grammar* g);
int IsMonotonic(Grammar* g);
int IsRightLinear(Grammar* g);
void ErrorManager(enum States _type, Production* p, int _line);
void DeleteProduction(Grammar* g ,int _index);



#endif


