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

	.ParseTest		= ParseTest,
};
