#pragma once

#include <Scraper.h>

#include "Token.h"

typedef struct {
	bool Succeeded;
	int32_t ErrorLine;
	String_t *Precipitate;
	String_t *Subsequent;
} ParseResult_t;

typedef struct {
	ParseResult_t (* Execute)(String_t *code);
} _MPLParser;

extern _MPLParser MPLParser;
