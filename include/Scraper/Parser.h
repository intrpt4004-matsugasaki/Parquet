#pragma once

#include <ctype.h>

#include "Scraper/String.h"
#include "Scraper/List.h"

#include "Scraper/Result.h"
#include "Scraper/Basis.h"
#include "Scraper/Combinator.h"

typedef struct {
	Result_t (* OneOf)(String_t *list, String_t *);
	Result_t (* NoneOf)(String_t *list, String_t *);
	Result_t (* Space)(String_t *);
	Result_t (* Spaces0)(String_t *);
	Result_t (* Spaces1)(String_t *);
	Result_t (* LF)(String_t *);
	Result_t (* CRLF)(String_t *);
	Result_t (* EndOfLine)(String_t *);
	Result_t (* Tab)(String_t *);
	Result_t (* Upper)(String_t *);
	Result_t (* Lower)(String_t *);
	Result_t (* AlphaNum)(String_t *);
	Result_t (* Letter)(String_t *);
	Result_t (* Digit)(String_t *);
	Result_t (* HexDigit)(String_t *);
	Result_t (* OctDigit)(String_t *);
	Result_t (* Char)(uint8_t c, String_t *);
	Result_t (* Any)(String_t *);
	Result_t (* Satisfy)(bool (* judge)(uint8_t c), String_t *);
} _Char;

typedef struct {
	Result_t (* Match)(String_t *pattern, String_t *s);
	Result_t (* UnMatch)(String_t *pattern, String_t *s);
	Result_t (* OneOf)(List_t *list, String_t *);
} _String_;

typedef struct {
	_Char Char;
	_String_ String;
} _Parser;

extern _Parser Parser;
