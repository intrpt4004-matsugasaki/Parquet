#pragma once

#include "Parquet/Base/List.h"
#include "Parquet/ParserCombinator/Parser.h"

typedef struct {
	__Reply Reply;

	List_t *Precipitate;
	List_t *Subsequent;

	Processor_t *Processor;
} SeqAnswer_t;
