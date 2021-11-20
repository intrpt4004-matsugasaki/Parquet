#pragma once

#include <Parquet.h>

#include "Token.h"

typedef struct {
	bool Succeeded;
	int32_t ErrorLine;
	String_t *Precipitate;
	String_t *Subsequent;
	List_t *TokenList;
} LexResult_t;

typedef struct {
	LexResult_t (* Execute)(String_t *code);
} _MPLLexer;

extern _MPLLexer MPLLexer;
