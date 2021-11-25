#pragma once

#include <Parquet.h>

#include "MPLLexer.h"

typedef struct {
	SeqAnswer_t (* SeqParser_Program)(List_t *seq, Processor_t *p);
} _MPLParser;

extern _MPLParser MPLParser;
