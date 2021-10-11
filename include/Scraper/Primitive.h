#pragma once

#include <ctype.h>

#include "Scraper/String.h"
#include "Scraper/List.h"

#include "Scraper/Parse.h"
#include "Scraper/Parser.h"

typedef struct {
	Parse (* OneOf)(String_t *list, String_t *);
	Parse (* NoneOf)(String_t *list, String_t *);
	//Parse (* Spaces)(String_t *);
	Parse (* Space)(String_t *);
	Parse (* LF)(String_t *);
	Parse (* CRLF)(String_t *);
	Parse (* EndOfLine)(String_t *);
	Parse (* Tab)(String_t *);
	Parse (* Upper)(String_t *);
	Parse (* Lower)(String_t *);
	Parse (* AlphaNum)(String_t *);
	Parse (* Letter)(String_t *);
	Parse (* Digit)(String_t *);
	Parse (* HexDigit)(String_t *);
	Parse (* OctDigit)(String_t *);
	Parse (* Char)(uint8_t c, String_t *);
	Parse (* Any)(String_t *);
	Parse (* Satisfy)(bool (* judge)(uint8_t c), String_t *);
} _Char;

typedef struct {
	Parse (* Match)(String_t *pattern, String_t *s);
	Parse (* OneOf)(List_t *list, String_t *);
} _String_;

typedef struct {
	_Char Char;
	_String_ String;
} _Primitive;

extern _Primitive Primitive;
