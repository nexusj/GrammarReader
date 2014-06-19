/********************************************************************
	created:	2014/06/19
	created:	19:6:2014   12:28
	filename: 	C:\Users\NexusJ\Documents\GitHub\GrammarReader\src\Extensions.h
	file path:	C:\Users\NexusJ\Documents\GitHub\GrammarReader\src
	file base:	Extensions
	file ext:	h
	author:		Vito Palumbo (aka NexusJ)
	
	purpose:	Questo è un progetto universitario per l'esame di teoria dei linguaggi formali. 
				Esso fornisce un GrammarReader con le seguenti caratteristiche:
				-Verificare a quale gerarchia di Chomsky appartiene la grammatica;
				-Unire,concatenare e iterare le grammatiche;
				-Convertire le produzioni da monotone a CS;
				-ErrorManager (ti mostra gli errori contenuti in ogni produzione);
				-Controllo dell'esistenza dell'init symbol e dei NT nella parte sinistra
*********************************************************************/


#ifndef _EXTENSIONS_H_
#define  _EXTENSIONS_H_

/* Controlla se si sta usando VISUAL STUDIO.
In caso positivo si disattivano i warning riguardo alcune funzioni deprecate(printf,scanf,..) */
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS 
#endif

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Grammar.h"

#define INIT_SYMBOL "S"
#define BUFFER_TABLE_SIZE 26

/* Struttura che contiene gli NT non ancora usati */
struct  _Table
{
    Symbol buffer[BUFFER_TABLE_SIZE];
	unsigned length;
	
};

/* Indice usato per i pedici dei simboli iniziali. */
unsigned offset;





//************************************
// Brief:	  Controlla l'esistenza di NT nella parte sinistra
// Method:    CheckNonTerminal
// Returns:   1 se vero. 0 se falso
// Parameter: Production * p : produzione di una grammatica
//************************************
int CheckNonTerminal(Production* p);


//************************************
// Brief:	  Controlla l'esistenza del simbolo iniziale
// Method:    CheckInitSymbol
// Returns:   1 se vero. 0 se falso
// Parameter: Grammar * g : grammatica in cui verificare l'esistenza dell'init symbol.
//************************************
int CheckInitSymbol(Grammar* g);

//************************************
// Brief:	  Verifica se la grammatica g è CF
// Method:    GrammarCF
// Returns:   1 se vero. 0 se falso
// Parameter: Grammar * g : grammatica in cui fare il controllo
//************************************
int GrammarCF(Grammar* g);

//************************************
// Brief:	  Verifica se la grammatica g è CS
// Method:    GrammarCS
// Returns:	  1 se vero. 0 se falso
// Parameter: Grammar * g : grammatica in cui fare il controllo
//************************************
int GrammarCS(Grammar* g);


//************************************
// Brief:	  Verifica se la grammatica g è monotona
// Method:    IsMonotonic
// Returns:   1 se vero. 0 se falso
// Parameter: Grammar * g : grammatica in cui fare il controllo
//************************************
int IsMonotonic(Grammar* g);


//************************************
// Brief:     Verifica se la grammatica g è lineare destra
// Method:    IsRightLinear
// Returns:   1 se vero. 0 se falso
// Parameter: Grammar * g : grammatica in cui fare il controllo
//************************************
int IsRightLinear(Grammar* g);


//************************************
// Brief:     Funzione che gestisce gli errori incontrati durante il caricamento della grammatica
// Method:    ErrorManager
// Returns:   void
// Parameter: enum States _type : tipo di errore
// Parameter: Production * p : produzione in cui è stato trovato l'errore
// Parameter: int _line : linea(o numero di produzione) in cui compare l'errore 
//************************************
void ErrorManager(enum States _type, Production* p, int _line);


//************************************
// Brief:	  Elimina una produzione dalla grammatica
// Method:    DeleteProduction
// Returns:   void
// Parameter: Grammar * g : grammatica dalla quale eliminare la produzione
// Parameter: int _index : numero della produzione da eliminare
//************************************
void DeleteProduction(Grammar* g ,int _index);


//************************************
// Brief:     Stampa a video gli errori
// Method:    DrawErrors
// Returns:   void
// Parameter: Errors _vector : struttura che contiene gli errori
// Parameter: Grammar * g : grammatica in cui compare l'errore
//************************************
void DrawErrors(Errors _vector,Grammar* g);


