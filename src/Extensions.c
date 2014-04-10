#include "Extensions.h"

int CheckNonTerminal(Production* p)
{
	int i,
		_existNT = 0;

	if (p->left.length > 1)
	{
		for (i = 0; i < p->left.length; i++)
		{
			if (is_nonterminal(p->left.word[i]))
				_existNT = 1;
		}
	

	}
	else
	{
		if (is_nonterminal(p->left.word[0]))
			_existNT = 1;
	}

	return _existNT;
	
}

int CheckInitSymbol(Grammar* g)
{
	int i,
		_existInitS = 0;

	for (i = 0; i < g->numprod && !_existInitS; i++)
	{
		if (g->productions[i].left.length == 1 && g->productions->left.word[0] == INIT_SYMBOL)
		{
			_existInitS = 1;
		}
	}

	return _existInitS;
}

int GrammarCF(Grammar* g)
{
	int i,
		_isCF = 1;

	for (i = 0; i < g->numprod && _isCF; i++)
	{
		if (g->productions[i].left.length > 1)
			_isCF = 0;
	}

	return _isCF;
}

int IsMonotonic(Grammar* g)
{
	int i,
		_IsMonotonic = 1;

	for (i = 0; i < g->numprod && _IsMonotonic; i++)
	{
		if (g->productions[i].left.length > g->productions[i].right.length)
			_IsMonotonic = 0;
	}

	return _IsMonotonic;
}

int IsRightLinear(Grammar* g)
{
	int i,
		_isRightLinear = 1;

	for (i = 0; i < g->numprod && _isRightLinear; i++)
	{
		if (g->productions[i].left.length > 1)
			_isRightLinear = 0;
		else if (g->productions[i].left.length == 1 && is_nonterminal(g->productions[i].left.word[0]))
		{
			if (g->productions[i].right.length == 1 && is_nonterminal(g->productions[i].right.word[0]))
			{
				_isRightLinear = 0;
			}
			else if (g->productions[i].right.length == 2 )
			{
				if (is_nonterminal(g->productions[i].right.word[0]) && is_terminal(g->productions[i].right.word[1]))
					_isRightLinear = 0;
			}
			else if(g->productions[i].right.length == 0) _isRightLinear = 1;
			else _isRightLinear = 0;
		}
		else
			_isRightLinear = 0;
	}

	return _isRightLinear;
}

void ErrorManager(enum States _type, Production* p, int _line)
{
	switch (_type)
	{
	
	case NO_INITSYM:
		
		fprintf(stdout, "\n!!! ERROR : Missing INIT SYMBOL in the current grammar! \n");
		break;
	case NO_NT:
		print_production(p);
		fprintf(stdout, " ERROR : Missing NT in the left side of production (%d) \n",_line);
		break;
	case NO_PRODSYM:
		print_word(&p->left);
		fprintf(stdout, "ERROR : Missing production symbol in production (%d) \n",_line);
		
		break;
	case INVALID_SYMBOL:
		print_production(p);
		fprintf(stdout, " ERROR : INVALID SYMBOL in production (%d) \n", _line);

		break;
	case INDEX_OUT_RANGE:
		fprintf(stdout,"ERROR! Index out of range! \n");
		break;
	}
}


void DeleteProduction(Grammar* g,int _index)
{
	
	if(_index < 0 || _index > g->numprod )
		ErrorManager(INDEX_OUT_RANGE,NULL,0);
	else
	{
		g->productions[_index-1] = g->productions[g->numprod-1];
		g->numprod--;
	}
	
}

void DrawErrors(Errors _vector, Grammar* g)
{
	int i;

	for (i = 0; i < _vector.size; i++)
		ErrorManager(_vector.type[i], &g->productions[_vector.lines[i] - 1], _vector.lines[i]);

}


