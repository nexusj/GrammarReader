#include "Extensions.h"


struct _Table NTTable =
{
	{ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' }, 0
};

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

int LoadGrammar(const char* _path, Grammar* g, bool _draw)
{
	FILE* gram_file = fopen(_path, "r");
	if (gram_file == NULL)
	{
		fprintf(stderr, "Errore durante il caricamento della grammatica(%s): %s \n", _path,strerror(errno));
		
		
		return -1;
	}

	load_grammar(gram_file, g);
	if (_draw)
	print_grammar(g);

	fclose(gram_file);

	return 0;
}

int AreDisjointed(Grammar* _g1, Grammar* _g2)
{
	int i,j,
		_djointed = 1;

	for (i = 0; i < _g1->numprod ; i++)
	{
		if ( _g1->productions[i].left.word[0] != INIT_SYMBOL)

		{
			if (CheckNonTerminal(&_g1->productions[i]))
			{
				for (j = 0; j < _g2->numprod; j++)
				{
					if (strcmp(_g1->productions[i].left.word, _g2->productions[j].left.word) == 0)
					{
						ChangeNT(_g2, _g2->productions[j].left.word);
						
					}
						
						//_djointed = 0;
				}
			 }
			
		}			
	}
	
	return _djointed;
}

Grammar JoinGrammar(Grammar* _g1, Grammar* _g2)
{
	Grammar g;
	int i;

	AreDisjointed(_g1, _g2);

	g.numprod = _g1->numprod + _g2->numprod;

	

	for (i = 0; i < _g1->numprod; i++)
	{
		strcpy(g.productions[i].left.word, _g1->productions[i].left.word);
		g.productions[i].left.length = _g1->productions[i].left.length;

		strcpy(g.productions[i].right.word, _g1->productions[i].right.word);
		g.productions[i].right.length = _g1->productions[i].right.length;
		
	}


	for (i = 0; i < _g2->numprod; i++)
	{
		strcpy(g.productions[i + (g.numprod - _g2->numprod)].left.word, _g2->productions[i].left.word);
		g.productions[i + (g.numprod - _g2->numprod)].left.length = _g2->productions[i].left.length;

		strcpy(g.productions[i + (g.numprod - _g2->numprod)].right.word, _g2->productions[i].right.word);
		g.productions[i + (g.numprod - _g2->numprod)].right.length = _g2->productions[i].right.length;

	}
	
	return g;
}

void ChangeNT(Grammar* g, const char* _s)
{
	
	int i;
	char* _tmp;

	if (strcmp(_s,&NTTable.buffer[NTTable.offset]))
		NTTable.offset++;

	for (i = 0; i < g->numprod; i++)
	{
		

		
		if (strcmp(_s, g->productions[i].left.word) == 0)
		{
			_tmp = strstr(g->productions[i].left.word, _s);
			strcpy(_tmp,&NTTable.buffer[NTTable.offset]);
		}

		_tmp = strchr(g->productions[i].right.word,_s[0]);

		if (_tmp)
	     strncpy(_tmp, &NTTable.buffer[NTTable.offset], 1);
	
			
	}

}








