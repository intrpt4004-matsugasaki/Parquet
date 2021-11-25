#pragma once

#include "Parquet/Base/Seq.h"
#include "Parquet/ParserCombinator/Sequence/SeqParser.h"

typedef struct {
	SeqAnswer_t (* Err)(Seq_t *, Processor_t *);
	SeqAnswer_t (* Ok)(Seq_t *, Processor_t *);
	SeqAnswer_t (* OkRead1)(Seq_t *, Processor_t *);
} _SeqBasis;

extern _SeqBasis SeqBasis;
