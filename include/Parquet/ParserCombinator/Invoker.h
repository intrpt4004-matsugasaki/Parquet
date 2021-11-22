#pragma once

#include "Parquet/Base/String.h"
#include "Parquet/ParserCombinator/Parser.h"

typedef struct {
	Answer_t (* Parse)(
		Answer_t (* parser)(String_t *, Processor_t),
		String_t *, Processor_t);

	void (* Invoke)(
		Answer_t (* parser)(String_t *, Processor_t),
		String_t *, Processor_t);

	void (* ParseTest)(
		Answer_t (* parser)(String_t *, Processor_t),
		String_t *, Processor_t);
} _Invoker;

extern _Invoker Invoker;
