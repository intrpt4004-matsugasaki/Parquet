#pragma once

#include "Parquet/Base/String.h"
#include "Parquet/ParserCombinator/Result.h"

typedef struct {
	Result_t (* Err)(String_t *);
	Result_t (* Ok)(String_t *);
	Result_t (* OkRead1)(String_t *);
} _Basis;

extern _Basis Basis;
