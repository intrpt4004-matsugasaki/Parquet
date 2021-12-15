#include "Parquet/ParserCombinator/Sequence/SeqParsers.h"

static SeqAnswer_t Match(String_t *pat, Seq_t *seq, Processor_t *p) {
	if (seq->IsEmpty(seq)) return SeqBasis.Err(seq, p);

	String_t *s = Seq.GetStringiser(seq)(Seq.Get(seq, 0));

	return (s->Equals(s, pat)) ? SeqBasis.OkRead1(seq, p) : SeqBasis.Err(seq, p);
}

static SeqAnswer_t UnMatch(String_t *pat, Seq_t *seq, Processor_t *p) {
	if (seq->IsEmpty(seq)) return SeqBasis.Err(seq, p);

	String_t *s = Seq.GetStringiser(seq)(Seq.Get(seq, 0));

	return (!s->Equals(s, pat)) ? SeqBasis.OkRead1(seq, p) : SeqBasis.Err(seq, p);
}

static SeqAnswer_t OneOf(Seq_t *pats, Seq_t *seq, Processor_t *p) {
	if (seq->IsEmpty(seq)) return SeqBasis.Err(seq, p);

	String_t *s = Seq.GetStringiser(seq)(Seq.Get(seq, 0));
	for (uint32_t i = 0; i < pats->GetLength(pats); i++)
		if (s->Equals(s, pats->Get(pats, i)))
			return SeqBasis.OkRead1(seq, p);

	return SeqBasis.Err(seq, p);
}

static SeqAnswer_t Satisfy(Answer_t (* judger)(String_t *, Processor_t *), Seq_t *seq, Processor_t *p) {
	if (seq->IsEmpty(seq)) return SeqBasis.Err(seq, p);

	String_t *s = Seq.GetStringiser(seq)(Seq.Get(seq, 0));
	Answer_t r = judger(s, p);
	return (r.Reply == Reply.Ok && String.IsEmpty(r.Subsequent)) ?
		SeqBasis.OkRead1(seq, p) : SeqBasis.Err(seq, p);
}

_SeqParsers SeqParsers = {
	.Match			= Match,
	.UnMatch		= UnMatch,
	.OneOf			= OneOf,
	.Satisfy		= Satisfy,
};
