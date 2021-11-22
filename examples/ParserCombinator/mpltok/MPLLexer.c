#include "MPLLexer.h"

static List_t *tokens;
static uint32_t lineNum;

static Answer_t Parser_Comment(String_t *s, Processor_t p) {
	Answer_t line(String_t *s, Processor_t p) {
		Answer_t open(String_t *s, Processor_t p) {
			return Parsers.Char.Match('{', s, p);
		}

		Answer_t nonClose(String_t *s, Processor_t p) {
			return Parsers.Char.NoneOf(
				String.New(u8"}"),
				s, p
			);
		}

		Answer_t content(String_t *s, Processor_t p) {
			return Combinator.Many0(nonClose, s, p);
		}

		Answer_t close(String_t *s, Processor_t p) {
			return Parsers.Char.Match('}', s, p);
		}

		return Combinator.Bind3(
			open,
			content,
			close,
			s, p
		);
	}

	Answer_t block(String_t *s, Processor_t p) {
		Answer_t open(String_t *s, Processor_t p) {
			return Parsers.String.Match(
				String.New(u8"/*"),
				s, p
			);
		}

		Answer_t nonClose(String_t *s, Processor_t p) {
			return Parsers.String.UnMatch(
				String.New(u8"*/"),
				s, p
			);
		}

		Answer_t content(String_t *s, Processor_t p) {
			return Combinator.Many0(nonClose, s, p);
		}

		Answer_t close(String_t *s, Processor_t p) {
			return Parsers.String.Match(
				String.New(u8"*/"),
				s, p
			);
		}

		return Combinator.Bind3(
			open,
			content,
			close,
			s, p
		);
	}

	return Combinator.Choise(line, block, s, p);
}

static Answer_t Parser_Separator(String_t *s, Processor_t p) {
	Answer_t space_tab(String_t *s, Processor_t p) {
		List_t *seps = List.New();
		seps->Add(seps, String.New(u8" "));
		seps->Add(seps, String.New(u8"\t"));

		return Parsers.String.OneOf(
			seps,
			s, p
		);
	}

	Answer_t newline(String_t *s, Processor_t p) {
		List_t *nls = List.New();
		nls->Add(nls, String.New(u8"\r\n"));
		nls->Add(nls, String.New(u8"\r"));
		nls->Add(nls, String.New(u8"\n\r"));
		nls->Add(nls, String.New(u8"\n"));

		Answer_t result = Parsers.String.OneOf(
			nls,
			s, p
		);

/****************************************/
		if (result.Reply == Reply.Ok) lineNum++;
/****************************************/

		return result;
	}

	return Combinator.Choise3(
		space_tab,
		newline,
		Parser_Comment,
		s, p
	); 
}

static Answer_t Parser_Digit(String_t *s, Processor_t p) {
	return Parsers.Char.Digit(s, p);
}

static Answer_t Parser_Alphabet(String_t *s, Processor_t p) {
	return Parsers.Char.Letter(s, p);
}

static Answer_t Parser_Symbol(String_t *s, Processor_t p) {
	List_t *syms = List.New();
	syms->Add(syms, String.New(u8"+"));
	syms->Add(syms, String.New(u8"-"));
	syms->Add(syms, String.New(u8"*"));
	syms->Add(syms, String.New(u8"="));
	syms->Add(syms, String.New(u8"<>"));
	syms->Add(syms, String.New(u8"<="));
	syms->Add(syms, String.New(u8"<"));
	syms->Add(syms, String.New(u8">="));
	syms->Add(syms, String.New(u8">"));
	syms->Add(syms, String.New(u8"("));
	syms->Add(syms, String.New(u8")"));
	syms->Add(syms, String.New(u8"["));
	syms->Add(syms, String.New(u8"]"));
	syms->Add(syms, String.New(u8"."));
	syms->Add(syms, String.New(u8","));
	syms->Add(syms, String.New(u8":="));
	syms->Add(syms, String.New(u8":"));
	syms->Add(syms, String.New(u8";"));

	Answer_t result = Parsers.String.OneOf(
		syms,
		s, p
	);

/****************************************/
	if (result.Reply == Reply.Ok)
		tokens->Add(tokens, Token.New(result.Precipitate, Token_Symbol, lineNum));
/****************************************/

	return result;
}

