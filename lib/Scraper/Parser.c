#include "Scraper/Parser.h"

static Parse makeErr(String_t *s) {
	return (Parse){
		.Reply			= Err,
		.Precipitate	= String.New(u8""),
		.Subsequent		= s,
	};
}

static Parse makeOk(String_t *s) {
	return (Parse){
		.Reply 			= Ok,
		.Precipitate	= String.New(u8""),
		.Subsequent		= s,
	};
}

static Parse makeOkRead1(String_t *s) {
	return (Parse){
		.Reply			= Ok,
		.Precipitate	= s->Substring(s, 0, 2),
		.Subsequent		= s->Substring(s, 1, s->GetLength(s) + 1),
	};
}

static Parse Bind(Parse (* fst)(String_t *), Parse (* snd)(String_t *), String_t *s) {
	Parse prs = fst(s);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  String_t *precip = prs.Precipitate;

	prs = snd(prs.Subsequent);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  precip = String.Concat(precip, prs.Precipitate);

	return (Parse){
		.Reply			= Ok,
		.Precipitate	= precip,
		.Subsequent		= prs.Subsequent,
	};
}

static Parse Bind3(Parse (* fst)(String_t *), Parse (* snd)(String_t *), Parse (* trd)(String_t *), String_t *s) {
	Parse prs = Parser.Bind(fst, snd, s);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  String_t *precip = prs.Precipitate;

	prs = trd(prs.Subsequent);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  precip = String.Concat(precip, prs.Precipitate);

	return (Parse){
		.Reply			= Ok,
		.Precipitate	= precip,
		.Subsequent		= prs.Subsequent,
	};
}

static Parse Bind4(Parse (* fst)(String_t *), Parse (* snd)(String_t *), Parse (* trd)(String_t *), Parse (* fth)(String_t *), String_t *s) {
	Parse prs = Parser.Bind3(fst, snd, trd, s);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  String_t *precip = prs.Precipitate;

	prs = fth(prs.Subsequent);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  precip = String.Concat(precip, prs.Precipitate);

	return (Parse){
		.Reply			= Ok,
		.Precipitate	= precip,
		.Subsequent		= prs.Subsequent,
	};
}

static Parse Bind5(Parse (* fst)(String_t *), Parse (* snd)(String_t *), Parse (* trd)(String_t *), Parse (* fth)(String_t *), Parse (* fif)(String_t *), String_t *s) {
	Parse prs = Parser.Bind4(fst, snd, trd, fth, s);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  String_t *precip = prs.Precipitate;

	prs = fif(prs.Subsequent);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  precip = String.Concat(precip, prs.Precipitate);

	return (Parse){
		.Reply			= Ok,
		.Precipitate	= precip,
		.Subsequent		= prs.Subsequent,
	};
}

static Parse Bind6(Parse (* fst)(String_t *), Parse (* snd)(String_t *), Parse (* trd)(String_t *), Parse (* fth)(String_t *), Parse (* fif)(String_t *), Parse (* sth)(String_t *), String_t *s) {
	Parse prs = Parser.Bind5(fst, snd, trd, fth, fif, s);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  String_t *precip = prs.Precipitate;

	prs = sth(prs.Subsequent);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  precip = String.Concat(precip, prs.Precipitate);

	return (Parse){
		.Reply			= Ok,
		.Precipitate	= precip,
		.Subsequent		= prs.Subsequent,
	};
}

static Parse Choise(Parse (* fst)(String_t *), Parse (* snd)(String_t *), String_t *s) {
	Parse prs = fst(s);
	if (prs.Reply == Ok) return prs;

	prs = snd(s);
	if (prs.Reply == Ok) return prs;

	return Parser.makeErr(s);
}

static Parse Choise3(Parse (* fst)(String_t *), Parse (* snd)(String_t *), Parse (* trd)(String_t *), String_t *s) {
	Parse prs = Choise(fst, snd, s);
	if (prs.Reply == Ok) return prs;

	prs = trd(s);
	if (prs.Reply == Ok) return prs;

	return Parser.makeErr(s);
}

static Parse Choise4(Parse (* fst)(String_t *), Parse (* snd)(String_t *), Parse (* trd)(String_t *), Parse (* fth)(String_t *), String_t *s) {
	Parse prs = Choise3(fst, snd, trd, s);
	if (prs.Reply == Ok) return prs;

	prs = fth(s);
	if (prs.Reply == Ok) return prs;

	return Parser.makeErr(s);
}

static Parse Choise5(Parse (* fst)(String_t *), Parse (* snd)(String_t *), Parse (* trd)(String_t *), Parse (* fth)(String_t *), Parse (* fif)(String_t *), String_t *s) {
	Parse prs = Choise4(fst, snd, trd, fth, s);
	if (prs.Reply == Ok) return prs;

	prs = fif(s);
	if (prs.Reply == Ok) return prs;

	return Parser.makeErr(s);
}

static Parse Choise6(Parse (* fst)(String_t *), Parse (* snd)(String_t *), Parse (* trd)(String_t *), Parse (* fth)(String_t *), Parse (* fif)(String_t *), Parse (* sth)(String_t *), String_t *s) {
	Parse prs = Choise5(fst, snd, trd, fth, fif, s);
	if (prs.Reply == Ok) return prs;

	prs = sth(s);
	if (prs.Reply == Ok) return prs;

	return Parser.makeErr(s);
}

static Parse Many0(Parse (* parser)(String_t *), String_t *s) {
	Parse prs = parser(s);
	if (prs.Reply == Err) return Parser.makeOk(s);

	String_t *precip = prs.Precipitate;
	String_t *subseq = prs.Subsequent;
	for (;;) {
		prs = parser(prs.Subsequent);
		if (prs.Reply == Err) return (Parse){
			.Reply			= Ok,
			.Precipitate	= precip,
			.Subsequent		= subseq,
		};

		precip = String.Concat(precip, prs.Precipitate);
		subseq = prs.Subsequent;
	}
}

static Parse Many1(Parse (* parser)(String_t *), String_t *s) {
	Parse prs = parser(s);
	if (prs.Reply == Err) return Parser.makeErr(s);

	String_t *precip = prs.Precipitate;
	String_t *subseq = prs.Subsequent;
	for (;;) {
		prs = parser(prs.Subsequent);
		if (prs.Reply == Err) return (Parse){
			.Reply			= Ok,
			.Precipitate	= precip,
			.Subsequent		= subseq,
		};

		precip = String.Concat(precip, prs.Precipitate);
		subseq = prs.Subsequent;
	}
}

static void Invoke(Parse (* parser)(String_t *), String_t *s) {
	parser(s);
}

static void ParseTest(Parse (* parser)(String_t *), String_t *s) {
	Parse prs = parser(s);
	if (prs.Reply == Err) {
		printf("Parser.ParseTest: parse failed.\n");
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
