#pragma once

#include "Parquet/Base/String.h"
#include "Parquet/ParserCombinator/Result.h"
#include "Parquet/ParserCombinator/Basis.h"

typedef struct {
	Result_t (* Bind)(
		Result_t (* parser1)(String_t *),
		Result_t (* parser2)(String_t *),
		String_t *);

	Result_t (* Bind3)(
		Result_t (* parser1)(String_t *),
		Result_t (* parser2)(String_t *),
		Result_t (* parser3)(String_t *),
		String_t *);

	Result_t (* Bind4)(
		Result_t (* parser1)(String_t *),
		Result_t (* parser2)(String_t *),
		Result_t (* parser3)(String_t *),
		Result_t (* parser4)(String_t *),
		String_t *);

	Result_t (* Bind5)(
		Result_t (* parser1)(String_t *),
		Result_t (* parser2)(String_t *),
		Result_t (* parser3)(String_t *),
		Result_t (* parser4)(String_t *),
		Result_t (* parser5)(String_t *),
		String_t *);

	Result_t (* Bind6)(
		Result_t (* parser1)(String_t *),
		Result_t (* parser2)(String_t *),
		Result_t (* parser3)(String_t *),
		Result_t (* parser4)(String_t *),
		Result_t (* parser5)(String_t *),
		Result_t (* parser6)(String_t *),
		String_t *);

	Result_t (* Choise)(
		Result_t (* parser1)(String_t *),
		Result_t (* parser2)(String_t *),
		String_t *);

	Result_t (* Choise3)(
		Result_t (* parser1)(String_t *),
		Result_t (* parser2)(String_t *),
		Result_t (* parser3)(String_t *),
		String_t *);

	Result_t (* Choise4)(
		Result_t (* parser1)(String_t *),
		Result_t (* parser2)(String_t *),
		Result_t (* parser3)(String_t *),
		Result_t (* parser4)(String_t *),
		String_t *);

	Result_t (* Choise5)(
		Result_t (* parser1)(String_t *),
		Result_t (* parser2)(String_t *),
		Result_t (* parser3)(String_t *),
		Result_t (* parser4)(String_t *),
		Result_t (* parser5)(String_t *),
		String_t *);

	Result_t (* Choise6)(
		Result_t (* parser1)(String_t *),
		Result_t (* parser2)(String_t *),
		Result_t (* parser3)(String_t *),
		Result_t (* parser4)(String_t *),
		Result_t (* parser5)(String_t *),
		Result_t (* parser6)(String_t *),
		String_t *);

	Result_t (* Many0)(Result_t (* parser)(String_t *), String_t *);
	Result_t (* Many1)(Result_t (* parser)(String_t *), String_t *);

	Result_t (* Possibly)(Result_t (* parser)(String_t *), String_t *);
} _Combinator;

extern _Combinator Combinator;
