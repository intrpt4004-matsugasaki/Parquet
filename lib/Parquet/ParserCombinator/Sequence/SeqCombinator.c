#include "Parquet/ParserCombinator/Sequence/SeqCombinator.h"

static SeqAnswer_t Bind(SeqAnswer_t (* seqParser1)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser2)(Seq_t *, Processor_t *), Seq_t *seq, Processor_t *p) {
	SeqAnswer_t result = seqParser1(seq, p);
	if (result.Reply == Reply.Err) return SeqBasis.Err(seq, p);
	Seq_t *precip = result.Precipitate;

	result = seqParser2(result.Subsequent, p);
	if (result.Reply == Reply.Err) return SeqBasis.Err(seq, p);
	Seq.AddAll(precip, result.Precipitate);

	return (SeqAnswer_t){
		.Reply			= Reply.Ok,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
		.Processor		= p,
	};
}

static SeqAnswer_t Bind3(SeqAnswer_t (* seqParser1)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser2)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser3)(Seq_t *, Processor_t *), Seq_t *seq, Processor_t *p) {
	SeqAnswer_t result = SeqCombinator.Bind(seqParser1, seqParser2, seq, p);
	if (result.Reply == Reply.Err) return SeqBasis.Err(seq, p);
	Seq_t *precip = result.Precipitate;

	result = seqParser3(result.Subsequent, p);
	if (result.Reply == Reply.Err) return SeqBasis.Err(seq, p);
	Seq.AddAll(precip, result.Precipitate);

	return (SeqAnswer_t){
		.Reply			= Reply.Ok,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
		.Processor		= p,
	};
}

static SeqAnswer_t Bind4(SeqAnswer_t (* seqParser1)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser2)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser3)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser4)(Seq_t *, Processor_t *), Seq_t *seq, Processor_t *p) {
	SeqAnswer_t result = SeqCombinator.Bind3(seqParser1, seqParser2, seqParser3, seq, p);
	if (result.Reply == Reply.Err) return SeqBasis.Err(seq, p);
	Seq_t *precip = result.Precipitate;

	result = seqParser4(result.Subsequent, p);
	if (result.Reply == Reply.Err) return SeqBasis.Err(seq, p);
	Seq.AddAll(precip, result.Precipitate);

	return (SeqAnswer_t){
		.Reply			= Reply.Ok,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
		.Processor		= p,
	};
}

static SeqAnswer_t Bind5(SeqAnswer_t (* seqParser1)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser2)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser3)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser4)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser5)(Seq_t *, Processor_t *), Seq_t *seq, Processor_t *p) {
	SeqAnswer_t result = SeqCombinator.Bind4(seqParser1, seqParser2, seqParser3, seqParser4, seq, p);
	if (result.Reply == Reply.Err) return SeqBasis.Err(seq, p);
	Seq_t *precip = result.Precipitate;

	result = seqParser5(result.Subsequent, p);
	if (result.Reply == Reply.Err) return SeqBasis.Err(seq, p);
	Seq.AddAll(precip, result.Precipitate);

	return (SeqAnswer_t){
		.Reply			= Reply.Ok,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
		.Processor		= p,
	};
}

static SeqAnswer_t Bind6(SeqAnswer_t (* seqParser1)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser2)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser3)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser4)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser5)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser6)(Seq_t *, Processor_t *), Seq_t *seq, Processor_t *p) {
	SeqAnswer_t result = SeqCombinator.Bind5(seqParser1, seqParser2, seqParser3, seqParser4, seqParser5, seq, p);
	if (result.Reply == Reply.Err) return SeqBasis.Err(seq, p);
	Seq_t *precip = result.Precipitate;

	result = seqParser6(result.Subsequent, p);
	if (result.Reply == Reply.Err) return SeqBasis.Err(seq, p);
	Seq.AddAll(precip, result.Precipitate);

	return (SeqAnswer_t){
		.Reply			= Reply.Ok,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
		.Processor		= p,
	};
}

static SeqAnswer_t Choise(SeqAnswer_t (* seqParser1)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser2)(Seq_t *, Processor_t *), Seq_t *seq, Processor_t *p) {
	SeqAnswer_t result = seqParser1(seq, p);
	if (result.Reply == Reply.Ok) return result;

	result = seqParser2(seq, p);
	if (result.Reply == Reply.Ok) return result;

	return SeqBasis.Err(seq, p);
}

