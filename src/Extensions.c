#include "Extensions.h"

/* Inizializzo la tabella dei NT liberi con l'alfabeto */
struct _Table NTTable =
{
	{ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'},BUFFER_TABLE_SIZE
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
		if (g->productions[i].left.length == 1 && g->productions[i].left.word[0] == INIT_SYMBOL[0])
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

int GrammarCS(Grammar* g)
{
	int i,
		j = 0,
		_isCS = 1,
		contextleft = 0,
		contextright = 0;

	for (i = 0; i < g->numprod && _isCS; i++)
	{
		while (j < g->productions[i].left.length && g->productions[i].left.word[j] == g->productions[i].right.word[j])
		{
			contextleft++;
			j++;
		}

		j = g->productions[i].left.length - 1;
		while (j > 0 && g->productions[i].left.word[j] == g->productions[i].right.word[j])
		{
			contextright++;
			j--;
		}

		j = 0;

		if (g->productions[i].left.length == (contextleft + contextright + 1))
		{
			if ((contextleft + contextright) < g->productions[i].right.length)
				_isCS = 1;

			if (g->productions[i].right.length == 0 && g->productions[i].left.word[0] != INIT_SYMBOL[0])
				_isCS = 0;
			else
				_isCS = 1;
		}
		else
			_isCS = 0;
	}
	
	return _isCS;
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
	case NO_CONCT:
		fprintf(stdout, " ERROR : Impossible to concatenate the two grammars \n");
		break;
	case NO_ITER:
		fprintf(stdout, " ERROR : Impossible to iterate the grammar \n");
		break;
	case NO_TRANSF:
		fprintf(stdout, " ERROR : Impossible to transform the grammar in CS \n");
		break;
	case INDEX_OUT_RANGE:
		fprintf(stdout,"ERROR! Index out of range! \n");
		break;
	}
}


void DeleteProduction(Grammar* g,int _index)
{
	/* Se l'indice è fuori dall'intervallo,viene generato un errore */
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

	/* Stampa gli errori rilevati durante il caricamento della grammatica */
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

	g = load_grammar(gram_file, g);

	if (_draw)
	print_grammar(g);

	fclose(gram_file);

	return 0;
}

void CheckCommonNT(Grammar* _g1, Grammar* _g2)
{
	int i,j;

	//Scorro tutte le produzioni
	for (i = 0; i < _g1->numprod ; i++)
	{
		//Ignoro il simbolo iniziale
		if ( _g1->productions[i].left.word[0] != INIT_SYMBOL[0])

		{
			//Se la produzione della prima grammatica contiene un NT procedo con il confronto
			if (CheckNonTerminal(&_g1->productions[i]))
			{
				for (j = 0; j < _g2->numprod; j++)
				{
					//Se entrambi le parti sinistre sono uguali,chiamo la funzione ChangeNT che sostituirà il NT in comune con uno libero
					if (strcmp(_g1->productions[i].left.word, _g2->productions[j].left.word) == 0)
					{
						ChangeNT(_g2, _g2->productions[j].left.word);
						
					}
						
						
				}
			 }
			
		}			
	}
	
	
}

Grammar* JoinGrammar(Grammar* _g1, Grammar* _g2,Grammar* _g)
{
	
	
	int i;

	
	CheckCommonNT(_g1, _g2);

	

	_g->numprod = _g1->numprod + _g2->numprod;

	//É un semplice "copia-incolla" di stringhe
	for (i = 0; i < _g1->numprod; i++)
	{
		strcpy(_g->productions[i].left.word, _g1->productions[i].left.word);
		_g->productions[i].left.length = _g1->productions[i].left.length;

		strcpy(_g->productions[i].right.word, _g1->productions[i].right.word);
		_g->productions[i].right.length = _g1->productions[i].right.length;
		
	}


	for (i = 0; i < _g2->numprod; i++)
	{
		strcpy(_g->productions[i + (_g->numprod - _g2->numprod)].left.word, _g2->productions[i].left.word);
		_g->productions[i + (_g->numprod - _g2->numprod)].left.length = _g2->productions[i].left.length;

		strcpy(_g->productions[i + (_g->numprod - _g2->numprod)].right.word, _g2->productions[i].right.word);
		_g->productions[i + (_g->numprod - _g2->numprod)].right.length = _g2->productions[i].right.length;

	}

	
	return _g;
}

void ChangeNT(Grammar* g, const char* _s)
{
	
	int i;
	char* _tmp,
		*_cnv = malloc(2);

	//Ridimensiona la tabella dei NT liberi
	AdjustTableNT(&NTTable, g);

	for (i = 0; i < g->numprod; i++)
	{
		
		//Controllo l'esistenza del NT nella parte sinistra della produzione
		_tmp = strchr(g->productions[i].left.word, _s[0]);
		
		if (_tmp)
		{
			//Sostituisco con il primo NT libero (se non è il simbolo iniziale
			if (strcmp(_tmp,INIT_SYMBOL) != 0)
				strncpy(_tmp, &NTTable.buffer[0],1);
			else
			{
				//Altrimenti aggiungo il pedice al simbolo iniziale
				sprintf(_cnv, "%d", ++offset);
				strcat(_tmp, _cnv);
				g->productions[i].left.length++;
				
			}
				
		}
		 
		//Stessa cosa come prima
		_tmp = strchr(g->productions[i].right.word,_s[0]);

		if (_tmp)
		{
			if (strcmp(_tmp, INIT_SYMBOL) != 0)
				strncpy(_tmp, &NTTable.buffer[0],1);
			else
			{
				sprintf(_cnv, "%d", offset);
				strcat(_tmp, _cnv);
				g->productions[i].right.length++;
			}
				
				
		}
	     
	
		
	}

}

Grammar* ConcatenateGrammar(Grammar* _g1, Grammar* _g2, Grammar* _g)
{

	int i;

	offset = 0;

	//Se entrambe le grammatiche sono di tipo 2(CF) si procede con la concatenazione
	if (GrammarCF(_g1) && GrammarCF(_g2))
	{

		//Modifica i simboli iniziali delle due grammatiche aggiungendo i pedici
		ChangeNT(_g1, INIT_SYMBOL);
		ChangeNT(_g2, INIT_SYMBOL);

		//Unisce tutte le loro produzioni
		JoinGrammar(_g1, _g2, _g);


		//Aggiungo il simbolo iniziale nella grammatica alla prima posizione
		AddProduction(_g, INIT_SYMBOL, "S1S2", 0);


	}
	else
	{
		ErrorManager(NO_CONCT, NULL, 0);
		_g = NULL;
	}
		

	return _g;
}

Grammar* IterateGrammar(Grammar* _g1, Grammar* _g)
{
	int i,
		j;

	offset = 0;
	
	//Se la grammatica è di tipo 2 (CF) si procede con l'iterazione
	if (GrammarCF(_g1))
	{
		ChangeNT(_g1, INIT_SYMBOL);


		_g->numprod = _g1->numprod;

		for (i = 0; i < _g1->numprod; i++)
		{
			strcpy(_g->productions[i].left.word, _g1->productions[i].left.word);
			_g->productions[i].left.length = _g1->productions[i].left.length;

			strcpy(_g->productions[i].right.word, _g1->productions[i].right.word);
			_g->productions[i].right.length = _g1->productions[i].right.length;

		}

		//Produzione "S>S1S"
		AddProduction(_g, INIT_SYMBOL, "S1S", 0);
		//Produzione "S>lambda"
		AddProduction(_g, INIT_SYMBOL, NULL, 0);



	}
	else
	{
		ErrorManager(NO_ITER, NULL, 0);
		_g = NULL;
	}
		
	
	

	
	return _g;

}
void ShifLVectorCh(char* _vector, int _index, int* _lenght)
{
	int i;

	//Shift verso sinistra del vettore _vector
	for (i = _index; i < *_lenght; i++)
	{
		_vector[i] = _vector[i + 1];
	}
	*_lenght-=1;
}

void ShiftRVectorP(Grammar* g, int _index)
{
	int i;

	for (i = g->numprod; i > 0; i--)
	{
		g->productions[i] = g->productions[i-1];
	}
	g->numprod++;
}

void AdjustTableNT(struct _Table* _table, Grammar* _g)
{
	int i, j;

	char *_tmp = NULL;

	//Scorro tutte le produzioni
	for (i = 0; i < _g->numprod; i++)
	{
		//Scorro la parte sinistra della produzione
		for (j = 0; j < strlen(_g->productions[i].left.word); j++)
		{
			//Controlla l'esistenza del NT nella tabella dei NT liberi
			_tmp = strchr(_table->buffer, _g->productions[i].left.word[j]);

			//In caso affermativo si effettua lo shift a sinistra della tabella dei NT liberi
			if (_tmp)
			{

				ShifLVectorCh(_table->buffer, _tmp - _table->buffer, &_table->length);

				

			}
		}
		


		
			
	}
	
}

void AddProduction(Grammar* g, char* _left, char* _right, int _index)
{
	ShiftRVectorP(g, _index+1);
	if (_left)
	{
		strcpy(g->productions[_index].left.word, _left);
		g->productions[_index].left.length = strlen(_left);
	}
	else
		g->productions[_index].left.length = 0;
	
	if (_right)
	{
		strcpy(g->productions[_index].right.word, _right);
		g->productions[_index].right.length = strlen(_right);
	}
	else
	{
		g->productions[_index].right.word[0] = '\0';
		g->productions[_index].right.length = 0;
	}
		
	
}

Grammar* ConvertToCS(Grammar* _g1, Grammar* _g)
{
	int i, j, diff = 0;
	
	//Controlla che la grammatica sia monotona
	if (IsMonotonic(_g1))
	{

		_g->numprod = 0;
		AdjustTableNT(&NTTable, _g1);

		//Scorro tutte le produzioni
		for (i = 0; i < _g1->numprod; i++)
		{
			//Effettuo la trasformazioni soltanto se la produzione non è del tipo "S>.."
			if (_g1->productions[i].left.word[0] != INIT_SYMBOL[0])
			{
				//Copio la parte sinistra della produzione in quella della nuova grammatica
				strcpy(_g->productions[i].left.word, _g1->productions[i].left.word);
				_g->productions[i].left.length = _g1->productions[i].left.length;

				//Copio la parte destra sinistra della nuova produzione in quella destra della stessa
				strcpy(_g->productions[i].right.word, _g->productions[i].left.word);
				_g->productions[i].right.length = _g->productions[i].left.length;
				
				_g->numprod++;

				/*Differenza tra la lunghezza della parte destra e sinistra della produzione da trasformare.
				  É utile,in quanto mi permette di copiare i giusti simboli della parte destra a partire da metà ciclo*/
				diff = (_g1->productions[i].right.length - _g1->productions[i].left.length);

				//Qui inizia la trasformazione della produzione
				for (j = 1; j <(2 * _g1->productions[i].left.length) + 1; j++)
				{
					//Controllo che il ciclo non abbia superato la metà della sua lunghezza
					if (j > _g1->productions[i].left.length)
					{
						/*Copio a partire dalla fine della parte destra della nuova produzione(per poi spostarmi sempre più a sinistra dopo ogni ciclo) 
						  alcuni simboli della parte destra della produzione originaria (qui "diff" viene in nostro soccorso) */
						strcpy((_g->productions[_g->numprod - 1].right.word + strlen(_g->productions[i].right.word) - (j - _g1->productions[i].left.length)), (_g1->productions[i].right.word + strlen(_g1->productions[i].right.word) - diff++));
					}
					/*Se il ciclo ha raggiunto la sua metà, si aggiunge nella parte destra della nuova produzione 
					  alcuni simboli della parte destra della nuova produzione*/
					else if (j == _g1->productions[i].left.length)
					{
						_g->productions[_g->numprod - 1].right.word[j - 1] = NTTable.buffer[0];
						strcat(_g->productions[_g->numprod - 1].right.word, (_g1->productions[i].right.word + strlen(_g1->productions[i].right.word) - diff++));
						_g->productions[_g->numprod - 1].right.length = strlen(_g->productions[_g->numprod - 1].right.word);
					}
					else
						//Sosituisco ad ogni ciclo ogni NT con uno libero
						_g->productions[_g->numprod -1 ].right.word[j - 1] = NTTable.buffer[0];

					/*Si copia la parte destra dell'ultima produzione nella parte sinistra della produzione successiva soltanto se
					  non si sta copiando la parte destra della produzione originaria */
					if (strcmp(_g->productions[_g->numprod - 1].right.word, _g1->productions[i].right.word) != 0)
					{


						strcpy(_g->productions[_g->numprod].left.word, _g->productions[_g->numprod - 1].right.word);
						strcpy(_g->productions[_g->numprod].right.word, _g->productions[_g->numprod].left.word);

						_g->productions[_g->numprod].left.length = strlen(_g->productions[_g->numprod - 1].right.word);
						_g->productions[_g->numprod].right.length = strlen(_g->productions[_g->numprod].left.word);
						_g->numprod++;

						AdjustTableNT(&NTTable, _g);
					}
				}

			}
			//Altrimenti copio il simbolo iniziale nella nuova grammatica
			else
			{
				strcpy(_g->productions[_g->numprod].left.word, _g1->productions[i].left.word);
				_g->productions[_g->numprod].left.length = _g1->productions[i].left.length;

				strcpy(_g->productions[_g->numprod].right.word, _g1->productions[i].right.word);
				_g->productions[_g->numprod].right.length = _g1->productions[i].right.length;

				_g->numprod++;
			}
		}
	}
	else
	{
		ErrorManager(NO_TRANSF, NULL, 0);
		_g = NULL;
	}
		

	return _g;
}

























