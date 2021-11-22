#include "Parquet/ParserCombinator/Parsers.h"

static Answer_t Match(uint8_t c, String_t *s, Processor_t p) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	if (!s->StartsWithChar(s, c)) return Basis.Err(s);

	return Basis.OkRead1(s);
}

static Answer_t UnMatch(uint8_t c, String_t *s, Processor_t p) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	if (s->StartsWithChar(s, c)) return Basis.Err(s);

	return Basis.OkRead1(s);
}

static Answer_t OneOf(String_t *list, String_t *s, Processor_t p) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	for (uint32_t i = 0; i < list->GetLength(list); i++) {
		if (list->GetCharAt(list, i) == s->GetHeadChar(s)) {
			return Basis.OkRead1(s);
		}
	}

	return Basis.Err(s);
}

static Answer_t NoneOf(String_t *list, String_t *s, Processor_t p) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	for (uint32_t i = 0; i < list->GetLength(list); i++) {
		if (list->GetCharAt(list, i) == s->GetHeadChar(s)) {
			return Basis.Err(s);
		}
	}

	return Basis.OkRead1(s);
}

static Answer_t Upper(String_t *s, Processor_t p) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	if (!isupper(s->GetHeadChar(s))) return Basis.Err(s);

	return Basis.OkRead1(s);
}

static Answer_t Lower(String_t *s, Processor_t p) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	if (!islower(s->GetHeadChar(s))) return Basis.Err(s);

	return Basis.OkRead1(s);
}

static Answer_t AlphaNum(String_t *s, Processor_t p) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	if (!isalnum(s->GetHeadChar(s))) return Basis.Err(s);

	return Basis.OkRead1(s);
}

static Answer_t Letter(String_t *s, Processor_t p) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	if (!isalpha(s->GetHeadChar(s))) return Basis.Err(s);

	return Basis.OkRead1(s);
}

static Answer_t Digit(String_t *s, Processor_t p) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	if (!isdigit(s->GetHeadChar(s))) return Basis.Err(s);

	return Basis.OkRead1(s);
}

static Answer_t HexDigit(String_t *s, Processor_t p) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	if (!isxdigit(s->GetHeadChar(s))) return Basis.Err(s);

	return Basis.OkRead1(s);
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

static Answer_t OctDigit(String_t *s, Processor_t p) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	if (!isodigit(s->GetHeadChar(s))) return Basis.Err(s);

	return Basis.OkRead1(s);
}

static Answer_t Any(String_t *s, Processor_t p) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	return Basis.OkRead1(s);
}

static Answer_t Satisfy(bool (* judge)(uint8_t c), String_t *s, Processor_t p) {	
	if (s->IsEmpty(s)) return Basis.Err(s);

	if (!judge(s->GetHeadChar(s))) return Basis.Err(s);

	return Basis.OkRead1(s);
}

static Answer_t Space(String_t *s, Processor_t p) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	return Parsers.Char.Match(' ', s, p);
}

static Answer_t Spaces0(String_t *s, Processor_t p) {
	return Combinator.Many0(Parsers.Char.Space, s, p);
}

static Answer_t Spaces1(String_t *s, Processor_t p) {
	return Combinator.Many0(Parsers.Char.Space, s, p);
}

static Answer_t LF(String_t *s, Processor_t p) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	return Parsers.Char.Match('\n', s, p);
}

static Answer_t CRLF(String_t *s, Processor_t p) {
	if (s->GetLength(s) < 2) return Basis.Err(s);

	return Parsers.String.Match(String.New(u8"\r\n"), s, p);
}

static Answer_t EndOfLine(String_t *s, Processor_t p) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	return Combinator.Choise(LF, CRLF, s, p);
}

static Answer_t Tab(String_t *s, Processor_t p) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	return Parsers.Char.Match('\t', s, p);
}

static Answer_t String_Match(String_t *pat, String_t *s, Processor_t p) {	
	if (s->IsEmpty(s)) return Basis.Err(s);

	if (!s->StartsWith(s, pat)) return Basis.Err(s);

	return (Answer_t){
		.Reply			= Reply.Ok,
		.Precipitate	= pat->Copy(pat),
		.Subsequent		= s->Substring(s, pat->GetLength(pat), s->GetLength(s) + 1),
	};
}

static Answer_t String_UnMatch(String_t *pat, String_t *s, Processor_t p) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	if (s->StartsWith(s, pat)) return Basis.Err(s);

	return Basis.OkRead1(s);
}

static Answer_t String_OneOf(List_t *list, String_t *s, Processor_t p) {
	for (uint32_t i = 0; i < list->GetLength(list); i++)
		if (s->StartsWith(s, list->Get(list, i)))
			return (Answer_t){
				.Reply			= Reply.Ok,
				.Precipitate	= String.Copy(list->Get(list, i)),
				.Subsequent		= String.Substring(s,
					String.GetLength(list->Get(list, i)),
					String.GetLength(s) + 1
				),
			};

	return Basis.Err(s);
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
	},
};