//************************************
// Brief:     Funzione che carica da file la grammatica g e stampa a video le sue produzioni(se _draw è vero)
// Method:    LoadGrammar
// Returns:   0 se non ci sono stati errori.Altrimenti -1
// Parameter: const char * _path : file della grammatica
// Parameter: Grammar * g : variabile in cui memorizzare la grammatica
// Parameter: bool _draw : stampare a video la grammatica?
//************************************
int LoadGrammar(const char* _path, Grammar* g, bool _draw);


//************************************
// Brief:     Date due grammatiche controlla se hanno NT in comune(con opportuna sostituzione).
// Method:    CheckCommonNT
// Returns:   void
// Parameter: Grammar * _g1 : prima grammatica
// Parameter: Grammar * _g2 : seconda grammatica
//************************************
void CheckCommonNT(Grammar* _g1, Grammar* _g2);


//************************************
// Brief:     Date due grammatiche restituisce  la loro unione(salvata in _g)
// Method:    JoinGrammar
// Returns:   Grammar*
// Parameter: Grammar * _g1 : prima grammatica
// Parameter: Grammar * _g2 : seconda grammatica
// Parameter: Grammar * _g  : grammatica ottenuta dall'unione delle precedenti
//************************************
Grammar* JoinGrammar(Grammar* _g1, Grammar* _g2, Grammar* _g);


//************************************
// Brief:	  Date due grammatiche restituisce  la loro concatenazione(salvata in _g)
// Method:    ConcatenateGrammar
// Returns:   Grammar*
// Parameter: Grammar * _g1 : prima grammatica
// Parameter: Grammar * _g2 : seconda grammatica
// Parameter: Grammar * _g  : grammatica ottenuta dalla concatenazione delle precedenti
//************************************
Grammar* ConcatenateGrammar(Grammar* _g1, Grammar* _g2,Grammar* _g);


//************************************
// Brief:     Data la grammatica _g1 ne restituisce la grammatica iterata
// Method:    IterateGrammar
// Returns:   Grammar*
// Parameter: Grammar * _g1 : prima grammatica
// Parameter: Grammar * _g  : grammatica iterata
//************************************
Grammar* IterateGrammar(Grammar* _g1, Grammar* _g);


//************************************
// Brief:     Cambia un NT contenuto nella grammatica g
// Method:    ChangeNT
// Returns:   void
// Parameter: Grammar * g : grammatica in cui sostituire il NT
// Parameter: const char * _s : NT  da sostituire
//************************************
void ChangeNT(Grammar* g, const char* _s);


//************************************
// Brief:     Effettua un shift sinistro del vettore _vector.
// Method:    ShifLVectorCh
// Returns:   void
// Parameter: char * _vector : vettore da shiftare
// Parameter: int _index : indice da cui iniziare
// Parameter: int * _lenght : lunghezza dello shift
//************************************
void ShifLVectorCh(char* _vector, int _index, int*_lenght);


//************************************
// Brief:     Effettua un shift destro della grammatica.
// Method:    ShiftRVectorP
// Returns:   void
// Parameter: Grammar * g : grammatica da shiftare
// Parameter: int _index  : indice da cui iniziare
//************************************
void ShiftRVectorP(Grammar* g, int _index);


//************************************
// Brief:     Ridimensiona la tabella che contiene gli NT liberi
// Method:    AdjustTableNT
// Returns:   void
// Parameter: struct _Table * _table : tabella dei NT liberi
// Parameter: Grammar * _g : grammatica da cui fare il confronto dei suoi NT con quelli liberi
//************************************
void AdjustTableNT(struct _Table* _table, Grammar* _g);


//************************************
// Brief:     Aggiunge una produzione
// Method:    AddProduction
// Returns:   void
// Parameter: Grammar * g : grammatica in cui inserire la produzione
// Parameter: char * _left : parte sinistra della produzione
// Parameter: char * _right : parte destra della produzione
// Parameter: int _index : indice in cui inserire la produzione
//************************************
void AddProduction(Grammar* g, char* _left, char* _right,int _index);


//************************************
// Brief:     Converte una grammatica monotona in una CS
// Method:    ConvertToCS
// Returns:   Grammar*
// Parameter: Grammar * _g1 : grammatica da convertire
// Parameter: Grammar * _g : grammatica convertita
//************************************
Grammar* ConvertToCS(Grammar* _g1, Grammar* _g);



#endif


