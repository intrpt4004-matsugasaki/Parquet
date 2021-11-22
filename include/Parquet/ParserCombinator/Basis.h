#pragma once

#include "Parquet/Base/String.h"
#include "Parquet/ParserCombinator/Parser.h"

typedef struct {
	Answer_t (* Err)(String_t *);
	Answer_t (* Ok)(String_t *);
	Answer_t (* OkRead1)(String_t *);
} _Basis;

extern _Basis Basis;
