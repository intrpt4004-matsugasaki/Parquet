#include "MPLLexer.h"

static List_t *tokens;
static uint32_t lineNum;

static Result_t Parser_Comment(String_t *code) {
	Result_t line(String_t *code) {
		Result_t open(String_t *code) {
			return Parser.Char.Match('{', code);
		}

		Result_t nonClose(String_t *code) {
			return Parser.Char.NoneOf(
				String.New(u8"}"),
				code
			);
		}

		Result_t content(String_t *code) {
			return Combinator.Many0(nonClose, code);
		}

		Result_t close(String_t *code) {
			return Parser.Char.Match('}', code);
		}

		return Combinator.Bind3(
			open,
			content,
			close,
			code
		);
	}

	Result_t block(String_t *code) {
		Result_t open(String_t *code) {
			return Parser.String.Match(
				String.New(u8"/*"),
				code
			);
		}

		Result_t nonClose(String_t *code) {
			return Parser.String.UnMatch(
				String.New(u8"*/"),
				code
			);
		}

		Result_t content(String_t *code) {
			return Combinator.Many0(nonClose, code);
		}

		Result_t close(String_t *code) {
			return Parser.String.Match(
				String.New(u8"*/"),
				code
			);
		}

		return Combinator.Bind3(
			open,
			content,
			close,
			code
		);
	}

	return Combinator.Choise(line, block, code);
}

static Result_t Parser_Separator(String_t *code) {
	Result_t space_tab(String_t *code) {
		List_t *seps = List.New();
		seps->Add(seps, String.New(u8" "));
		seps->Add(seps, String.New(u8"\t"));

		return Parser.String.OneOf(
			seps,
			code
		);
	}

	Result_t newline(String_t *code) {
		List_t *nls = List.New();
		nls->Add(nls, String.New(u8"\r\n"));
		nls->Add(nls, String.New(u8"\r"));
		nls->Add(nls, String.New(u8"\n\r"));
		nls->Add(nls, String.New(u8"\n"));

		Result_t result = Parser.String.OneOf(
			nls,
			code
		);

/****************************************/
		if (result.Reply == Succeeded) lineNum++;
/****************************************/

		return result;
	}

	return Combinator.Choise3(
		space_tab,
		newline,
		Parser_Comment,
		code
	); 
}

static Result_t Parser_Digit(String_t *code) {
	return Parser.Char.Digit(code);
}

static Result_t Parser_Alphabet(String_t *code) {
	return Parser.Char.Letter(code);
}

static Result_t Parser_Symbol(String_t *code) {
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

	Result_t result = Parser.String.OneOf(
		syms,
		code
	);

/****************************************/
	if (result.Reply == Succeeded)
		tokens->Add(tokens, Token.New(result.Precipitate, Token_Symbol, lineNum));
/****************************************/

	return result;
}

static Result_t Parser_String(String_t *code) {
	Result_t apostr(String_t *code) {
		return Parser.Char.Match('\'', code);
	}

	Result_t nonapostr(String_t *code) {
		return Parser.Char.NoneOf(
			String.New(u8"'"),
			code
		);
	}

	Result_t content(String_t *code) {
		return Combinator.Many0(nonapostr, code);
	}

	Result_t result = Combinator.Bind3(
		apostr,
		content,
		apostr,
		code
	);

/****************************************/
	if (result.Reply == Succeeded)
		tokens->Add(tokens, Token.New(result.Precipitate, Token_String, lineNum));
/****************************************/

	return result;
}

static Result_t Parser_UInt(String_t *code) {
	Result_t result = Combinator.Many1(Parser_Digit, code);

/****************************************/
	if (result.Reply == Succeeded)
		tokens->Add(tokens, Token.New(result.Precipitate, Token_UInt, lineNum));
/****************************************/

	return result;
}

static Result_t Parser_Keyword(String_t *code) {
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

	Result_t result = Parser.String.OneOf(
		keywords,
		code
	);

/****************************************/
	if (result.Reply == Succeeded)
		tokens->Add(tokens, Token.New(result.Precipitate, Token_Keyword, lineNum));
/****************************************/

	return result;
}

static Result_t Parser_Name(String_t *code) {
	Result_t al_num(String_t *code) {
		return Combinator.Choise(
			Parser_Alphabet,
			Parser_Digit,
			code
		);
	}

	Result_t al_num_Rep(String_t *code) {
		return Combinator.Many0(al_num, code);
	}

	Result_t result = Combinator.Bind(
		al_num,
		al_num_Rep,
		code
	);

/****************************************/
	if (result.Reply == Succeeded)
		tokens->Add(tokens, Token.New(result.Precipitate, Token_Name, lineNum));
/****************************************/

	return result;
}

static Result_t Parser_Token(String_t *code) {
	return Combinator.Choise5(
		Parser_Symbol,
		Parser_Keyword,
		Parser_UInt,
		Parser_String,
		Parser_Name,
		code
	);
}

static Result_t Parser_Program(String_t *code) {
	Result_t tok_sep(String_t *code) {
		return Combinator.Choise(
			Parser_Separator,
			Parser_Token,
			code
		);
	}

	return Combinator.Many0(tok_sep, code);
}

static LexResult_t Execute(String_t *code) {
	tokens = List.New();
	lineNum = 1;

	Result_t result = Invoker.Parse(Parser_Program, code);

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
