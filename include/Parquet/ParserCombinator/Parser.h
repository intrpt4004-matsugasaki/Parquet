#pragma once

#include <ctype.h>

#include "Parquet/Base/String.h"
#include "Parquet/Base/List.h"
#include "Parquet/ParserCombinator/Result.h"
#include "Parquet/ParserCombinator/Basis.h"
#include "Parquet/ParserCombinator/Combinator.h"

typedef struct {
	Result_t (* Match)(uint8_t c, String_t *);
	Result_t (* UnMatch)(uint8_t c, String_t *);
	Result_t (* OneOf)(String_t *list, String_t *);
	Result_t (* NoneOf)(String_t *list, String_t *);

	Result_t (* Upper)(String_t *);
	Result_t (* Lower)(String_t *);
	Result_t (* AlphaNum)(String_t *);
	Result_t (* Letter)(String_t *);
	Result_t (* Digit)(String_t *);
	Result_t (* HexDigit)(String_t *);
	Result_t (* OctDigit)(String_t *);
	Result_t (* Any)(String_t *);
	Result_t (* Satisfy)(bool (* judge)(uint8_t c), String_t *);

	Result_t (* Space)(String_t *);
	Result_t (* Spaces0)(String_t *);
	Result_t (* Spaces1)(String_t *);
	Result_t (* LF)(String_t *);
	Result_t (* CRLF)(String_t *);
	Result_t (* EndOfLine)(String_t *);
	Result_t (* Tab)(String_t *);
} _Char;

typedef struct {
	Result_t (* Match)(String_t *pat, String_t *s);
	Result_t (* UnMatch)(String_t *pat, String_t *s);
	Result_t (* OneOf)(List_t *list, String_t *);
} _String_;

typedef struct {
	_Char Char;
	_String_ String;
} _Parser;

extern _Parser Parser;
