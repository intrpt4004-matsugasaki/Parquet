#include "Scraper/Parser.h"

static Result_t makeErr(String_t *s) {
	return (Result_t){
		.Reply			= Err,
		.Precipitate	= String.New(u8""),
		.Subsequent		= s,
	};
}

static Result_t makeOk(String_t *s) {
	return (Result_t){
		.Reply 			= Ok,
		.Precipitate	= String.New(u8""),
		.Subsequent		= s,
	};
}

static Result_t makeOkRead1(String_t *s) {
	return (Result_t){
		.Reply			= Ok,
		.Precipitate	= s->Substring(s, 0, 2),
		.Subsequent		= s->Substring(s, 1, s->GetLength(s) + 1),
	};
}

static Result_t Bind(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), String_t *s) {
	Result_t result = fst(s);
	  if (result.Reply == Err) return Parser.makeErr(s);
	  String_t *precip = result.Precipitate;

	result = snd(result.Subsequent);
	  if (result.Reply == Err) return Parser.makeErr(s);
	  precip = String.Concat(precip, result.Precipitate);

	return (Result_t){
		.Reply			= Ok,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
	};
}

static Result_t Bind3(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), String_t *s) {
	Result_t result = Parser.Bind(fst, snd, s);
	  if (result.Reply == Err) return Parser.makeErr(s);
	  String_t *precip = result.Precipitate;

	result = trd(result.Subsequent);
	  if (result.Reply == Err) return Parser.makeErr(s);
	  precip = String.Concat(precip, result.Precipitate);

	return (Result_t){
		.Reply			= Ok,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
	};
}

static Result_t Bind4(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), String_t *s) {
	Result_t result = Parser.Bind3(fst, snd, trd, s);
	  if (result.Reply == Err) return Parser.makeErr(s);
	  String_t *precip = result.Precipitate;

	result = fth(result.Subsequent);
	  if (result.Reply == Err) return Parser.makeErr(s);
	  precip = String.Concat(precip, result.Precipitate);

	return (Result_t){
		.Reply			= Ok,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
	};
}

static Result_t Bind5(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), Result_t (* fif)(String_t *), String_t *s) {
	Result_t result = Parser.Bind4(fst, snd, trd, fth, s);
	  if (result.Reply == Err) return Parser.makeErr(s);
	  String_t *precip = result.Precipitate;

	result = fif(result.Subsequent);
	  if (result.Reply == Err) return Parser.makeErr(s);
	  precip = String.Concat(precip, result.Precipitate);

	return (Result_t){
		.Reply			= Ok,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
	};
}

static Result_t Bind6(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), Result_t (* fif)(String_t *), Result_t (* sth)(String_t *), String_t *s) {
	Result_t result = Parser.Bind5(fst, snd, trd, fth, fif, s);
	  if (result.Reply == Err) return Parser.makeErr(s);
	  String_t *precip = result.Precipitate;

	result = sth(result.Subsequent);
	  if (result.Reply == Err) return Parser.makeErr(s);
	  precip = String.Concat(precip, result.Precipitate);

	return (Result_t){
		.Reply			= Ok,
		.Precipitate	= precip,
		.Subsequent		= result.Subsequent,
	};
}

static Result_t Choise(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), String_t *s) {
	Result_t result = fst(s);
	if (result.Reply == Ok) return result;

	result = snd(s);
	if (result.Reply == Ok) return result;

	return Parser.makeErr(s);
}

static Result_t Choise3(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), String_t *s) {
	Result_t result = Choise(fst, snd, s);
	if (result.Reply == Ok) return result;

	result = trd(s);
	if (result.Reply == Ok) return result;

	return Parser.makeErr(s);
}

static Result_t Choise4(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), String_t *s) {
	Result_t result = Choise3(fst, snd, trd, s);
	if (result.Reply == Ok) return result;

	result = fth(s);
	if (result.Reply == Ok) return result;

	return Parser.makeErr(s);
}

static Result_t Choise5(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), Result_t (* fif)(String_t *), String_t *s) {
	Result_t result = Choise4(fst, snd, trd, fth, s);
	if (result.Reply == Ok) return result;

	result = fif(s);
	if (result.Reply == Ok) return result;

	return Parser.makeErr(s);
}

static Result_t Choise6(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), Result_t (* fif)(String_t *), Result_t (* sth)(String_t *), String_t *s) {
	Result_t result = Choise5(fst, snd, trd, fth, fif, s);
	if (result.Reply == Ok) return result;

	result = sth(s);
	if (result.Reply == Ok) return result;

	return Parser.makeErr(s);
}

static Result_t Many0(Result_t (* parser)(String_t *), String_t *s) {
	Result_t result = parser(s);
	if (result.Reply == Err) return Parser.makeOk(s);

	String_t *precip = result.Precipitate;
	String_t *subseq = result.Subsequent;
	for (;;) {
		result = parser(result.Subsequent);
		if (result.Reply == Err) return (Result_t){
			.Reply			= Ok,
			.Precipitate	= precip,
			.Subsequent		= subseq,
		};

		precip = String.Concat(precip, result.Precipitate);
		subseq = result.Subsequent;
	}
}

static Result_t Many1(Result_t (* parser)(String_t *), String_t *s) {
	Result_t result = parser(s);
	if (result.Reply == Err) return Parser.makeErr(s);

	String_t *precip = result.Precipitate;
	String_t *subseq = result.Subsequent;
	for (;;) {
		result = parser(result.Subsequent);
		if (result.Reply == Err) return (Result_t){
			.Reply			= Ok,
			.Precipitate	= precip,
			.Subsequent		= subseq,
		};

		precip = String.Concat(precip, result.Precipitate);
		subseq = result.Subsequent;
	}
}

static Result_t Invoke(Result_t (* parser)(String_t *), String_t *s) {
	return parser(s);
}

static void ParseTest(Result_t (* parser)(String_t *), String_t *s) {
	Result_t result = parser(s);
	if (result.Reply == Err) {
		printf("Parser.ParseTest: parse failed.\n");
		return;
	}

	if (!result.Subsequent->IsEmpty(result.Subsequent)) {
		printf("Parser.ParseTest: parse incorrect.\n");
		printf("\"%s\" [%s]\n", String.GetPrimitive(result.Precipitate), String.GetPrimitive(result.Subsequent));
		return;
	}

	printf("\"%s\"\n", String.GetPrimitive(result.Precipitate));
}

_Parser Parser = {
	.makeErr		= makeErr,
	.makeOk			= makeOk,
	.makeOkRead1	= makeOkRead1,

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

	.Invoke			= Invoke,
	.ParseTest		= ParseTest,
};
