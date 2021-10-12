#pragma once

#include <Scraper.h>

#include "Token.h"

typedef struct {
	List_t *(* Execute)(String_t *code);
} _MPLLexer;

extern _MPLLexer MPLLexer;
