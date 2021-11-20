#pragma once

#include "Scraper/String.h"

#include "Scraper/Result.h"
#include "Scraper/Basis.h"

typedef struct {
	Result_t (* Bind)(
		Result_t (* fst)(String_t *),
		Result_t (* snd)(String_t *),
		String_t *);

	Result_t (* Bind3)(
		Result_t (* fst)(String_t *),
		Result_t (* snd)(String_t *),
		Result_t (* trd)(String_t *),
		String_t *);

	Result_t (* Bind4)(
		Result_t (* fst)(String_t *),
		Result_t (* snd)(String_t *),
		Result_t (* trd)(String_t *),
		Result_t (* fth)(String_t *),
		String_t *);

	Result_t (* Bind5)(
		Result_t (* fst)(String_t *),
		Result_t (* snd)(String_t *),
		Result_t (* trd)(String_t *),
		Result_t (* fth)(String_t *),
		Result_t (* fif)(String_t *),
		String_t *);

	Result_t (* Bind6)(
		Result_t (* fst)(String_t *),
		Result_t (* snd)(String_t *),
		Result_t (* trd)(String_t *),
		Result_t (* fth)(String_t *),
		Result_t (* fif)(String_t *),
		Result_t (* sth)(String_t *),
		String_t *);

	Result_t (* Choise)(
		Result_t (* fst)(String_t *),
		Result_t (* snd)(String_t *),
		String_t *);

	Result_t (* Choise3)(
		Result_t (* fst)(String_t *),
		Result_t (* snd)(String_t *),
		Result_t (* trd)(String_t *),
		String_t *);

	Result_t (* Choise4)(
		Result_t (* fst)(String_t *),
		Result_t (* snd)(String_t *),
		Result_t (* trd)(String_t *),
		Result_t (* fth)(String_t *),
		String_t *);

	Result_t (* Choise5)(
		Result_t (* fst)(String_t *),
		Result_t (* snd)(String_t *),
		Result_t (* trd)(String_t *),
		Result_t (* fth)(String_t *),
		Result_t (* fif)(String_t *),
		String_t *);

	Result_t (* Choise6)(
		Result_t (* fst)(String_t *),
		Result_t (* snd)(String_t *),
		Result_t (* trd)(String_t *),
		Result_t (* fth)(String_t *),
		Result_t (* fif)(String_t *),
		Result_t (* sth)(String_t *),
		String_t *);

	Result_t (* Many0)(Result_t (* parser)(String_t *), String_t *);
	Result_t (* Many1)(Result_t (* parser)(String_t *), String_t *);

	Result_t (* Possibly)(Result_t (* parser)(String_t *), String_t *);
} _Combinator;

extern _Combinator Combinator;
