#include "Parquet/ParserCombinator/Parser.h"

static Result_t OneOf(String_t *list, String_t *s) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	for (uint32_t i = 0; i < list->GetLength(list); i++) {
		if (list->GetCharAt(list, i) == s->GetHeadChar(s)) {
			return Basis.OkRead1(s);
		}
	}

	return Basis.Err(s);
}

static Result_t NoneOf(String_t *list, String_t *s) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	for (uint32_t i = 0; i < list->GetLength(list); i++) {
		if (list->GetCharAt(list, i) == s->GetHeadChar(s)) {
			return Basis.Err(s);
		}
	}

	return Basis.OkRead1(s);
}

static Result_t Space(String_t *s) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	return Parser.Char.Char(' ', s);
}

static Result_t Spaces0(String_t *s) {
	return Combinator.Many0(Parser.Char.Space, s);
}

static Result_t Spaces1(String_t *s) {
	return Combinator.Many0(Parser.Char.Space, s);
}

static Result_t LF(String_t *s) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	return Parser.Char.Char('\n', s);
}

static Result_t CRLF(String_t *s) {
	if (s->GetLength(s) < 2) return Basis.Err(s);

	return Parser.String.Match(String.New(u8"\r\n"), s);
}

static Result_t EndOfLine(String_t *s) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	return Combinator.Choise(LF, CRLF, s);
}

static Result_t Tab(String_t *s) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	return Parser.Char.Char('\t', s);
}

static Result_t Upper(String_t *s) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	if (!isupper(s->GetHeadChar(s))) return Basis.Err(s);

	return Basis.OkRead1(s);
}

static Result_t Lower(String_t *s) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	if (!islower(s->GetHeadChar(s))) return Basis.Err(s);

	return Basis.OkRead1(s);
}

static Result_t AlphaNum(String_t *s) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	if (!isalnum(s->GetHeadChar(s))) return Basis.Err(s);

	return Basis.OkRead1(s);
}

static Result_t Letter(String_t *s) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	if (!isalpha(s->GetHeadChar(s))) return Basis.Err(s);

	return Basis.OkRead1(s);
}

static Result_t Digit(String_t *s) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	if (!isdigit(s->GetHeadChar(s))) return Basis.Err(s);

	return Basis.OkRead1(s);
}

static Result_t HexDigit(String_t *s) {
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

static Result_t OctDigit(String_t *s) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	if (!isodigit(s->GetHeadChar(s))) return Basis.Err(s);

	return Basis.OkRead1(s);
}

static Result_t Char(uint8_t c, String_t *s) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	if (!s->StartsWithChar(s, c)) return Basis.Err(s);

	return Basis.OkRead1(s);
}

static Result_t NonChar(uint8_t c, String_t *s) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	if (s->StartsWithChar(s, c)) return Basis.Err(s);

	return Basis.OkRead1(s);
}

static Result_t Any(String_t *s) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	return Basis.OkRead1(s);
}

static Result_t Satisfy(bool (* judge)(uint8_t c), String_t *s) {	
	if (s->IsEmpty(s)) return Basis.Err(s);

	if (!judge(s->GetHeadChar(s))) return Basis.Err(s);

	return Basis.OkRead1(s);
}

static Result_t Match(String_t *pat, String_t *s) {	
	if (s->IsEmpty(s)) return Basis.Err(s);

	if (!s->StartsWith(s, pat)) return Basis.Err(s);

	return (Result_t){
		.Reply			= Succeeded,
		.Precipitate	= pat->Copy(pat),
		.Subsequent		= s->Substring(s, pat->GetLength(pat), s->GetLength(s) + 1),
	};
}

static Result_t UnMatch(String_t *pat, String_t *s) {
	if (s->IsEmpty(s)) return Basis.Err(s);

	if (s->StartsWith(s, pat)) return Basis.Err(s);

	return Basis.OkRead1(s);
}

static Result_t String_OneOf(List_t *list, String_t *s) {
	for (uint32_t i = 0; i < list->GetLength(list); i++)
		if (s->StartsWith(s, list->Get(list, i)))
			return (Result_t){
				.Reply			= Succeeded,
				.Precipitate	= String.Copy(list->Get(list, i)),
				.Subsequent		= String.Substring(s,
					String.GetLength(list->Get(list, i)),
					String.GetLength(s) + 1
				),
			};

	return Basis.Err(s);
}

_Parser Parser = {
	.Char = {
		.OneOf		= OneOf,
		.NoneOf		= NoneOf,
		.Space		= Space,
		.Spaces0	= Spaces0,
		.Spaces1	= Spaces1,
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
		.NonChar	= NonChar,
		.Any		= Any,
		.Satisfy	= Satisfy,
	},

	.String = {
		.Match		= Match,
		.UnMatch	= UnMatch,
		.OneOf		= String_OneOf,
	},
};
