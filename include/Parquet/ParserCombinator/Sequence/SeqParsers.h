#pragma once

#include "Parquet/Base/String.h"
#include "Parquet/Base/Seq.h"
#include "Parquet/ParserCombinator/Invoker.h"
#include "Parquet/ParserCombinator/Sequence/SeqParser.h"
#include "Parquet/ParserCombinator/Sequence/SeqBasis.h"
#include "Parquet/ParserCombinator/Sequence/SeqCombinator.h"

typedef struct {
	SeqAnswer_t (* Match)(String_t *pat, Seq_t *, Processor_t *);
	SeqAnswer_t (* UnMatch)(String_t *pat, Seq_t *, Processor_t *);
	SeqAnswer_t (* OneOf)(Seq_t *pats, Seq_t *, Processor_t *);

	SeqAnswer_t (* Complete)(Answer_t (* batch)(String_t *, Processor_t *), Seq_t *, Processor_t *);
} _SeqParsers;

extern _SeqParsers SeqParsers;
