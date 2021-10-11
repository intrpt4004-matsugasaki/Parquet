#include "Scraper/Primitive.h"

static Parse OneOf(String_t *cs, String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr();

	for (uint32_t i = 0; i < cs->GetLength(cs); i++) {
		if (cs->GetHeadChar(cs) == s->GetHeadChar(s)) { // 複数当て嵌る可能性の考慮は？
			return Parser.makeOkChar(s);
		}
	}

	return Parser.makeErr();
}

static Parse NoneOf(String_t *cs, String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr();

	for (uint32_t i = 0; i < cs->GetLength(cs); i++) {
		if (cs->GetHeadChar(cs) == s->GetHeadChar(s)) {
			return Parser.makeErr();
		}
	}

	return Parser.makeOkChar(s);
}

static Parse Spaces(String_t *s) {
	// skip spaces
}


static Parse Space(String_t *s) {
	return Primitive.Char.Char(' ', s);
}

static Parse NewLine(String_t *s) {
	return Primitive.Char.Char('\n', s);
}

static Parse Crlf(String_t *s) {
	Parse prs = Primitive.Char.Char('\r', s);
	if (prs.Reply == Err) return Parser.makeErr();
	String_t *precip = prs.Precipitate;

	prs = Primitive.Char.Char('\r', prs.Subsequent);
	if (prs.Reply == Err) return Parser.makeErr();
	precip = String.Concat(precip, prs.Precipitate);

	return (Parse){
		.Reply			= Ok,
		.Precipitate	= precip,
		.Subsequent		= prs.Subsequent,
	};
}

static Parse EndOfLine(String_t *s) {

}

static Parse Tab(String_t *s) {
	return Primitive.Char.Char('\t', s);
}

static Parse Upper(String_t *) {

}

static Parse Lower(String_t *) {

}

static Parse AlphaNum(String_t *) {

}

static Parse Letter(String_t *) {

}

static Parse Digit(String_t *) {

}

static Parse HexDigit(String_t *) {
}

static Parse OctDigit(String_t *) {
}

static Parse Char(uint8_t c, String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr();

	if (!s->StartsWithChar(s, c)) return Parser.makeErr();

	return Parser.makeOkChar(s);
}

static Parse Any(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr();

	return Parser.makeOkChar(s);
}

static Parse Satisfy(String_t *s) {	

}

static Parse Str(String_t *s) {	

}

_Primitive Primitive = {
	.Char = {
		.Any	= Any,
		.Space	= Space,
	},
};
