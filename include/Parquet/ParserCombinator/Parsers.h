#pragma once

#include <stdint.h>
#include <ctype.h>

#include "Parquet/Base/String.h"
#include "Parquet/Base/List.h"
#include "Parquet/ParserCombinator/Parser.h"
#include "Parquet/ParserCombinator/Basis.h"
#include "Parquet/ParserCombinator/Combinator.h"

typedef struct {
	Answer_t (* Match)(uint8_t c, String_t *, Processor_t *);
	Answer_t (* UnMatch)(uint8_t c, String_t *, Processor_t *);
	Answer_t (* OneOf)(String_t *cs, String_t *, Processor_t *);
	Answer_t (* NoneOf)(String_t *cs, String_t *, Processor_t *);

	Answer_t (* Upper)(String_t *, Processor_t *);
	Answer_t (* Lower)(String_t *, Processor_t *);
	Answer_t (* AlphaNum)(String_t *, Processor_t *);
	Answer_t (* Letter)(String_t *, Processor_t *);
	Answer_t (* Digit)(String_t *, Processor_t *);
	Answer_t (* HexDigit)(String_t *, Processor_t *);
	Answer_t (* OctDigit)(String_t *, Processor_t *);
	Answer_t (* Any)(String_t *, Processor_t *);
	Answer_t (* Satisfy)(
		bool (* judge)(uint8_t c),
		String_t *, Processor_t *);

	Answer_t (* Space)(String_t *, Processor_t *);
	Answer_t (* Spaces0)(String_t *, Processor_t *);
	Answer_t (* Spaces1)(String_t *, Processor_t *);
	Answer_t (* LF)(String_t *, Processor_t *);
	Answer_t (* CRLF)(String_t *, Processor_t *);
	Answer_t (* EndOfLine)(String_t *, Processor_t *);
	Answer_t (* Tab)(String_t *, Processor_t *);
} _Char;

typedef struct {
	Answer_t (* Match)(String_t *pat, String_t *, Processor_t *);
	Answer_t (* UnMatch)(String_t *pat, String_t *, Processor_t *);
	Answer_t (* OneOf)(List_t *pats, String_t *, Processor_t *);
	Answer_t (* NoneOf)(List_t *pats, String_t *, Processor_t *);
} _String_;

typedef struct {
	_Char Char;
	_String_ String;
} _Parsers;

extern _Parsers Parsers;
