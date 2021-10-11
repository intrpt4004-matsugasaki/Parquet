#include <Scraper.h>

Parse Parser_Comment(String_t *code) {
	Parse line(String_t *code) {
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

	return Parser.Choise(line, block, code);
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
			String.New(u8"+-*=<>()[]."),
			code
		);
	}

	// List実装で OneOf :: [String] -> String -> Parse
	Parse not(String_t *str) {
		return Primitive.String.Match(
			String.New(u8"<>"),
			code
		);
	}

	Parse leq(String_t *str) {
		return Primitive.String.Match(
			String.New(u8"<="),
			code
		);
	}

	Parse geq(String_t *str) {
		return Primitive.String.Match(
			String.New(u8">="),
			code
		);
	}

	Parse subst(String_t *str) {
		return Primitive.String.Match(
			String.New(u8":="),
			code
		);
	}

	return Parser.Choise5(
		add_sub_mul_eq_lt_gt_open_close_openb_closeb_dot,
		not,
		leq,
		geq,
		subst,
		code
	);
}

Parse Parser_String(String_t *code) {
	/*Primitive.Char.Char('\'', code)

	//

	Primitive.Char.Char('\'', code)
*/}

Parse Parser_UInt(String_t *code) {
	return Parser.Many1(Parser_Digit, code);
}

Parse Parser_Keyword(String_t *code) {
	Parse program(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"program"),
			code
		);
	}

	Parse var(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"var"),
			code
		);
	}

	Parse array(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"array"),
			code
		);
	}

	Parse of(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"of"),
			code
		);
	}

	Parse begin(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"begin"),
			code
		);
	}

	Parse end(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"end"),
			code
		);
	}

	Parse program_var_array_of_begin_end(String_t *code) {
		return Parser.Choise5(
			program,
			var,
			array,
			of,
			end,
			code
		);
	}

	Parse if_(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"if"),
			code
		);
	}

	Parse then(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"then"),
			code
		);
	}

	Parse else_(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"else"),
			code
		);
	}

	Parse procedure(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"procedure"),
			code
		);
	}

	Parse return_(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"return"),
			code
		);
	}

	Parse call(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"call"),
			code
		);
	}

	Parse if_then_else_procedure_return_call(String_t *code) {
		return Parser.Choise6(
			if_,
			then,
			else_,
			procedure,
			return_,
			call,
			code
		);
	}

	Parse while_(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"while"),
			code
		);
	}

	Parse do_(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"do"),
			code
		);
	}

	Parse not(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"not"),
			code
		);
	}

	Parse or(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"or"),
			code
		);
	}

	Parse div(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"div"),
			code
		);
	}

	Parse and(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"and"),
			code
		);
	}

	Parse while_do_not_or_div_and(String_t *code) {
		return Parser.Choise6(
			while_,
			do_,
			not,
			or,
			div,
			and,
			code
		);
	}

	Parse char_(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"char"),
			code
		);
	}

	Parse integer(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"integer"),
			code
		);
	}

	Parse boolean(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"boolean"),
			code
		);
	}

	Parse read(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"read"),
			code
		);
	}

	Parse write(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"write"),
			code
		);
	}

	Parse readln(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"readln"),
			code
		);
	}

	Parse char_integer_boolean_read_write_readln(String_t *code) {
		return Parser.Choise6(
			char_,
			integer,
			boolean,
			read,
			write,
			readln,
			code
		);
	}

	Parse writeln(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"writeln"),
			code
		);
	}

	Parse true_(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"true"),
			code
		);
	}

	Parse false_(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"false"),
			code
		);
	}

	Parse break_(String_t *code) {
		return Primitive.String.Match(
			String.New(u8"break"),
			code
		);
	}

	Parse writeln_true_false_break(String_t *code) {
		return Parser.Choise4(
			writeln,
			true_,
			false_,
			break_,
			code
		);
	}

	return Parser.Choise5(
		program_var_array_of_begin_end,
		if_then_else_procedure_return_call,
		while_do_not_or_div_and,
		char_integer_boolean_read_write_readln,
		while_do_not_or_div_and,
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
	return Parser.Choise5(
		Parser_Name,
		Parser_Keyword,
		Parser_UInt,
		Parser_String,
		Parser_Symbol,
		code
	);
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
