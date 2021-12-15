#pragma once

#include "Parquet/ParserCombinator/Sequence/Seq.h"
#include "Parquet/ParserCombinator/Parser.h"
#include "Parquet/ParserCombinator/Sequence/SeqParser.h"

typedef struct {
	SeqAnswer_t (* Invoke)(
		SeqAnswer_t (* seqParser)(Seq_t *, Processor_t *),
		Seq_t *, Processor_t *);

	SeqAnswer_t (* Parse)(
		SeqAnswer_t (* seqParser)(Seq_t *, Processor_t *),
		Seq_t *);

	void (* InvokeTest)(
		SeqAnswer_t (* seqParser)(Seq_t *, Processor_t *),
		Seq_t *, Processor_t *);

	void (* ParseTest)(
		SeqAnswer_t (* seqParser)(Seq_t *, Processor_t *),
		Seq_t *);
} _SeqInvoker;

extern _SeqInvoker SeqInvoker;
