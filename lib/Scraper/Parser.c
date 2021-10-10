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

_Parser Parser = {
	.makeErr	= makeErr,
	.makeOkChar	= makeOkChar,
};
