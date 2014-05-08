#ifndef _EXTENSIONS_H_
#define  _EXTENSIONS_H_

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Grammar.h"

#define INIT_SYMBOL 'S'
#define BUFFER_TABLE_SIZE 26
struct  _Table
{
    Symbol buffer[BUFFER_TABLE_SIZE];
	unsigned offset;
};




int CheckNonTerminal(Production* p);
int CheckInitSymbol(Grammar* g);
int GrammarCF(Grammar* g);
int IsMonotonic(Grammar* g);
int IsRightLinear(Grammar* g);
void ErrorManager(enum States _type, Production* p, int _line);
void DeleteProduction(Grammar* g ,int _index);
void DrawErrors(Errors _vector,Grammar* g);
int LoadGrammar(const char* _path, Grammar* g, bool _draw);
int AreDisjointed(Grammar* _g1, Grammar* _g2);
Grammar JoinGrammar(Grammar* _g1, Grammar* _g2);
void ChangeNT(Grammar* g, const char* _s);



#endif


