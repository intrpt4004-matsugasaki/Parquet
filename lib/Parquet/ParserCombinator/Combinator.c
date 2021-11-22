#include "Parquet/ParserCombinator/Combinator.h"

static Answer_t Bind(Answer_t (* parser1)(String_t *, Processor_t), Answer_t (* parser2)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t result = parser1(s, p);
	  if (result.Reply == Reply.Err) return Basis.Err(s);
	  String_t *precip = result.Precipitate;

	result = parser2(result.Subsequent, p);
	  if (result.Reply == Reply.Err) return Basis.Err(s);
	  precip = String.Concat(precip, result.Precipitate);

	return (Answer_t){
		.Reply			= Reply.Ok,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
	};
}

static Answer_t Bind3(Answer_t (* parser1)(String_t *, Processor_t), Answer_t (* parser2)(String_t *, Processor_t), Answer_t (* parser3)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t result = Combinator.Bind(parser1, parser2, s, p);
	  if (result.Reply == Reply.Err) return Basis.Err(s);
	  String_t *precip = result.Precipitate;

	result = parser3(result.Subsequent, p);
	  if (result.Reply == Reply.Err) return Basis.Err(s);
	  precip = String.Concat(precip, result.Precipitate);

	return (Answer_t){
		.Reply			= Reply.Ok,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
	};
}

static Answer_t Bind4(Answer_t (* parser1)(String_t *, Processor_t), Answer_t (* parser2)(String_t *, Processor_t), Answer_t (* parser3)(String_t *, Processor_t), Answer_t (* parser4)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t result = Combinator.Bind3(parser1, parser2, parser3, s, p);
	  if (result.Reply == Reply.Err) return Basis.Err(s);
	  String_t *precip = result.Precipitate;

	result = parser4(result.Subsequent, p);
	  if (result.Reply == Reply.Err) return Basis.Err(s);
	  precip = String.Concat(precip, result.Precipitate);

	return (Answer_t){
		.Reply			= Reply.Ok,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
	};
}

static Answer_t Bind5(Answer_t (* parser1)(String_t *, Processor_t), Answer_t (* parser2)(String_t *, Processor_t), Answer_t (* parser3)(String_t *, Processor_t), Answer_t (* parser4)(String_t *, Processor_t), Answer_t (* parser5)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t result = Combinator.Bind4(parser1, parser2, parser3, parser4, s, p);
	  if (result.Reply == Reply.Err) return Basis.Err(s);
	  String_t *precip = result.Precipitate;

	result = parser5(result.Subsequent, p);
	  if (result.Reply == Reply.Err) return Basis.Err(s);
	  precip = String.Concat(precip, result.Precipitate);

	return (Answer_t){
		.Reply			= Reply.Ok,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
	};
}

static Answer_t Bind6(Answer_t (* parser1)(String_t *, Processor_t), Answer_t (* parser2)(String_t *, Processor_t), Answer_t (* parser3)(String_t *, Processor_t), Answer_t (* parser4)(String_t *, Processor_t), Answer_t (* parser5)(String_t *, Processor_t), Answer_t (* parser6)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t result = Combinator.Bind5(parser1, parser2, parser3, parser4, parser5, s, p);
	  if (result.Reply == Reply.Err) return Basis.Err(s);
	  String_t *precip = result.Precipitate;

	result = parser6(result.Subsequent, p);
	  if (result.Reply == Reply.Err) return Basis.Err(s);
	  precip = String.Concat(precip, result.Precipitate);

	return (Answer_t){
		.Reply			= Reply.Ok,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
	};
}

static Answer_t Choise(Answer_t (* parser1)(String_t *, Processor_t), Answer_t (* parser2)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t result = parser1(s, p);
	if (result.Reply == Reply.Ok) return result;

	result = parser2(s, p);
	if (result.Reply == Reply.Ok) return result;

	return Basis.Err(s);
}

static Answer_t Choise3(Answer_t (* parser1)(String_t *, Processor_t), Answer_t (* parser2)(String_t *, Processor_t), Answer_t (* parser3)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t result = Choise(parser1, parser2, s, p);
	if (result.Reply == Reply.Ok) return result;

	result = parser3(s, p);
	if (result.Reply == Reply.Ok) return result;

	return Basis.Err(s);
}

static Answer_t Choise4(Answer_t (* parser1)(String_t *, Processor_t), Answer_t (* parser2)(String_t *, Processor_t), Answer_t (* parser3)(String_t *, Processor_t), Answer_t (* parser4)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t result = Choise3(parser1, parser2, parser3, s, p);
	if (result.Reply == Reply.Ok) return result;

	result = parser4(s, p);
	if (result.Reply == Reply.Ok) return result;

	return Basis.Err(s);
}

static Answer_t Choise5(Answer_t (* parser1)(String_t *, Processor_t), Answer_t (* parser2)(String_t *, Processor_t), Answer_t (* parser3)(String_t *, Processor_t), Answer_t (* parser4)(String_t *, Processor_t), Answer_t (* parser5)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t result = Choise4(parser1, parser2, parser3, parser4, s, p);
	if (result.Reply == Reply.Ok) return result;

	result = parser5(s, p);
	if (result.Reply == Reply.Ok) return result;

	return Basis.Err(s);
}

static Answer_t Choise6(Answer_t (* parser1)(String_t *, Processor_t), Answer_t (* parser2)(String_t *, Processor_t), Answer_t (* parser3)(String_t *, Processor_t), Answer_t (* parser4)(String_t *, Processor_t), Answer_t (* parser5)(String_t *, Processor_t), Answer_t (* parser6)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t result = Choise5(parser1, parser2, parser3, parser4, parser5, s, p);
	if (result.Reply == Reply.Ok) return result;

	result = parser6(s, p);
	if (result.Reply == Reply.Ok) return result;

	return Basis.Err(s);
}

static Answer_t Many0(Answer_t (* parser)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t result = parser(s, p);
	if (result.Reply == Reply.Err) return Basis.Ok(s);

	String_t *precip = result.Precipitate;
	String_t *subseq = result.Subsequent;
	for (;;) {
		result = parser(result.Subsequent, p);
		if (result.Reply == Reply.Err) return (Answer_t){
			.Reply			= Reply.Ok,
			.Precipitate	= precip,
			.Subsequent		= subseq,
		};

		precip = String.Concat(precip, result.Precipitate);
		subseq = result.Subsequent;
	}
}

static Answer_t Many1(Answer_t (* parser)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t result = parser(s, p);
	if (result.Reply == Reply.Err) return Basis.Err(s);

	String_t *precip = result.Precipitate;
	String_t *subseq = result.Subsequent;
	for (;;) {
		result = parser(result.Subsequent, p);
		if (result.Reply == Reply.Err) return (Answer_t){
			.Reply			= Reply.Ok,
			.Precipitate	= precip,
			.Subsequent		= subseq,
		};

		precip = String.Concat(precip, result.Precipitate);
		subseq = result.Subsequent;
	}
}

static Answer_t Possibly(Answer_t (* parser)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t result = parser(s, p);
	return (result.Reply == Reply.Ok) ?
		result : Basis.Ok(s);
}

_Combinator Combinator = {
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