static Answer_t Parser_String(String_t *s, Processor_t p) {
	Answer_t apostr(String_t *s, Processor_t p) {
		return Parsers.Char.Match('\'', s, p);
	}

	Answer_t nonapostr(String_t *s, Processor_t p) {
		return Parsers.Char.NoneOf(
			String.New(u8"'"),
			s, p
		);
	}

	Answer_t content(String_t *s, Processor_t p) {
		return Combinator.Many0(nonapostr, s, p);
	}

	Answer_t result = Combinator.Bind3(
		apostr,
		content,
		apostr,
		s, p
	);

/****************************************/
	if (result.Reply == Reply.Ok)
		tokens->Add(tokens, Token.New(result.Precipitate, Token_String, lineNum));
/****************************************/

	return result;
}

static Answer_t Parser_UInt(String_t *s, Processor_t p) {
	Answer_t result = Combinator.Many1(Parser_Digit, s, p);

/****************************************/
	if (result.Reply == Reply.Ok)
		tokens->Add(tokens, Token.New(result.Precipitate, Token_UInt, lineNum));
/****************************************/

	return result;
}

static Answer_t Parser_Keyword(String_t *s, Processor_t p) {
	List_t *keywords = List.New();
	keywords->Add(keywords, String.New(u8"program"));
	keywords->Add(keywords, String.New(u8"var"));
	keywords->Add(keywords, String.New(u8"array"));
	keywords->Add(keywords, String.New(u8"of"));
	keywords->Add(keywords, String.New(u8"begin"));
	keywords->Add(keywords, String.New(u8"if"));
	keywords->Add(keywords, String.New(u8"then"));
	keywords->Add(keywords, String.New(u8"else"));
	keywords->Add(keywords, String.New(u8"procedure"));
	keywords->Add(keywords, String.New(u8"call"));
	keywords->Add(keywords, String.New(u8"while"));
	keywords->Add(keywords, String.New(u8"do"));
	keywords->Add(keywords, String.New(u8"not"));
	keywords->Add(keywords, String.New(u8"or"));
	keywords->Add(keywords, String.New(u8"div"));
	keywords->Add(keywords, String.New(u8"and"));
	keywords->Add(keywords, String.New(u8"char"));
	keywords->Add(keywords, String.New(u8"integer"));
	keywords->Add(keywords, String.New(u8"boolean"));
	keywords->Add(keywords, String.New(u8"readln"));
	keywords->Add(keywords, String.New(u8"read"));
	keywords->Add(keywords, String.New(u8"writeln"));
	keywords->Add(keywords, String.New(u8"write"));
	keywords->Add(keywords, String.New(u8"true"));
	keywords->Add(keywords, String.New(u8"false"));
	keywords->Add(keywords, String.New(u8"break"));

	Answer_t result = Parsers.String.OneOf(
		keywords,
		s, p
	);

/****************************************/
	if (result.Reply == Reply.Ok)
		tokens->Add(tokens, Token.New(result.Precipitate, Token_Keyword, lineNum));
/****************************************/

	return result;
}

static Answer_t Parser_Name(String_t *s, Processor_t p) {
	Answer_t al_num(String_t *s, Processor_t p) {
		return Combinator.Choise(
			Parser_Alphabet,
			Parser_Digit,
			s, p
		);
	}

	Answer_t al_num_Rep(String_t *s, Processor_t p) {
		return Combinator.Many0(al_num, s, p);
	}

	Answer_t result = Combinator.Bind(
		al_num,
		al_num_Rep,
		s, p
	);

/****************************************/
	if (result.Reply == Reply.Ok)
		tokens->Add(tokens, Token.New(result.Precipitate, Token_Name, lineNum));
/****************************************/

	return result;
}

static Answer_t Parser_Token(String_t *s, Processor_t p) {
	return Combinator.Choise5(
		Parser_Symbol,
		Parser_Keyword,
		Parser_UInt,
		Parser_String,
		Parser_Name,
		s, p
	);
}

static Answer_t Parser_Program(String_t *s, Processor_t p) {
	Answer_t tok_sep(String_t *s, Processor_t p) {
		return Combinator.Choise(
			Parser_Separator,
			Parser_Token,
			s, p
		);
	}

	return Combinator.Many0(tok_sep, s, p);
}

static LexResult_t Execute(String_t *s) {
	tokens = List.New();
	lineNum = 1;

	Answer_t result = Invoker.Parse(Parser_Program, s, NULL);

	return (LexResult_t){
		.Succeeded		= String.IsEmpty(result.Subsequent),
		.ErrorLine		= lineNum,
		.Precipitate	= result.Precipitate,
		.Subsequent		= result.Subsequent,
		.TokenList		= tokens,
	};
}

_MPLLexer MPLLexer = {
	.Execute = Execute,
};
