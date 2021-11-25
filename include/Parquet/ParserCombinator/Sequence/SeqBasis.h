#pragma once

#include "Parquet/Base/List.h"
#include "Parquet/ParserCombinator/Sequence/SeqParser.h"

typedef struct {
	SeqAnswer_t (* Err)(List_t *, Processor_t *);
	SeqAnswer_t (* Ok)(List_t *, Processor_t *);
	SeqAnswer_t (* OkRead1)(List_t *, Processor_t *);
} _SeqBasis;

extern _SeqBasis SeqBasis;
