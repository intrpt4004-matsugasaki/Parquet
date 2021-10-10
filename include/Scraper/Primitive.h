#pragma once

#include "Scraper/String.h"

#include "Scraper/Parse.h"
#include "Scraper/Parser.h"

typedef struct {
	Parse (* Any)(String_t *);
	Parse (* Lower)(String_t *);
	Parse (* Upper)(String_t *);
	Parse (* AlphaNum)(String_t *);
	Parse (* Space)(String_t *);
	Parse (* Tab)(String_t *);
	Parse (* Char)(uint8_t, String_t *);
} _Char;

typedef struct {
	_Char Char;
} _Primitive;

extern _Primitive Primitive;
