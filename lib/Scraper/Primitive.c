#include "Scraper/Primitive.h"

static Result_t OneOf(String_t *list, String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	for (uint32_t i = 0; i < list->GetLength(list); i++) {
		if (list->GetCharAt(list, i) == s->GetHeadChar(s)) { // 複数当て嵌る可能性の考慮は？
			return Parser.makeOkRead1(s);
		}
	}

	return Parser.makeErr(s);
}

static Result_t NoneOf(String_t *list, String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	for (uint32_t i = 0; i < list->GetLength(list); i++) {
		if (list->GetCharAt(list, i) == s->GetHeadChar(s)) {
			return Parser.makeErr(s);
		}
	}

	return Parser.makeOkRead1(s);
}

static Result_t Spaces(String_t *s) {
	// skip spaces
}

static Result_t Space(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	return Primitive.Char.Char(' ', s);
}

static Result_t LF(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	return Primitive.Char.Char('\n', s);
}

static Result_t CRLF(String_t *s) {
	if (s->GetLength(s) < 2) return Parser.makeErr(s);

	Result_t prs = Primitive.Char.Char('\r', s);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  String_t *precip = prs.Precipitate;

	prs = Primitive.Char.LF(prs.Subsequent);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  precip = String.Concat(precip, prs.Precipitate);

	return (Result_t){
		.Reply			= Ok,
		.Precipitate	= precip,
		.Subsequent		= prs.Subsequent,
	};
}

static Result_t EndOfLine(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	return Parser.Choise(LF, CRLF, s);
}

static Result_t Tab(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	return Primitive.Char.Char('\t', s);
}

static Result_t Upper(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	if (!isupper(s->GetHeadChar(s))) return Parser.makeErr(s);

	return Parser.makeOkRead1(s);
}

static Result_t Lower(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	if (!islower(s->GetHeadChar(s))) return Parser.makeErr(s);

	return Parser.makeOkRead1(s);
}

static Result_t AlphaNum(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	if (!isalnum(s->GetHeadChar(s))) return Parser.makeErr(s);

	return Parser.makeOkRead1(s);
}

static Result_t Letter(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	if (!isalpha(s->GetHeadChar(s))) return Parser.makeErr(s);

	return Parser.makeOkRead1(s);
}

static Result_t Digit(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	if (!isdigit(s->GetHeadChar(s))) return Parser.makeErr(s);

	return Parser.makeOkRead1(s);
}

static Result_t HexDigit(String_t *s) {
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

static Result_t OctDigit(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	if (!isodigit(s->GetHeadChar(s))) return Parser.makeErr(s);

	return Parser.makeOkRead1(s);
}

static Result_t Char(uint8_t c, String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	if (!s->StartsWithChar(s, c)) return Parser.makeErr(s);

	return Parser.makeOkRead1(s);
}

static Result_t Any(String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	return Parser.makeOkRead1(s);
}

static Result_t Satisfy(bool (* judge)(uint8_t c), String_t *s) {	
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	if (!judge(s->GetHeadChar(s))) return Parser.makeErr(s);

	return Parser.makeOkRead1(s);
}

static Result_t Match(String_t *pattern, String_t *s) {	
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	if (!s->StartsWith(s, pattern)) return Parser.makeErr(s);

	return (Result_t){
		.Reply			= Ok,
		.Precipitate	= pattern->Copy(pattern),
		.Subsequent		= s->Substring(s, pattern->GetLength(pattern), s->GetLength(s) + 1),
	};
}

static Result_t UnMatch(String_t *pattern, String_t *s) {
	if (s->IsEmpty(s)) return Parser.makeErr(s);

	if (s->StartsWith(s, pattern)) return Parser.makeErr(s);

	return Parser.makeOkRead1(s);
}

static Result_t String_OneOf(List_t *list, String_t *s) {
	for (uint32_t i = 0; i < list->GetLength(list); i++)
		if (s->StartsWith(s, list->Get(list, i)))
			return (Result_t){
				.Reply			= Ok,
				.Precipitate	= String.Copy(list->Get(list, i)),
				.Subsequent		= String.Substring(s,
					String.GetLength(list->Get(list, i)),
					String.GetLength(s) + 1
				),
			};

	return Parser.makeErr(s);
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
		.UnMatch	= UnMatch,
		.OneOf		= String_OneOf,
	},
};
