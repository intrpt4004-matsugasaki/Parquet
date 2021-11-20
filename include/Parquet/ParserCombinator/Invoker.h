#pragma once

#include "Parquet/Base/String.h"
#include "Parquet/ParserCombinator/Result.h"

typedef struct {
	Result_t (* Parse)(Result_t (* parser)(String_t *), String_t *);
	void (* Invoke)(Result_t (* parser)(String_t *), String_t *);
	void (* ParseTest)(Result_t (* parser)(String_t *), String_t *);
} _Invoker;

extern _Invoker Invoker;
