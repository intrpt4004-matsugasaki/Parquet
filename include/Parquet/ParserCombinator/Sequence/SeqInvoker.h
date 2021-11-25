#pragma once

#include "Parquet/Base/String.h"
#include "Parquet/ParserCombinator/Sequence/SeqParser.h"

typedef struct {
	SeqAnswer_t (* Invoke)(
		SeqAnswer_t (* seqParser)(List_t *, Processor_t *),
		List_t *, Processor_t *);

	SeqAnswer_t (* Parse)(
		SeqAnswer_t (* seqParser)(List_t *, Processor_t *),
		List_t *);

	void (* InvokeTest)(
		SeqAnswer_t (* seqParser)(List_t *, Processor_t *),
		List_t *, Processor_t *);

	void (* ParseTest)(
		SeqAnswer_t (* seqParser)(List_t *, Processor_t *),
		List_t *);
} _SeqInvoker;

extern _SeqInvoker SeqInvoker;
