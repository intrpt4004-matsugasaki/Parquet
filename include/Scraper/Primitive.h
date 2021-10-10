#pragma once

#include "Scraper/Parser.h"

typedef struct {
	Parse (* AnyChar)(String_t *);
	Parse (* Lower)(String_t *);
	Parse (* Upper)(String_t *);
	Parse (* AlphaNum)(String_t *);
	Parse (* Char)(String_t *);
} _Char;

typedef struct {
	_Char Char;
} _Primitive;

extern _Primitive Primitive;
