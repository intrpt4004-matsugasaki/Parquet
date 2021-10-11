#include "Scraper/Primitive.h"

static Parse OneOf(String_t *list, String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr();

	for (uint32_t i = 0; i < list->GetLength(list); i++) {
		if (list->GetCharAt(list, i) == s->GetHeadChar(s)) { // 複数当て嵌る可能性の考慮は？
			return Parser.makeOkChar(s);
		}
	}

	return Parser.makeErr();
}

static Parse NoneOf(String_t *list, String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr();

	for (uint32_t i = 0; i < list->GetLength(list); i++) {
		if (list->GetCharAt(list, i) == s->GetHeadChar(s)) {
			return Parser.makeErr();
		}
	}

	return Parser.makeOkChar(s);
}

static Parse Spaces(String_t *s) {
	// skip spaces
}

static Parse Space(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr();

	return Primitive.Char.Char(' ', s);
}

static Parse LF(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr();

	return Primitive.Char.Char('\n', s);
}

static Parse CRLF(String_t *s) {
	if (s->GetLength(s) < 2) return Parser.makeErr();

	Parse prs = Primitive.Char.Char('\r', s);
	if (prs.Reply == Err) return Parser.makeErr();
	String_t *precip = prs.Precipitate;

	prs = Primitive.Char.LF(prs.Subsequent);
	if (prs.Reply == Err) return Parser.makeErr();
	precip = String.Concat(precip, prs.Precipitate);

	return (Parse){
		.Reply			= Ok,
		.Precipitate	= precip,
		.Subsequent		= prs.Subsequent,
	};
}

static Parse EndOfLine(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr();

	return Parser.Choise(LF, CRLF, s);
}

static Parse Tab(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr();

	return Primitive.Char.Char('\t', s);
}

static Parse Upper(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr();

	if (!isupper(s->GetHeadChar(s))) return Parser.makeErr();

	return Parser.makeOkChar(s);
}

static Parse Lower(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr();

	if (!islower(s->GetHeadChar(s))) return Parser.makeErr();

	return Parser.makeOkChar(s);
}

static Parse AlphaNum(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr();

	if (!isalnum(s->GetHeadChar(s))) return Parser.makeErr();

	return Parser.makeOkChar(s);
}

static Parse Letter(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr();

	//
}

static Parse Digit(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr();

	if (!isdigit(s->GetHeadChar(s))) return Parser.makeErr();

	return Parser.makeOkChar(s);
}

static Parse HexDigit(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr();

	if (!isxdigit(s->GetHeadChar(s))) return Parser.makeErr();

	return Parser.makeOkChar(s);
}

static bool isodigit(uint8_t c) {
	return isdigit(c)
		|| c == 'a'
		|| c == 'b'
		|| c == 'c'
		|| c == 'd'
		|| c == 'e'
		|| c == 'f';
}

static Parse OctDigit(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr();

	if (!isodigit(s->GetHeadChar(s))) return Parser.makeErr();

	return Parser.makeOkChar(s);
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

static Parse Satisfy(bool (* judge)(uint8_t c), String_t *s) {	
	if (s->IsEmpty(s)) return Parser.makeErr();

	if (!judge(s->GetHeadChar(s))) return Parser.makeErr();

	return Parser.makeOkChar(s);
}

static Parse Match(String_t *pattern, String_t *s) {	
	if (s->IsEmpty(s)) return Parser.makeErr();

	if (!s->StartsWith(s, pattern)) return Parser.makeErr();

	return (Parse){
		.Reply			= Ok,
		.Precipitate	= pattern->Copy(pattern),
		.Subsequent		= s->Substring(s, pattern->GetLength(pattern), s->GetLength(s) + 1),
	};
}

_Primitive Primitive = {
	.Char = {
		.OneOf		= OneOf,
		.NoneOf		= NoneOf,
		//.Spaces		= Spaces,
		.Space		= Space,
		.LF			= LF,
		.CRLF		= CRLF,
		.EndOfLine	= EndOfLine,
		.Tab		= Tab,
		.Upper		= Upper,
		.Lower		= Lower,
		.AlphaNum	= AlphaNum,
		//.Letter		= Letter,
		.Digit		= Digit,
		.HexDigit	= HexDigit,
		.OctDigit	= OctDigit,
		.Char		= Char,
		.Any		= Any,
		.Satisfy	= Satisfy,
	},

	.String = {
		.Match		= Match,
	},
};
