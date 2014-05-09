#ifndef _EXTENSIONS_H_
#define  _EXTENSIONS_H_

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS 1
#endif

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Grammar.h"

#define INIT_SYMBOL "S"
#define BUFFER_TABLE_SIZE 26
struct  _Table
{
    Symbol buffer[BUFFER_TABLE_SIZE];
	unsigned lenght;
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
void CheckCommonNT(Grammar* _g1, Grammar* _g2);
Grammar JoinGrammar(Grammar* _g1, Grammar* _g2);
Grammar ConcatenateGrammar(Grammar* _g1, Grammar* _g2);
void ChangeNT(Grammar* g, const char* _s);
void ShifLVectorCh(char* _vector, int _index, int*_lenght);
void ShiftRVectorP(Grammar* g, int _index);
void AdjustTableNT(struct _Table* _table, Grammar* _g);


#endif


