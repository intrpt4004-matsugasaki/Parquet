#include "Scraper/Primitive.h"

static Parse OneOf(String_t *list, String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	for (uint32_t i = 0; i < list->GetLength(list); i++) {
		if (list->GetCharAt(list, i) == s->GetHeadChar(s)) { // 複数当て嵌る可能性の考慮は？
			return Parser.makeOkRead1(s);
		}
	}

	return Parser.makeErr(s);
}

static Parse NoneOf(String_t *list, String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	for (uint32_t i = 0; i < list->GetLength(list); i++) {
		if (list->GetCharAt(list, i) == s->GetHeadChar(s)) {
			return Parser.makeErr(s);
		}
	}

	return Parser.makeOkRead1(s);
}

static Parse Spaces(String_t *s) {
	// skip spaces
}

static Parse Space(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	return Primitive.Char.Char(' ', s);
}

static Parse LF(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	return Primitive.Char.Char('\n', s);
}

static Parse CRLF(String_t *s) {
	if (s->GetLength(s) < 2) return Parser.makeErr(s);

	Parse prs = Primitive.Char.Char('\r', s);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  String_t *precip = prs.Precipitate;

	prs = Primitive.Char.LF(prs.Subsequent);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  precip = String.Concat(precip, prs.Precipitate);

	return (Parse){
		.Reply			= Ok,
		.Precipitate	= precip,
		.Subsequent		= prs.Subsequent,
	};
}

static Parse EndOfLine(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	return Parser.Choise(LF, CRLF, s);
}

static Parse Tab(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	return Primitive.Char.Char('\t', s);
}

static Parse Upper(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	if (!isupper(s->GetHeadChar(s))) return Parser.makeErr(s);

	return Parser.makeOkRead1(s);
}

static Parse Lower(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	if (!islower(s->GetHeadChar(s))) return Parser.makeErr(s);

	return Parser.makeOkRead1(s);
}

static Parse AlphaNum(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	if (!isalnum(s->GetHeadChar(s))) return Parser.makeErr(s);

	return Parser.makeOkRead1(s);
}

static Parse Letter(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	if (!isalpha(s->GetHeadChar(s))) return Parser.makeErr(s);

	return Parser.makeOkRead1(s);
}

static Parse Digit(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	if (!isdigit(s->GetHeadChar(s))) return Parser.makeErr(s);

	return Parser.makeOkRead1(s);
}

static Parse HexDigit(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	if (!isxdigit(s->GetHeadChar(s))) return Parser.makeErr(s);

	return Parser.makeOkRead1(s);
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
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	if (!isodigit(s->GetHeadChar(s))) return Parser.makeErr(s);

	return Parser.makeOkRead1(s);
}

static Parse Char(uint8_t c, String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	if (!s->StartsWithChar(s, c)) return Parser.makeErr(s);

	return Parser.makeOkRead1(s);
}

static Parse Any(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	return Parser.makeOkRead1(s);
}

static Parse Satisfy(bool (* judge)(uint8_t c), String_t *s) {	
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	if (!judge(s->GetHeadChar(s))) return Parser.makeErr(s);

	return Parser.makeOkRead1(s);
}

static Parse Match(String_t *pattern, String_t *s) {	
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	if (!s->StartsWith(s, pattern)) return Parser.makeErr(s);

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
		.Letter		= Letter,
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
