#include "MPLParser.h"

//static AST_t *ast;
static uint32_t lineNum;

static Result_t Parser_Comment(String_t *code) {
	Result_t line(String_t *code) {
		Result_t open(String_t *code) {
			return Primitive.Char.Char('{', code);
		}

		Result_t nonClose(String_t *code) {
			return Primitive.Char.NoneOf(
				String.New(u8"}"),
				code
			);
		}

		Result_t content(String_t *code) {
			return Parser.Many0(nonClose, code);
		}

		Result_t close(String_t *code) {
			return Primitive.Char.Char('}', code);
		}

		return Parser.Bind3(
			open,
			content,
			close,
			code
		);
	}

	Result_t block(String_t *code) {
		Result_t open(String_t *code) {
			return Primitive.String.Match(
				String.New(u8"/*"),
				code
			);
		}

		Result_t nonClose(String_t *code) {
			return Primitive.String.UnMatch(
				String.New(u8"*/"),
				code
			);
		}

		Result_t content(String_t *code) {
			return Parser.Many0(nonClose, code);
		}

		Result_t close(String_t *code) {
			return Primitive.String.Match(
				String.New(u8"*/"),
				code
			);
		}

		return Parser.Bind3(
			open,
			content,
			close,
			code
		);
	}

	return Parser.Choise(line, block, code);
}

static Result_t Parser_Separator(String_t *code) {
	Result_t space_tab(String_t *code) {
		List_t *seps = List.New();
		seps->Add(seps, String.New(u8" "));
		seps->Add(seps, String.New(u8"\t"));

		return Primitive.String.OneOf(
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

		Result_t result = Primitive.String.OneOf(
			nls,
			code
		);

/****************************************/
		if (result.Reply == Ok) lineNum++;
/****************************************/

		return result;
	}

	return Parser.Choise3(
		space_tab,
		newline,
		Parser_Comment,
		code
	); 
}

static Result_t Parser_Digit(String_t *code) {
	return Primitive.Char.Digit(code);
}

static Result_t Parser_Alphabet(String_t *code) {
	return Primitive.Char.Letter(code);
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

	Result_t result = Primitive.String.OneOf(
		syms,
		code
	);

/****************************************/
	if (result.Reply == Ok)
		;
/****************************************/

	return result;
}

static Result_t Parser_String(String_t *code) {
	Result_t apostr(String_t *code) {
		return Primitive.Char.Char('\'', code);
	}

	Result_t nonapostr(String_t *code) {
		return Primitive.Char.NoneOf(
			String.New(u8"'"),
			code
		);
	}

	Result_t content(String_t *code) {
		return Parser.Many0(nonapostr, code);
	}

	Result_t result = Parser.Bind3(
		apostr,
		content,
		apostr,
		code
	);

/****************************************/
	if (result.Reply == Ok)
		;
/****************************************/

	return result;
}

static Result_t Parser_UInt(String_t *code) {
	Result_t result = Parser.Many1(Parser_Digit, code);

/****************************************/
	if (result.Reply == Ok)
		;
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

	Result_t result = Primitive.String.OneOf(
		keywords,
		code
	);

/****************************************/
	if (result.Reply == Ok)
		;
/****************************************/

	return result;
}

static Result_t Parser_Name(String_t *code) {
	Result_t al_num(String_t *code) {
		return Parser.Choise(
			Parser_Alphabet,
			Parser_Digit,
			code
		);
	}

	Result_t al_num_Rep(String_t *code) {
		return Parser.Many0(al_num, code);
	}

	Result_t result = Parser.Bind(
		al_num,
		al_num_Rep,
		code
	);

/****************************************/
	if (result.Reply == Ok)
		;
/****************************************/

	return result;
}

static Result_t Parser_Token(String_t *code) {
	return Parser.Choise5(
		Parser_Symbol,
		Parser_Keyword,
		Parser_UInt,
		Parser_String,
		Parser_Name,
		code
	);
}

static Result_t Parser_Program_(String_t *code) {
	Result_t tok_sep(String_t *code) {
		return Parser.Choise(
			Parser_Separator,
			Parser_Token,
			code
		);
	}

	return Parser.Many0(tok_sep, code);
}

static Result_t Parser_Program(String_t *code) {
	Result_t program(String_t *code) {
		return Primitive.String.Match(String.New(u8"program"), code);
	}

	Result_t nenddotrep(String_t *code) {
		Result_t nenddot(String_t *code) {
			return Primitive.String.UnMatch(String.New(u8"end."), code);
		}

		return Parser.Many0(nenddot, code);
	}

	Result_t enddot(String_t *code) {
		return Primitive.String.Match(String.New(u8"end."), code);
	}

	return Parser.Bind3(
		program,
		nenddotrep,
		enddot,
		code
	);
}

static ParseResult_t Execute(String_t *code) {
	lineNum = 1;

	Result_t result = Parser.Invoke(Parser_Program, code);

	return (ParseResult_t){
		.Succeeded		= result.Reply == Ok,
		.ErrorLine		= lineNum,
		.Precipitate	= result.Precipitate,
		.Subsequent		= result.Subsequent,
	};
}

_MPLParser MPLParser = {
	.Execute = Execute,
};
