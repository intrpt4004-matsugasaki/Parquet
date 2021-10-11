#include <Scraper.h>

Parse Parser_Comment(String_t *code) { // Ok
	Parse line(String_t *code) {
		Parse open(String_t *code) {
			return Primitive.Char.Char('{', code);
		}

		Parse nonClose(String_t *code) {
			return Primitive.Char.NoneOf(
				String.New(u8"}"),
				code
			);
		}

		Parse content(String_t *code) {
			return Parser.Many0(nonClose, code);
		}

		Parse close(String_t *code) {
			return Primitive.Char.Char('}', code);
		}

		return Parser.Bind3(
			open,
			content,
			close,
			code
		);
	}

	Parse block(String_t *code) {
		Parse open(String_t *code) {
			return Primitive.String.Match(
				String.New(u8"/*"),
				code
			);
		}

		Parse nonClose(String_t *code) {
			return Primitive.String.UnMatch(
				String.New(u8"*/"),
				code
			);
		}

		Parse content(String_t *code) {
			return Parser.Many0(nonClose, code);
		}

		Parse close(String_t *code) {
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

Parse Parser_Separator(String_t *code) { // Ok
	Parse space_tab_newline(String_t *code) {
		List_t *seps = List.New();
		seps->Add(seps, String.New(u8" "));
		seps->Add(seps, String.New(u8"\t"));
		seps->Add(seps, String.New(u8"\r\n"));
		seps->Add(seps, String.New(u8"\r"));
		seps->Add(seps, String.New(u8"\n\r"));
		seps->Add(seps, String.New(u8"\n"));

		return Primitive.String.OneOf(
			seps,
			code
		);
	}

	return Parser.Choise(space_tab_newline, Parser_Comment, code); 
}

Parse Parser_Digit(String_t *code) { // Ok?
	return Primitive.Char.Digit(code);
}

Parse Parser_Alphabet(String_t *code) { // Ok?
	return Primitive.Char.Letter(code);
}

Parse Parser_Symbol(String_t *code) { // Ok
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

	return Primitive.String.OneOf(
		syms,
		code
	);
}

Parse Parser_String(String_t *code) { // Ok*?
	Parse apostr(String_t *code) {
		return Primitive.Char.Char('\'', code);
	}

	Parse nonapostr(String_t *code) {
		return Primitive.Char.NoneOf(
			String.New(u8"'"),
			code
		);
	}

	Parse content(String_t *code) {
		return Parser.Many0(nonapostr, code);
	}

	return Parser.Bind3(
		apostr,
		content,
		apostr,
		code
	);
}

Parse Parser_UInt(String_t *code) { // Ok?
	return Parser.Many1(Parser_Digit, code);
}

Parse Parser_Keyword(String_t *code) { // OK
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
	keywords->Add(keywords, String.New(u8"read"));
	keywords->Add(keywords, String.New(u8"write"));
	keywords->Add(keywords, String.New(u8"readln"));
	keywords->Add(keywords, String.New(u8"writeln"));
	keywords->Add(keywords, String.New(u8"true"));
	keywords->Add(keywords, String.New(u8"false"));
	keywords->Add(keywords, String.New(u8"break"));

	return Primitive.String.OneOf(
		keywords,
		code
	);
}

Parse Parser_Name(String_t *code) { // Ok
	Parse al_num(String_t *code) {
		return Parser.Choise(
			Parser_Alphabet,
			Parser_Digit,
			code
		);
	}

	Parse al_num_Rep(String_t *code) {
		return Parser.Many0(al_num, code);
	}

	return Parser.Bind(
		al_num,
		al_num_Rep,
		code
	);
}

Parse Parser_Token(String_t *code) {
	Parse prs = Parser.Choise5(
		Parser_Name,
		Parser_Keyword,
		Parser_UInt,
		Parser_String,
		Parser_Symbol,
		code
	);

  //printf("(%s)", String.GetPrimitive(prs.Precipitate)); fflush(stdout);

	return prs;
}

Parse Parser_Program(String_t *code) {
	Parse tok_sep(String_t *code) {
		return Parser.Choise(
			Parser_Token,
			Parser_Separator,
			code
		);
	}

	return Parser.Many0(tok_sep, code);
}

void main(const int32_t argc, uint8_t *argv[]) {
	Parser.ParseTest(Parser_Program, String.FromFile(argv[1]));
}
