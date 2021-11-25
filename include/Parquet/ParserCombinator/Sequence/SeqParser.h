#pragma once

#include "Parquet/Base/Seq.h"
#include "Parquet/ParserCombinator/Parser.h"

typedef struct {
	__Reply Reply;

	Seq_t *Precipitate;
	Seq_t *Subsequent;

	Processor_t *Processor;
} SeqAnswer_t;
