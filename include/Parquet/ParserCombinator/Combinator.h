#pragma once

#include "Parquet/Base/String.h"
#include "Parquet/ParserCombinator/Parser.h"
#include "Parquet/ParserCombinator/Basis.h"

typedef struct {
	Answer_t (* Bind)(
		Answer_t (* parser1)(String_t *, Processor_t *),
		Answer_t (* parser2)(String_t *, Processor_t *),
		String_t *, Processor_t *);

	Answer_t (* Bind3)(
		Answer_t (* parser1)(String_t *, Processor_t *),
		Answer_t (* parser2)(String_t *, Processor_t *),
		Answer_t (* parser3)(String_t *, Processor_t *),
		String_t *, Processor_t *);

	Answer_t (* Bind4)(
		Answer_t (* parser1)(String_t *, Processor_t *),
		Answer_t (* parser2)(String_t *, Processor_t *),
		Answer_t (* parser3)(String_t *, Processor_t *),
		Answer_t (* parser4)(String_t *, Processor_t *),
		String_t *, Processor_t *);

	Answer_t (* Bind5)(
		Answer_t (* parser1)(String_t *, Processor_t *),
		Answer_t (* parser2)(String_t *, Processor_t *),
		Answer_t (* parser3)(String_t *, Processor_t *),
		Answer_t (* parser4)(String_t *, Processor_t *),
		Answer_t (* parser5)(String_t *, Processor_t *),
		String_t *, Processor_t *);

	Answer_t (* Bind6)(
		Answer_t (* parser1)(String_t *, Processor_t *),
		Answer_t (* parser2)(String_t *, Processor_t *),
		Answer_t (* parser3)(String_t *, Processor_t *),
		Answer_t (* parser4)(String_t *, Processor_t *),
		Answer_t (* parser5)(String_t *, Processor_t *),
		Answer_t (* parser6)(String_t *, Processor_t *),
		String_t *, Processor_t *);

	Answer_t (* Choise)(
		Answer_t (* parser1)(String_t *, Processor_t *),
		Answer_t (* parser2)(String_t *, Processor_t *),
		String_t *, Processor_t *);

	Answer_t (* Choise3)(
		Answer_t (* parser1)(String_t *, Processor_t *),
		Answer_t (* parser2)(String_t *, Processor_t *),
		Answer_t (* parser3)(String_t *, Processor_t *),
		String_t *, Processor_t *);

	Answer_t (* Choise4)(
		Answer_t (* parser1)(String_t *, Processor_t *),
		Answer_t (* parser2)(String_t *, Processor_t *),
		Answer_t (* parser3)(String_t *, Processor_t *),
		Answer_t (* parser4)(String_t *, Processor_t *),
		String_t *, Processor_t *);

	Answer_t (* Choise5)(
		Answer_t (* parser1)(String_t *, Processor_t *),
		Answer_t (* parser2)(String_t *, Processor_t *),
		Answer_t (* parser3)(String_t *, Processor_t *),
		Answer_t (* parser4)(String_t *, Processor_t *),
		Answer_t (* parser5)(String_t *, Processor_t *),
		String_t *, Processor_t *);

	Answer_t (* Choise6)(
		Answer_t (* parser1)(String_t *, Processor_t *),
		Answer_t (* parser2)(String_t *, Processor_t *),
		Answer_t (* parser3)(String_t *, Processor_t *),
		Answer_t (* parser4)(String_t *, Processor_t *),
		Answer_t (* parser5)(String_t *, Processor_t *),
		Answer_t (* parser6)(String_t *, Processor_t *),
		String_t *, Processor_t *);

	Answer_t (* Many0)(
		Answer_t (* parser)(String_t *, Processor_t *),
		String_t *, Processor_t *);

	Answer_t (* Many1)(
		Answer_t (* parser)(String_t *, Processor_t *),
		String_t *, Processor_t *);

	Answer_t (* Possibly)(
		Answer_t (* parser)(String_t *, Processor_t *),
		String_t *, Processor_t *);
} _Combinator;

extern _Combinator Combinator;
