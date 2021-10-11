#include "Scraper/Parser.h"

static Parse makeErr() {
	return (Parse){
		.Reply = Err,
	};
}

static Parse makeOkChar(String_t *s) {
	return (Parse){
		.Reply			= Ok,
		.Precipitate	= s->Substring(s, 0, 2),
		.Subsequent		= s->Substring(s, 1, s->GetLength(s) + 1),
	};
}

static Parse Bind(Parse (* fst)(String_t *), Parse (* snd)(String_t *), String_t *s) {
	Parse prs = fst(s);
	if (prs.Reply == Err) return Parser.makeErr();
	String_t *precip = prs.Precipitate;

	prs = snd(prs.Subsequent);
	if (prs.Reply == Err) return Parser.makeErr();
	precip = String.Concat(precip, prs.Precipitate);

	return (Parse){
		.Reply			= Ok,
		.Precipitate	= precip,
		.Subsequent		= prs.Subsequent,
	};
}

static Parse Bind3(Parse (* fst)(String_t *), Parse (* snd)(String_t *), Parse (* trd)(String_t *), String_t *s) {
	Parse prs = Parser.Bind(fst, snd, s);
	if (prs.Reply == Err) return Parser.makeErr();
	String_t *precip = prs.Precipitate;

	prs = trd(prs.Subsequent);
	if (prs.Reply == Err) return Parser.makeErr();
	precip = String.Concat(precip, prs.Precipitate);

	return (Parse){
		.Reply			= Ok,
		.Precipitate	= precip,
		.Subsequent		= prs.Subsequent,
	};
}

static Parse Bind4(Parse (* fst)(String_t *), Parse (* snd)(String_t *), Parse (* trd)(String_t *), Parse (* fth)(String_t *), String_t *s) {
	Parse prs = Parser.Bind3(fst, snd, trd, s);
	if (prs.Reply == Err) return Parser.makeErr();
	String_t *precip = prs.Precipitate;

	prs = fth(prs.Subsequent);
	if (prs.Reply == Err) return Parser.makeErr();
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

	return Parser.makeErr();
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
	.makeOkChar		= makeOkChar,

	.Bind			= Bind,
	.Bind3			= Bind3,
	.Bind4			= Bind4,
	.Choise			= Choise,

	.ParseTest		= ParseTest,
};
