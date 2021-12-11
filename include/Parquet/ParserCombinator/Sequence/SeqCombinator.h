#pragma once

#include "Parquet/Base/Seq.h"
#include "Parquet/ParserCombinator/Sequence/SeqParser.h"
#include "Parquet/ParserCombinator/Sequence/SeqBasis.h"

typedef struct {
	/* >> */
	SeqAnswer_t (* Bind)(
		SeqAnswer_t (* seqParser1)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser2)(Seq_t *, Processor_t *),
		Seq_t *, Processor_t *);

	SeqAnswer_t (* Bind3)(
		SeqAnswer_t (* seqParser1)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser2)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser3)(Seq_t *, Processor_t *),
		Seq_t *, Processor_t *);

	SeqAnswer_t (* Bind4)(
		SeqAnswer_t (* seqParser1)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser2)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser3)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser4)(Seq_t *, Processor_t *),
		Seq_t *, Processor_t *);

	SeqAnswer_t (* Bind5)(
		SeqAnswer_t (* seqParser1)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser2)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser3)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser4)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser5)(Seq_t *, Processor_t *),
		Seq_t *, Processor_t *);

	SeqAnswer_t (* Bind6)(
		SeqAnswer_t (* seqParser1)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser2)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser3)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser4)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser5)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser6)(Seq_t *, Processor_t *),
		Seq_t *, Processor_t *);

	/* / */
	SeqAnswer_t (* Choise)(
		SeqAnswer_t (* seqParser1)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser2)(Seq_t *, Processor_t *),
		Seq_t *, Processor_t *);

	SeqAnswer_t (* Choise3)(
		SeqAnswer_t (* seqParser1)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser2)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser3)(Seq_t *, Processor_t *),
		Seq_t *, Processor_t *);

	SeqAnswer_t (* Choise4)(
		SeqAnswer_t (* seqParser1)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser2)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser3)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser4)(Seq_t *, Processor_t *),
		Seq_t *, Processor_t *);

	SeqAnswer_t (* Choise5)(
		SeqAnswer_t (* seqParser1)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser2)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser3)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser4)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser5)(Seq_t *, Processor_t *),
		Seq_t *, Processor_t *);

	SeqAnswer_t (* Choise6)(
		SeqAnswer_t (* seqParser1)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser2)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser3)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser4)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser5)(Seq_t *, Processor_t *),
		SeqAnswer_t (* seqParser6)(Seq_t *, Processor_t *),
		Seq_t *, Processor_t *);

	/* * */
	SeqAnswer_t (* Many0)(
		SeqAnswer_t (* seqParser)(Seq_t *, Processor_t *),
		Seq_t *, Processor_t *);

	/* + */
	SeqAnswer_t (* Many1)(
		SeqAnswer_t (* seqParser)(Seq_t *, Processor_t *),
		Seq_t *, Processor_t *);

	/* ? */
	SeqAnswer_t (* Optional)(
		SeqAnswer_t (* seqParser)(Seq_t *, Processor_t *),
		Seq_t *, Processor_t *);

	/* & */
	SeqAnswer_t (* Predict)(
		SeqAnswer_t (* seqParser)(Seq_t *, Processor_t *),
		Seq_t *, Processor_t *);

	/* ! */
	SeqAnswer_t (* PredictNot)(
		SeqAnswer_t (* seqParser)(Seq_t *, Processor_t *),
		Seq_t *, Processor_t *);

} _SeqCombinator;

extern _SeqCombinator SeqCombinator;
