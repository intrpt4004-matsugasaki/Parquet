#pragma once

#include <Parquet.h>

typedef struct {
	bool Succeeded;
	String_t *Precipitate;
	String_t *Subsequent;

	int32_t ErrorLine;
	String_t *ErrorMessage;
} ParseResult_t;

typedef struct {
	ParseResult_t (* Execute)(String_t *code);
} _MPLParser;

extern _MPLParser MPLParser;
