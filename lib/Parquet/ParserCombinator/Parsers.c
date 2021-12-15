#include "Parquet/ParserCombinator/Parsers.h"

static Answer_t Match(uint8_t c, String_t *s, Processor_t *p) {
	if (s->IsEmpty(s)) return Basis.Err(s, p);

	if (!s->StartsWithChar(s, c)) return Basis.Err(s, p);

	return Basis.OkRead1(s, p);
}

static Answer_t UnMatch(uint8_t c, String_t *s, Processor_t *p) {
	if (s->IsEmpty(s)) return Basis.Err(s, p);

	if (s->StartsWithChar(s, c)) return Basis.Err(s, p);

	return Basis.OkRead1(s, p);
}

static Answer_t OneOf(String_t *cs, String_t *s, Processor_t *p) {
	if (s->IsEmpty(s)) return Basis.Err(s, p);

	for (uint32_t i = 0; i < cs->GetLength(cs); i++) {
		if (cs->GetCharAt(cs, i) == s->GetHeadChar(s)) {
			return Basis.OkRead1(s, p);
		}
	}

	return Basis.Err(s, p);
}

static Answer_t NoneOf(String_t *cs, String_t *s, Processor_t *p) {
	if (s->IsEmpty(s)) return Basis.Err(s, p);

	for (uint32_t i = 0; i < cs->GetLength(cs); i++) {
		if (cs->GetCharAt(cs, i) == s->GetHeadChar(s)) {
			return Basis.Err(s, p);
		}
	}

	return Basis.OkRead1(s, p);
}

static Answer_t Upper(String_t *s, Processor_t *p) {
	if (s->IsEmpty(s)) return Basis.Err(s, p);

	if (!isupper(s->GetHeadChar(s))) return Basis.Err(s, p);

	return Basis.OkRead1(s, p);
}

static Answer_t Lower(String_t *s, Processor_t *p) {
	if (s->IsEmpty(s)) return Basis.Err(s, p);

	if (!islower(s->GetHeadChar(s))) return Basis.Err(s, p);

	return Basis.OkRead1(s, p);
}

static Answer_t AlphaNum(String_t *s, Processor_t *p) {
	if (s->IsEmpty(s)) return Basis.Err(s, p);

	if (!isalnum(s->GetHeadChar(s))) return Basis.Err(s, p);

	return Basis.OkRead1(s, p);
}

static Answer_t Letter(String_t *s, Processor_t *p) {
	if (s->IsEmpty(s)) return Basis.Err(s, p);

	if (!isalpha(s->GetHeadChar(s))) return Basis.Err(s, p);

	return Basis.OkRead1(s, p);
}

static Answer_t Digit(String_t *s, Processor_t *p) {
	if (s->IsEmpty(s)) return Basis.Err(s, p);

	if (!isdigit(s->GetHeadChar(s))) return Basis.Err(s, p);

	return Basis.OkRead1(s, p);
}

static Answer_t HexDigit(String_t *s, Processor_t *p) {
	if (s->IsEmpty(s)) return Basis.Err(s, p);

	if (!isxdigit(s->GetHeadChar(s))) return Basis.Err(s, p);

	return Basis.OkRead1(s, p);
}

static bool isodigit(uint8_t c) {
	return isdigit(c)
		|| c == u8'a'
		|| c == u8'b'
		|| c == u8'c'
		|| c == u8'd'
		|| c == u8'e'
		|| c == u8'f';
}

static Answer_t OctDigit(String_t *s, Processor_t *p) {
	if (s->IsEmpty(s)) return Basis.Err(s, p);

	if (!isodigit(s->GetHeadChar(s))) return Basis.Err(s, p);

	return Basis.OkRead1(s, p);
}

static Answer_t Any(String_t *s, Processor_t *p) {
	if (s->IsEmpty(s)) return Basis.Err(s, p);

	return Basis.OkRead1(s, p);
}

static Answer_t Satisfy(bool (* judger)(uint8_t c), String_t *s, Processor_t *p) {	
	if (s->IsEmpty(s)) return Basis.Err(s, p);

	if (!judger(s->GetHeadChar(s))) return Basis.Err(s, p);

	return Basis.OkRead1(s, p);
}

