#include "Parquet/ParserCombinator/Sequence/SeqParsers.h"

static SeqAnswer_t Match(String_t *pat, List_t *seq, Processor_t *p) {
	if (seq->IsEmpty(seq)) return SeqBasis.Err(seq, p);

	String_t *s = List.Get(seq, 0);
	if (!s->Equals(s, pat)) return SeqBasis.Err(seq, p);

	return SeqBasis.OkRead1(seq, p);
}

static SeqAnswer_t UnMatch(String_t *pat, List_t *seq, Processor_t *p) {
	if (seq->IsEmpty(seq)) return SeqBasis.Err(seq, p);

	String_t *s = List.Get(seq, 0);
	if (s->Equals(s, pat)) return SeqBasis.Err(seq, p);

	return SeqBasis.OkRead1(seq, p);
}

static SeqAnswer_t OneOf(List_t *pats, List_t *seq, Processor_t *p) {
	if (seq->IsEmpty(seq)) return SeqBasis.Err(seq, p);

	String_t *s = List.Get(seq, 0);
	for (uint32_t i = 0; i < pats->GetLength(pats); i++)
		if (s->Equals(s, pats->Get(pats, i)))
			return SeqBasis.OkRead1(seq, p);

	return SeqBasis.Err(seq, p);
}

_SeqParsers SeqParsers = {
	.Match			= Match,
	.UnMatch		= UnMatch,
	.OneOf			= OneOf,
};
