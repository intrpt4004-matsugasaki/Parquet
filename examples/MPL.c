#include <Scraper.h>

Parse Parser_Comment(String_t *code) {
	Parse open(String_t *str) {
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

	Parse close(String_t *str) {
		return Primitive.Char.Char('}', code);
	}

	Parse line(String_t *code) {
		return Parser.Bind3(
			open,
			content,
			close,
			code
		);
	}

	Parse block(String_t *code) {
		Parse nonClose(String_t *code) {
			Parse nonaster(String_t *code) {
				return Primitive.Char.NoneOf(
					String.New(u8"*"),
					code
				);
			}

			Parse nonasterseq(String_t *code) {
				return Parser.Many0(nonaster, code);
			}

			Parse aster(String_t *code) {
				return Primitive.Char.Char('*', code);
			}

			Parse slash(String_t *code) {
				return Primitive.Char.Char('/', code);
			}

			return Parser.Bind3(
				nonasterseq,
				aster,
				slash,
				code
			);
		}
	}

return line(code);
	//return Parser.Choise(line, block, code);
}

Parse Parser_Separator(String_t *code) {
	Parse carret(String_t *str) {
		return Primitive.Char.Char('\r', code);
	}

	Parse feedret(String_t *str) {
		return Primitive.String.Match(
			String.New(u8"\n\r"),
			code
		);
	}

	Parse newline(String_t *code) {
		return Parser.Choise3(
			Primitive.Char.EndOfLine,
			carret,
			feedret,
			code
		);
	}

	return Parser.Choise4(
		Primitive.Char.Space,
		Primitive.Char.Tab,
		newline,
		Parser_Comment,
		code
	);
}

Parse Parser_Digit(String_t *code) {
	return Primitive.Char.Digit(code);
}

Parse Parser_Alphabet(String_t *code) {
	return Primitive.Char.Letter(code);
}

Parse Parser_Symbol(String_t *code) {
	Parse add_sub_mul_eq_lt_gt_open_close_openb_closeb_dot(String_t *str) {
		return Primitive.Char.OneOf(
			String.New(u8"+-*=<>()[].,:;"),
			code
		);
	}

	Parse not_leq_geq_subst(String_t *str) {
		List_t *syms = List.New();
		syms->Add(syms, String.New(u8"<>"));
		syms->Add(syms, String.New(u8"<="));
		syms->Add(syms, String.New(u8">="));
		syms->Add(syms, String.New(u8":="));

		return Primitive.String.OneOf(
			syms,
			code
		);
	}

	return Parser.Choise(
		add_sub_mul_eq_lt_gt_open_close_openb_closeb_dot,
		not_leq_geq_subst,
		code
	);
}

Parse Parser_String(String_t *code) {
	Parse apostr(String_t *str) {
		return Primitive.Char.Char('\'', code);
	}

	Parse nonapostr(String_t *code) {
		return Primitive.Char.NoneOf(
			String.New(u8"\'"),
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

Parse Parser_UInt(String_t *code) {
	return Parser.Many1(Parser_Digit, code);
}

Parse Parser_Keyword(String_t *code) {
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

Parse Parser_Name(String_t *code) {
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

  printf("(%s)", String.GetPrimitive(prs.Precipitate)); fflush(stdout);

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
	for (;;) {
		uint8_t str[256];
		scanf("%s", str);
		Parser.ParseTest(Parser_Keyword, String.New(str));
	}

	//Parser.ParseTest(Parser_Program, String.FromFile(argv[1]));
}