static Answer_t Space(String_t *s, Processor_t *p) {
	if (s->IsEmpty(s)) return Basis.Err(s, p);

	return Parsers.Char.Match(u8' ', s, p);
}

static Answer_t Spaces0(String_t *s, Processor_t *p) {
	return Combinator.Many0(Parsers.Char.Space, s, p);
}

static Answer_t Spaces1(String_t *s, Processor_t *p) {
	return Combinator.Many0(Parsers.Char.Space, s, p);
}

static Answer_t LF(String_t *s, Processor_t *p) {
	if (s->IsEmpty(s)) return Basis.Err(s, p);

	return Parsers.Char.Match(u8'\n', s, p);
}

static Answer_t CRLF(String_t *s, Processor_t *p) {
	if (s->GetLength(s) < 2) return Basis.Err(s, p);

	return Parsers.String.Match(String.New(u8"\r\n"), s, p);
}

static Answer_t EndOfLine(String_t *s, Processor_t *p) {
	if (s->IsEmpty(s)) return Basis.Err(s, p);

	return Combinator.Choise(LF, CRLF, s, p);
}

static Answer_t Tab(String_t *s, Processor_t *p) {
	if (s->IsEmpty(s)) return Basis.Err(s, p);

	return Parsers.Char.Match(u8'\t', s, p);
}

static Answer_t String_Match(String_t *pat, String_t *s, Processor_t *p) {	
	if (s->IsEmpty(s)) return Basis.Err(s, p);

	if (!s->StartsWith(s, pat)) return Basis.Err(s, p);

	return (Answer_t){
		.Reply			= Reply.Ok,
		.Precipitate	= pat->Copy(pat),
		.Subsequent		= s->Substring(s, pat->GetLength(pat), s->GetLength(s) + 1),
	};
}

static Answer_t String_UnMatch(String_t *pat, String_t *s, Processor_t *p) {
	if (s->IsEmpty(s)) return Basis.Err(s, p);

	if (s->StartsWith(s, pat)) return Basis.Err(s, p);

	return Basis.OkRead1(s, p);
}

static Answer_t String_OneOf(List_t *pats, String_t *s, Processor_t *p) {
	for (uint32_t i = 0; i < pats->GetLength(pats); i++) {
		String_t *pat = pats->Get(pats, i);

		if (pat->GetLength(pat) > s->GetLength(s))
			continue;

		if (s->StartsWith(s, pat)) {
			return Basis.OkReadString(pat, s, p);
		}
	}

	return Basis.Err(s, p);
}

static Answer_t String_NoneOf(List_t *pats, String_t *s, Processor_t *p) {
	for (uint32_t i = 0; i < pats->GetLength(pats); i++) {
		String_t *pat = pats->Get(pats, i);

		if (pat->GetLength(pat) > s->GetLength(s))
			continue;

		if (s->StartsWith(s, pat))
			return Basis.Err(s, p);
	}

	return Basis.OkRead1(s, p);
}

_Parsers Parsers = {
	.Char = {
		.Match		= Match,
		.UnMatch	= UnMatch,
		.OneOf		= OneOf,
		.NoneOf		= NoneOf,

		.Upper		= Upper,
		.Lower		= Lower,
		.AlphaNum	= AlphaNum,
		.Letter		= Letter,
		.Digit		= Digit,
		.HexDigit	= HexDigit,
		.OctDigit	= OctDigit,
		.Any		= Any,
		.Satisfy	= Satisfy,

		.Space		= Space,
		.Spaces0	= Spaces0,
		.Spaces1	= Spaces1,
		.LF			= LF,
		.CRLF		= CRLF,
		.EndOfLine	= EndOfLine,
		.Tab		= Tab,
	},

	.String = {
		.Match			= String_Match,
		.UnMatch		= String_UnMatch,
		.OneOf			= String_OneOf,
		.NoneOf			= String_NoneOf,
	},
};
