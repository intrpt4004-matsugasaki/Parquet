#pragma once

#include "Parquet/ParserCombinator/Sequence/Seq.h"
#include "Parquet/ParserCombinator/Parser.h"

typedef struct {
	__Reply Reply;

	Seq_t *Precipitate;
	Seq_t *Subsequent;

	Processor_t *Processor;
} SeqAnswer_t;
