#pragma once

#include <ctype.h>

#include "Parquet/Base/String.h"
#include "Parquet/Base/List.h"
#include "Parquet/ParserCombinator/Sequence/SeqParser.h"
#include "Parquet/ParserCombinator/Sequence/SeqBasis.h"
#include "Parquet/ParserCombinator/Sequence/SeqCombinator.h"

typedef struct {
	SeqAnswer_t (* Match)(String_t *pat, List_t *, Processor_t *);
	SeqAnswer_t (* UnMatch)(String_t *pat, List_t *, Processor_t *);
	SeqAnswer_t (* OneOf)(List_t *pats, List_t *, Processor_t *);
} _SeqParsers;

extern _SeqParsers SeqParsers;
