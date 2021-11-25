#include "Parquet/ParserCombinator/Sequence/SeqBasis.h"

static SeqAnswer_t Err(Seq_t *seq, Processor_t *p) {
	return (SeqAnswer_t){
		.Reply			= Reply.Err,
		.Precipitate	= seq->Duplicate(seq),
		.Subsequent		= seq,
		.Processor		= p,
	};
}

static SeqAnswer_t Ok(Seq_t *seq, Processor_t *p) {
	return (SeqAnswer_t){
		.Reply 			= Reply.Ok,
		.Precipitate	= seq->Duplicate(seq),
		.Subsequent		= seq,
		.Processor		= p
	};
}

static SeqAnswer_t OkRead1(Seq_t *seq, Processor_t *p) {
	return (SeqAnswer_t){
		.Reply			= Reply.Ok,
		.Precipitate	= Seq.GetHeadSeq(seq),
		.Subsequent		= Seq.GetTailSeq(seq),
		.Processor		= p
	};
}

_SeqBasis SeqBasis = {
	.Err		= Err,
	.Ok			= Ok,
	.OkRead1	= OkRead1,
};
