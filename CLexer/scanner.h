/********************************************************************
	created:	2014/06/19
	created:	19:6:2014   12:26
	filename: 	C:\Users\NexusJ\Documents\GitHub\GrammarReader\CLexer\scanner.h
	file path:	C:\Users\NexusJ\Documents\GitHub\GrammarReader\CLexer
	file base:	scanner
	file ext:	h
	author:		Vito Palumbo (aka NexusJ)
	
	purpose:	Questo progetto fornisce un lexer per un linguaggio C-like (riconosce quasi tutto del C)
*********************************************************************/

#ifndef _SCANNER_H
#define _SCANNER_H
#define _CRT_SECURE_NO_WARNINGS
#define MAX_STRING_LENGTH 40
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef char String[MAX_STRING_LENGTH + 1];

typedef enum
{
	IDENTIFIER,
	KEYWORD,
	COMMENT,
	LEFT_PAR,
	RIGHT_PAR,
	START_BLOCK,
	END_BLOCK,
	PLUS,
	MINUS,
	ASTERIX,
	SLASH,
	EQUAL,
	SEMICOLON,
	DOT,
	COMMA,
	GREATER,
	GREATER_OR_EQUAL,
	LESS,
	LESS_OR_EQUAL,
	DIFFERENT,
	COLON,
	ASSIGNMENT,
	INTEGER,
	FLOAT,
	DOUBLE,
	LONG,
	STRING,
	ERROR
} TokenType;

typedef struct
{
	TokenType type;
	String value;
} Token;

int isKeyword(String s);
int getToken(FILE* src, Token* tkn);


#endif