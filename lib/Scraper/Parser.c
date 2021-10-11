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

static Parse Choise(Parse (* left)(String_t *), Parse (* right)(String_t *), String_t *s) {
	Parse prs = left(s);
	if (prs.Reply == Ok) return prs;

	prs = right(s);
	if (prs.Reply == Ok) return prs;

	return Parser.makeErr(s);
}

static Parse Many(Parse (* parser)(String_t *), String_t *s) {
	String_t *precip = String.New(u8"");
	for (;;) {
		Parse prs = parser(s);
//		if (prs.Reply == Err) return Parser.makeOk(s);
	}
}

static Parse Many1(Parse (* parser)(String_t *), String_t *s) {
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
	.Choise			= Choise,
	.Many			= Many,
	.Many1			= Many1,

	.ParseTest		= ParseTest,
};
