#pragma once

#include "Scraper/Parse.h"

typedef struct {
	/* Util */
	Parse (* makeErr)(String_t *);
	Parse (* makeOk)(String_t *);
	Parse (* makeOkRead1)(String_t *);

	/* Combinator */
	Parse (* Bind)(
		Parse (* fst)(String_t *),
		Parse (* snd)(String_t *),
		String_t *);

	Parse (* Bind3)(
		Parse (* fst)(String_t *),
		Parse (* snd)(String_t *),
		Parse (* trd)(String_t *),
		String_t *);

	Parse (* Bind4)(
		Parse (* fst)(String_t *),
		Parse (* snd)(String_t *),
		Parse (* trd)(String_t *),
		Parse (* fth)(String_t *),
		String_t *);

	Parse (* Choise)(
		Parse (* left)(String_t *),
		Parse (* right)(String_t *),
		String_t *);

	Parse (* Many)(Parse (* parser)(String_t *), String_t *);
	Parse (* Many1)(Parse (* parser)(String_t *), String_t *);

	/* Tester */
	void (* ParseTest)(Parse (* parser)(String_t *), String_t *);
} _Parser;

extern _Parser Parser;
