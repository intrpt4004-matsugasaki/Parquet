#pragma once

#include "Parquet/Base/String.h"
#include "Parquet/ParserCombinator/Parser.h"

typedef struct {
	Answer_t (* Invoke)(
		Answer_t (* parser)(String_t *, Processor_t *),
		String_t *, Processor_t *);

	Answer_t (* Parse)(
		Answer_t (* parser)(String_t *, Processor_t *),
		String_t *);

	void (* InvokeTest)(
		Answer_t (* parser)(String_t *, Processor_t *),
		String_t *, Processor_t *);

	void (* ParseTest)(
		Answer_t (* parser)(String_t *, Processor_t *),
		String_t *);
} _Invoker;

extern _Invoker Invoker;
