/********************************************************************
	created:	2014/06/19
	created:	19:6:2014   12:34
	filename: 	C:\Users\NexusJ\Documents\GitHub\GrammarReader\DateDFA\DFA.h
	file path:	C:\Users\NexusJ\Documents\GitHub\GrammarReader\DateDFA
	file base:	DFA
	file ext:	h
	author:		Vito Palumbo (aka NexusJ)
	
	purpose:	Questo progetto fornisce un automa a stati finiti deterministico,il quale riconosce l'ora nel formato 24 ore.
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LENGTH 100

int scan(char* s);