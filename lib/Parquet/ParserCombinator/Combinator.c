#include "Parquet/ParserCombinator/Combinator.h"

static Result_t Bind(Result_t (* parser1)(String_t *), Result_t (* parser2)(String_t *), String_t *s) {
	Result_t result = parser1(s);
	  if (result.Reply == Failed) return Basis.Err(s);
	  String_t *precip = result.Precipitate;

	result = parser2(result.Subsequent);
	  if (result.Reply == Failed) return Basis.Err(s);
	  precip = String.Concat(precip, result.Precipitate);

	return (Result_t){
		.Reply			= Succeeded,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
	};
}

static Result_t Bind3(Result_t (* parser1)(String_t *), Result_t (* parser2)(String_t *), Result_t (* parser3)(String_t *), String_t *s) {
	Result_t result = Combinator.Bind(parser1, parser2, s);
	  if (result.Reply == Failed) return Basis.Err(s);
	  String_t *precip = result.Precipitate;

	result = parser3(result.Subsequent);
	  if (result.Reply == Failed) return Basis.Err(s);
	  precip = String.Concat(precip, result.Precipitate);

	return (Result_t){
		.Reply			= Succeeded,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
	};
}

static Result_t Bind4(Result_t (* parser1)(String_t *), Result_t (* parser2)(String_t *), Result_t (* parser3)(String_t *), Result_t (* parser4)(String_t *), String_t *s) {
	Result_t result = Combinator.Bind3(parser1, parser2, parser3, s);
	  if (result.Reply == Failed) return Basis.Err(s);
	  String_t *precip = result.Precipitate;

	result = parser4(result.Subsequent);
	  if (result.Reply == Failed) return Basis.Err(s);
	  precip = String.Concat(precip, result.Precipitate);

	return (Result_t){
		.Reply			= Succeeded,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
	};
}

static Result_t Bind5(Result_t (* parser1)(String_t *), Result_t (* parser2)(String_t *), Result_t (* parser3)(String_t *), Result_t (* parser4)(String_t *), Result_t (* parser5)(String_t *), String_t *s) {
	Result_t result = Combinator.Bind4(parser1, parser2, parser3, parser4, s);
	  if (result.Reply == Failed) return Basis.Err(s);
	  String_t *precip = result.Precipitate;

	result = parser5(result.Subsequent);
	  if (result.Reply == Failed) return Basis.Err(s);
	  precip = String.Concat(precip, result.Precipitate);

	return (Result_t){
		.Reply			= Succeeded,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
	};
}

static Result_t Bind6(Result_t (* parser1)(String_t *), Result_t (* parser2)(String_t *), Result_t (* parser3)(String_t *), Result_t (* parser4)(String_t *), Result_t (* parser5)(String_t *), Result_t (* parser6)(String_t *), String_t *s) {
	Result_t result = Combinator.Bind5(parser1, parser2, parser3, parser4, parser5, s);
	  if (result.Reply == Failed) return Basis.Err(s);
	  String_t *precip = result.Precipitate;

	result = parser6(result.Subsequent);
	  if (result.Reply == Failed) return Basis.Err(s);
	  precip = String.Concat(precip, result.Precipitate);

	return (Result_t){
		.Reply			= Succeeded,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
	};
}

static Result_t Choise(Result_t (* parser1)(String_t *), Result_t (* parser2)(String_t *), String_t *s) {
	Result_t result = parser1(s);
	if (result.Reply == Succeeded) return result;

	result = parser2(s);
	if (result.Reply == Succeeded) return result;

	return Basis.Err(s);
}

static Result_t Choise3(Result_t (* parser1)(String_t *), Result_t (* parser2)(String_t *), Result_t (* parser3)(String_t *), String_t *s) {
	Result_t result = Choise(parser1, parser2, s);
	if (result.Reply == Succeeded) return result;

	result = parser3(s);
	if (result.Reply == Succeeded) return result;

	return Basis.Err(s);
}

static Result_t Choise4(Result_t (* parser1)(String_t *), Result_t (* parser2)(String_t *), Result_t (* parser3)(String_t *), Result_t (* parser4)(String_t *), String_t *s) {
	Result_t result = Choise3(parser1, parser2, parser3, s);
	if (result.Reply == Succeeded) return result;

	result = parser4(s);
	if (result.Reply == Succeeded) return result;

	return Basis.Err(s);
}

static Result_t Choise5(Result_t (* parser1)(String_t *), Result_t (* parser2)(String_t *), Result_t (* parser3)(String_t *), Result_t (* parser4)(String_t *), Result_t (* parser5)(String_t *), String_t *s) {
	Result_t result = Choise4(parser1, parser2, parser3, parser4, s);
	if (result.Reply == Succeeded) return result;

	result = parser5(s);
	if (result.Reply == Succeeded) return result;

	return Basis.Err(s);
}

static Result_t Choise6(Result_t (* parser1)(String_t *), Result_t (* parser2)(String_t *), Result_t (* parser3)(String_t *), Result_t (* parser4)(String_t *), Result_t (* parser5)(String_t *), Result_t (* parser6)(String_t *), String_t *s) {
	Result_t result = Choise5(parser1, parser2, parser3, parser4, parser5, s);
	if (result.Reply == Succeeded) return result;

	result = parser6(s);
	if (result.Reply == Succeeded) return result;

	return Basis.Err(s);
}

static Result_t Many0(Result_t (* parser)(String_t *), String_t *s) {
	Result_t result = parser(s);
	if (result.Reply == Failed) return Basis.Ok(s);

	String_t *precip = result.Precipitate;
	String_t *subseq = result.Subsequent;
	for (;;) {
		result = parser(result.Subsequent);
		if (result.Reply == Failed) return (Result_t){
			.Reply			= Succeeded,
			.Precipitate	= precip,
			.Subsequent		= subseq,
		};

		precip = String.Concat(precip, result.Precipitate);
		subseq = result.Subsequent;
	}
}

static Result_t Many1(Result_t (* parser)(String_t *), String_t *s) {
	Result_t result = parser(s);
	if (result.Reply == Failed) return Basis.Err(s);

	String_t *precip = result.Precipitate;
	String_t *subseq = result.Subsequent;
	for (;;) {
		result = parser(result.Subsequent);
		if (result.Reply == Failed) return (Result_t){
			.Reply			= Succeeded,
			.Precipitate	= precip,
			.Subsequent		= subseq,
		};

		precip = String.Concat(precip, result.Precipitate);
		subseq = result.Subsequent;
	}
}

static Result_t Possibly(Result_t (* parser)(String_t *), String_t *s) {
	Result_t result = parser(s);
	return (result.Reply == Succeeded) ?
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
