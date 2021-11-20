#include "Parquet/ParserCombinator/Combinator.h"

static Result_t Bind(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), String_t *s) {
	Result_t result = fst(s);
	  if (result.Reply == Failed) return Basis.Err(s);
	  String_t *precip = result.Precipitate;

	result = snd(result.Subsequent);
	  if (result.Reply == Failed) return Basis.Err(s);
	  precip = String.Concat(precip, result.Precipitate);

	return (Result_t){
		.Reply			= Succeeded,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
	};
}

static Result_t Bind3(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), String_t *s) {
	Result_t result = Combinator.Bind(fst, snd, s);
	  if (result.Reply == Failed) return Basis.Err(s);
	  String_t *precip = result.Precipitate;

	result = trd(result.Subsequent);
	  if (result.Reply == Failed) return Basis.Err(s);
	  precip = String.Concat(precip, result.Precipitate);

	return (Result_t){
		.Reply			= Succeeded,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
	};
}

static Result_t Bind4(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), String_t *s) {
	Result_t result = Combinator.Bind3(fst, snd, trd, s);
	  if (result.Reply == Failed) return Basis.Err(s);
	  String_t *precip = result.Precipitate;

	result = fth(result.Subsequent);
	  if (result.Reply == Failed) return Basis.Err(s);
	  precip = String.Concat(precip, result.Precipitate);

	return (Result_t){
		.Reply			= Succeeded,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
	};
}

static Result_t Bind5(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), Result_t (* fif)(String_t *), String_t *s) {
	Result_t result = Combinator.Bind4(fst, snd, trd, fth, s);
	  if (result.Reply == Failed) return Basis.Err(s);
	  String_t *precip = result.Precipitate;

	result = fif(result.Subsequent);
	  if (result.Reply == Failed) return Basis.Err(s);
	  precip = String.Concat(precip, result.Precipitate);

	return (Result_t){
		.Reply			= Succeeded,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
	};
}

static Result_t Bind6(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), Result_t (* fif)(String_t *), Result_t (* sth)(String_t *), String_t *s) {
	Result_t result = Combinator.Bind5(fst, snd, trd, fth, fif, s);
	  if (result.Reply == Failed) return Basis.Err(s);
	  String_t *precip = result.Precipitate;

	result = sth(result.Subsequent);
	  if (result.Reply == Failed) return Basis.Err(s);
	  precip = String.Concat(precip, result.Precipitate);

	return (Result_t){
		.Reply			= Succeeded,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
	};
}

static Result_t Choise(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), String_t *s) {
	Result_t result = fst(s);
	if (result.Reply == Succeeded) return result;

	result = snd(s);
	if (result.Reply == Succeeded) return result;

	return Basis.Err(s);
}

static Result_t Choise3(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), String_t *s) {
	Result_t result = Choise(fst, snd, s);
	if (result.Reply == Succeeded) return result;

	result = trd(s);
	if (result.Reply == Succeeded) return result;

	return Basis.Err(s);
}

static Result_t Choise4(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), String_t *s) {
	Result_t result = Choise3(fst, snd, trd, s);
	if (result.Reply == Succeeded) return result;

	result = fth(s);
	if (result.Reply == Succeeded) return result;

	return Basis.Err(s);
}

static Result_t Choise5(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), Result_t (* fif)(String_t *), String_t *s) {
	Result_t result = Choise4(fst, snd, trd, fth, s);
	if (result.Reply == Succeeded) return result;

	result = fif(s);
	if (result.Reply == Succeeded) return result;

	return Basis.Err(s);
}

static Result_t Choise6(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), Result_t (* fif)(String_t *), Result_t (* sth)(String_t *), String_t *s) {
	Result_t result = Choise5(fst, snd, trd, fth, fif, s);
	if (result.Reply == Succeeded) return result;

	result = sth(s);
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
