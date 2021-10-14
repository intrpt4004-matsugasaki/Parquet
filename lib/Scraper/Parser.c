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
	Result_t prs = fst(s);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  String_t *precip = prs.Precipitate;

	prs = snd(prs.Subsequent);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  precip = String.Concat(precip, prs.Precipitate);

	return (Result_t){
		.Reply			= Ok,
		.Precipitate	= precip,
		.Subsequent		= prs.Subsequent,
	};
}

static Result_t Bind3(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), String_t *s) {
	Result_t prs = Parser.Bind(fst, snd, s);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  String_t *precip = prs.Precipitate;

	prs = trd(prs.Subsequent);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  precip = String.Concat(precip, prs.Precipitate);

	return (Result_t){
		.Reply			= Ok,
		.Precipitate	= precip,
		.Subsequent		= prs.Subsequent,
	};
}

static Result_t Bind4(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), String_t *s) {
	Result_t prs = Parser.Bind3(fst, snd, trd, s);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  String_t *precip = prs.Precipitate;

	prs = fth(prs.Subsequent);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  precip = String.Concat(precip, prs.Precipitate);

	return (Result_t){
		.Reply			= Ok,
		.Precipitate	= precip,
		.Subsequent		= prs.Subsequent,
	};
}

static Result_t Bind5(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), Result_t (* fif)(String_t *), String_t *s) {
	Result_t prs = Parser.Bind4(fst, snd, trd, fth, s);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  String_t *precip = prs.Precipitate;

	prs = fif(prs.Subsequent);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  precip = String.Concat(precip, prs.Precipitate);

	return (Result_t){
		.Reply			= Ok,
		.Precipitate	= precip,
		.Subsequent		= prs.Subsequent,
	};
}

static Result_t Bind6(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), Result_t (* fif)(String_t *), Result_t (* sth)(String_t *), String_t *s) {
	Result_t prs = Parser.Bind5(fst, snd, trd, fth, fif, s);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  String_t *precip = prs.Precipitate;

	prs = sth(prs.Subsequent);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  precip = String.Concat(precip, prs.Precipitate);

	return (Result_t){
		.Reply			= Ok,
		.Precipitate	= precip,
		.Subsequent		= prs.Subsequent,
	};
}

static Result_t Choise(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), String_t *s) {
	Result_t prs = fst(s);
	if (prs.Reply == Ok) return prs;

	prs = snd(s);
	if (prs.Reply == Ok) return prs;

	return Parser.makeErr(s);
}

static Result_t Choise3(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), String_t *s) {
	Result_t prs = Choise(fst, snd, s);
	if (prs.Reply == Ok) return prs;

	prs = trd(s);
	if (prs.Reply == Ok) return prs;

	return Parser.makeErr(s);
}

static Result_t Choise4(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), String_t *s) {
	Result_t prs = Choise3(fst, snd, trd, s);
	if (prs.Reply == Ok) return prs;

	prs = fth(s);
	if (prs.Reply == Ok) return prs;

	return Parser.makeErr(s);
}

static Result_t Choise5(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), Result_t (* fif)(String_t *), String_t *s) {
	Result_t prs = Choise4(fst, snd, trd, fth, s);
	if (prs.Reply == Ok) return prs;

	prs = fif(s);
	if (prs.Reply == Ok) return prs;

	return Parser.makeErr(s);
}

static Result_t Choise6(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), Result_t (* fif)(String_t *), Result_t (* sth)(String_t *), String_t *s) {
	Result_t prs = Choise5(fst, snd, trd, fth, fif, s);
	if (prs.Reply == Ok) return prs;

	prs = sth(s);
	if (prs.Reply == Ok) return prs;

	return Parser.makeErr(s);
}

static Result_t Many0(Result_t (* parser)(String_t *), String_t *s) {
	Result_t prs = parser(s);
	if (prs.Reply == Err) return Parser.makeOk(s);

	String_t *precip = prs.Precipitate;
	String_t *subseq = prs.Subsequent;
	for (;;) {
		prs = parser(prs.Subsequent);
		if (prs.Reply == Err) return (Result_t){
			.Reply			= Ok,
			.Precipitate	= precip,
			.Subsequent		= subseq,
		};

		precip = String.Concat(precip, prs.Precipitate);
		subseq = prs.Subsequent;
	}
}

static Result_t Many1(Result_t (* parser)(String_t *), String_t *s) {
	Result_t prs = parser(s);
	if (prs.Reply == Err) return Parser.makeErr(s);

	String_t *precip = prs.Precipitate;
	String_t *subseq = prs.Subsequent;
	for (;;) {
		prs = parser(prs.Subsequent);
		if (prs.Reply == Err) return (Result_t){
			.Reply			= Ok,
			.Precipitate	= precip,
			.Subsequent		= subseq,
		};

		precip = String.Concat(precip, prs.Precipitate);
		subseq = prs.Subsequent;
	}
}

static Result_t Invoke(Result_t (* parser)(String_t *), String_t *s) {
	return parser(s);
}

static void ParseTest(Result_t (* parser)(String_t *), String_t *s) {
	Result_t prs = parser(s);
	if (prs.Reply == Err) {
		printf("Parser.ParseTest: parse failed.\n");
		return;
	}

	if (!prs.Subsequent->IsEmpty(prs.Subsequent)) {
		printf("Parser.ParseTest: parse incorrect.\n");
		printf("\"%s\" [%s]\n", String.GetPrimitive(prs.Precipitate), String.GetPrimitive(prs.Subsequent));
		return;
	}

	printf("\"%s\"\n", String.GetPrimitive(prs.Precipitate));
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
