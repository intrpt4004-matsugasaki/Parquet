#pragma once

#include "Scraper/Parse.h"

typedef struct {
	Parse (* makeErr)();
	Parse (* makeOkChar)(String_t *);

	void (* ParseTest)(Parse (* parser)(String_t *), String_t *);
} _Parser;

extern _Parser Parser;
