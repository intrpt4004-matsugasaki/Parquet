#include "Parquet/ParserCombinator/Sequence/SeqBasis.h"

static SeqAnswer_t Err(List_t *seq, Processor_t *p) {
	return (SeqAnswer_t){
		.Reply			= Reply.Err,
		.Precipitate	= seq->GetListWhoseBasisWasDuplicated(seq),
		.Subsequent		= seq,
		.Processor		= p,
	};
}

static SeqAnswer_t Ok(List_t *seq, Processor_t *p) {
	return (SeqAnswer_t){
		.Reply 			= Reply.Ok,
		.Precipitate	= seq->GetListWhoseBasisWasDuplicated(seq),
		.Subsequent		= seq,
		.Processor		= p
	};
}

static SeqAnswer_t OkRead1(List_t *seq, Processor_t *p) {
	return (SeqAnswer_t){
		.Reply			= Reply.Ok,
		.Precipitate	= List.GetHeadList(seq),
		.Subsequent		= List.GetTailList(seq),
		.Processor		= p
	};
}

_SeqBasis SeqBasis = {
	.Err		= Err,
	.Ok			= Ok,
	.OkRead1	= OkRead1,
};
