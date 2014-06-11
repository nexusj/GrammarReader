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
	INC,
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