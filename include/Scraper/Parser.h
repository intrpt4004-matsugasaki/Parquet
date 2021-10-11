#pragma once

#include "Scraper/Parse.h"

typedef struct {
	/* Maker */
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

	Parse (* Bind5)(
		Parse (* fst)(String_t *),
		Parse (* snd)(String_t *),
		Parse (* trd)(String_t *),
		Parse (* fth)(String_t *),
		Parse (* fif)(String_t *),
		String_t *);

	Parse (* Bind6)(
		Parse (* fst)(String_t *),
		Parse (* snd)(String_t *),
		Parse (* trd)(String_t *),
		Parse (* fth)(String_t *),
		Parse (* fif)(String_t *),
		Parse (* sth)(String_t *),
		String_t *);

	Parse (* Choise)(
		Parse (* fst)(String_t *),
		Parse (* snd)(String_t *),
		String_t *);

	Parse (* Choise3)(
		Parse (* fst)(String_t *),
		Parse (* snd)(String_t *),
		Parse (* trd)(String_t *),
		String_t *);

	Parse (* Choise4)(
		Parse (* fst)(String_t *),
		Parse (* snd)(String_t *),
		Parse (* trd)(String_t *),
		Parse (* fth)(String_t *),
		String_t *);

	Parse (* Choise5)(
		Parse (* fst)(String_t *),
		Parse (* snd)(String_t *),
		Parse (* trd)(String_t *),
		Parse (* fth)(String_t *),
		Parse (* fif)(String_t *),
		String_t *);

	Parse (* Choise6)(
		Parse (* fst)(String_t *),
		Parse (* snd)(String_t *),
		Parse (* trd)(String_t *),
		Parse (* fth)(String_t *),
		Parse (* fif)(String_t *),
		Parse (* sth)(String_t *),
		String_t *);

	Parse (* Many0)(Parse (* parser)(String_t *), String_t *);
	Parse (* Many1)(Parse (* parser)(String_t *), String_t *);

	/* Invoker/Tester */
	void (* Invoke)(Parse (* parser)(String_t *), String_t *);
	void (* ParseTest)(Parse (* parser)(String_t *), String_t *);
} _Parser;

extern _Parser Parser;