static SeqAnswer_t Choise3(SeqAnswer_t (* seqParser1)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser2)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser3)(Seq_t *, Processor_t *), Seq_t *seq, Processor_t *p) {
	SeqAnswer_t result = Choise(seqParser1, seqParser2, seq, p);
	if (result.Reply == Reply.Ok) return result;

	result = seqParser3(seq, p);
	if (result.Reply == Reply.Ok) return result;

	return SeqBasis.Err(seq, p);
}

static SeqAnswer_t Choise4(SeqAnswer_t (* seqParser1)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser2)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser3)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser4)(Seq_t *, Processor_t *), Seq_t *seq, Processor_t *p) {
	SeqAnswer_t result = Choise3(seqParser1, seqParser2, seqParser3, seq, p);
	if (result.Reply == Reply.Ok) return result;

	result = seqParser4(seq, p);
	if (result.Reply == Reply.Ok) return result;

	return SeqBasis.Err(seq, p);
}

static SeqAnswer_t Choise5(SeqAnswer_t (* seqParser1)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser2)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser3)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser4)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser5)(Seq_t *, Processor_t *), Seq_t *seq, Processor_t *p) {
	SeqAnswer_t result = Choise4(seqParser1, seqParser2, seqParser3, seqParser4, seq, p);
	if (result.Reply == Reply.Ok) return result;

	result = seqParser5(seq, p);
	if (result.Reply == Reply.Ok) return result;

	return SeqBasis.Err(seq, p);
}

static SeqAnswer_t Choise6(SeqAnswer_t (* seqParser1)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser2)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser3)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser4)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser5)(Seq_t *, Processor_t *), SeqAnswer_t (* seqParser6)(Seq_t *, Processor_t *), Seq_t *seq, Processor_t *p) {
	SeqAnswer_t result = Choise5(seqParser1, seqParser2, seqParser3, seqParser4, seqParser5, seq, p);
	if (result.Reply == Reply.Ok) return result;

	result = seqParser6(seq, p);
	if (result.Reply == Reply.Ok) return result;

	return SeqBasis.Err(seq, p);
}

static SeqAnswer_t Many0(SeqAnswer_t (* seqParser)(Seq_t *, Processor_t *), Seq_t *seq, Processor_t *p) {
	SeqAnswer_t result = seqParser(seq, p);
	if (result.Reply == Reply.Err) return SeqBasis.Ok(seq, p);

	Seq_t *precip = result.Precipitate;
	Seq_t *subseq = result.Subsequent;
	for (;;) {
		result = seqParser(result.Subsequent, p);
		if (result.Reply == Reply.Err) return (SeqAnswer_t){
			.Reply			= Reply.Ok,
			.Precipitate	= precip,
			.Subsequent		= subseq,
			.Processor		= p,
		};

		Seq.AddAll(precip, result.Precipitate);
		subseq = result.Subsequent;
	}
}

static SeqAnswer_t Many1(SeqAnswer_t (* seqParser)(Seq_t *, Processor_t *), Seq_t *seq, Processor_t *p) {
	SeqAnswer_t result = seqParser(seq, p);
	if (result.Reply == Reply.Err) return SeqBasis.Err(seq, p);

	Seq_t *precip = result.Precipitate;
	Seq_t *subseq = result.Subsequent;
	for (;;) {
		result = seqParser(result.Subsequent, p);
		if (result.Reply == Reply.Err) return (SeqAnswer_t){
			.Reply			= Reply.Ok,
			.Precipitate	= precip,
			.Subsequent		= subseq,
			.Processor		= p,
		};

		Seq.AddAll(precip, result.Precipitate);
		subseq = result.Subsequent;
	}
}

static SeqAnswer_t Possibly(SeqAnswer_t (* seqParser)(Seq_t *, Processor_t *), Seq_t *seq, Processor_t *p) {
	SeqAnswer_t result = seqParser(seq, p);
	return (result.Reply == Reply.Ok) ?
		result : SeqBasis.Ok(seq, p);
}

_SeqCombinator SeqCombinator = {
	.Bind			= Bind,
	.Bind3			= Bind3,
	.Bind4			= Bind4,
	.Bind5			= Bind5,
	.Bind6			= Bind6,

	.Choise			= Choise,
	.Choise3		= Choise3,
	.Choise4		= Choise4,
	.Choise5		= Choise5,
	.Choise6		= Choise6,

	.Many0			= Many0,
	.Many1			= Many1,

	.Possibly		= Possibly,
};
