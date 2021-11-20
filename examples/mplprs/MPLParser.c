#include "MPLParser.h"

//static AST_t *ast;
static uint32_t lineNum;

static Result_t Parser_String(String_t *code) {
	Result_t apostrophe(String_t *code) {
		return Parser.Char.Char('\'', code);
	}

	Result_t content(String_t *code) {
		Result_t nonApostrophe(String_t *code) {
			return Parser.Char.NoneOf(
				String.New(u8"'"),
				code
			);
		}

		return Combinator.Many0(nonApostrophe, code);
	}

	Result_t result = Combinator.Bind3(
		apostrophe,
		content,
		apostrophe,
		code
	);

/****************************************/
	if (result.Reply == Succeeded)
		;
/****************************************/

	return result;
}

static Result_t Parser_UInt(String_t *code) {
	Result_t result = Combinator.Many1(Parser.Char.Digit, code);

/****************************************/
	if (result.Reply == Succeeded)
		;
/****************************************/

	return result;
}

static Result_t Parser_Name(String_t *code) {
	Result_t AlphaNums0(String_t *code) {
		return Combinator.Many0(Parser.Char.AlphaNum, code);
	}

	Result_t result = Combinator.Bind(
		Parser.Char.Letter, AlphaNums0,

		code
	);

/****************************************/
	if (result.Reply == Succeeded)
		;
/****************************************/

	return result;
}

static Result_t Parser_Comment(String_t *code) {
	Result_t line(String_t *code) {
		Result_t open(String_t *code) {
			return Parser.Char.Char('{', code);
		}

		Result_t content(String_t *code) {
			Result_t nonClose(String_t *code) {
				return Parser.Char.NonChar('}', code);
			}

			return Combinator.Many0(nonClose, code);
		}

		Result_t close(String_t *code) {
			return Parser.Char.Char('}', code);
		}

		return Combinator.Bind3(
			open, content, close,

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

		Result_t content(String_t *code) {
			Result_t nonClose(String_t *code) {
				return Parser.String.UnMatch(
					String.New(u8"*/"),
					code
				);
			}

			return Combinator.Many0(nonClose, code);
		}

		Result_t close(String_t *code) {
			return Parser.String.Match(
				String.New(u8"*/"),
				code
			);
		}

		return Combinator.Bind3(
			open, content, close,

			code
		);
	}

	return Combinator.Choise(line, block, code);
}

static Result_t Parser_Separator(String_t *code) {
	Result_t space_or_tab(String_t *code) {
		return Combinator.Choise(
			Parser.Char.Space,
			Parser.Char.Tab,

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
		space_or_tab,
		newline,
		Parser_Comment,

		code
	); 
}

static Result_t _Separators0(String_t *code) {
	return Combinator.Many0(Parser_Separator, code);
}

static _fix(Result_t (* parser)(String_t *), String_t *code) {
	return Combinator.Bind(_Separators0, parser, code);
}

static Result_t Bind(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), String_t *s) {
	Result_t _fst(String_t *code) {
		return _fix(fst, code);
	}

	Result_t _snd(String_t *code) {
		return _fix(snd, code);
	}

	return Combinator.Bind(
		_fst, _snd,

		s
	);
}

static Result_t Bind3(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), String_t *s) {
	Result_t _fst(String_t *code) {
		return _fix(fst, code);
	}

	Result_t _snd(String_t *code) {
		return _fix(snd, code);
	}

	Result_t _trd(String_t *code) {
		return _fix(trd, code);
	}

	return Combinator.Bind3(
		_fst, _snd, _trd,

		s
	);
}

static Result_t Bind4(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), String_t *s) {
	Result_t _fst(String_t *code) {
		return _fix(fst, code);
	}

	Result_t _snd(String_t *code) {
		return _fix(snd, code);
	}

	Result_t _trd(String_t *code) {
		return _fix(trd, code);
	}

	Result_t _fth(String_t *code) {
		return _fix(fth, code);
	}

	return Combinator.Bind4(
		_fst, _snd, _trd, _fth,

		s
	);
}

static Result_t Bind5(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), Result_t (* fif)(String_t *), String_t *s) {
	Result_t _fst(String_t *code) {
		return _fix(fst, code);
	}

	Result_t _snd(String_t *code) {
		return _fix(snd, code);
	}

	Result_t _trd(String_t *code) {
		return _fix(trd, code);
	}

	Result_t _fth(String_t *code) {
		return _fix(fth, code);
	}

	Result_t _fif(String_t *code) {
		return _fix(fif, code);
	}

	return Combinator.Bind5(
		_fst, _snd, _trd, _fth, _fif,

		s
	);
}

static Result_t Bind6(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), Result_t (* fif)(String_t *), Result_t (* sth)(String_t *), String_t *s) {
	Result_t _fst(String_t *code) {
		return _fix(fst, code);
	}

	Result_t _snd(String_t *code) {
		return _fix(snd, code);
	}

	Result_t _trd(String_t *code) {
		return _fix(trd, code);
	}

	Result_t _fth(String_t *code) {
		return _fix(fth, code);
	}

	Result_t _fif(String_t *code) {
		return _fix(fif, code);
	}

	Result_t _sth(String_t *code) {
		return _fix(sth, code);
	}

	return Combinator.Bind6(
		_fst, _snd, _trd, _fth, _fif, _sth,

		s
	);
}

static Result_t Bind7(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), Result_t (* fif)(String_t *), Result_t (* sth)(String_t *), Result_t (* svn)(String_t *), String_t *s) {
	Result_t _fst(String_t *code) {
		return _fix(fst, code);
	}

	Result_t _snd(String_t *code) {
		return _fix(snd, code);
	}

	Result_t _trd(String_t *code) {
		return _fix(trd, code);
	}

	Result_t _fth(String_t *code) {
		return _fix(fth, code);
	}

	Result_t _fif(String_t *code) {
		return _fix(fif, code);
	}

	Result_t _sth(String_t *code) {
		return _fix(sth, code);
	}

	Result_t _svn(String_t *code) {
		return _fix(svn, code);
	}

	Result_t _binds(String_t *code) {
		return Combinator.Bind6(
			_fst, _snd, _trd, _fth, _fif, _sth,

			s
		);
	}

	return Combinator.Bind(_binds, _svn, s);
}

static Result_t Choise(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), String_t *s) {
	Result_t Choise_body(String_t *code) {
		return Combinator.Choise(fst, snd, s);
	}

	return _fix(Choise_body, s);
}

static Result_t Choise3(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), String_t *s) {
	Result_t Choise3_body(String_t *code) {
		return Combinator.Choise3(fst, snd, trd, s);
	}

	return _fix(Choise3_body, s);
}

static Result_t Choise4(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), String_t *s) {
	Result_t Choise4_body(String_t *code) {
		return Combinator.Choise4(fst, snd, trd, fth, s);
	}

	return _fix(Choise4_body, s);
}

static Result_t Choise5(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), Result_t (* fif)(String_t *), String_t *s) {
	Result_t Choise5_body(String_t *code) {
		return Combinator.Choise5(fst, snd, trd, fth, fif, s);
	}

	return _fix(Choise5_body, s);
}

static Result_t Choise6(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), Result_t (* fif)(String_t *), Result_t (* sth)(String_t *), String_t *s) {
	Result_t Choise6_body(String_t *code) {
		return Combinator.Choise6(fst, snd, trd, fth, fif, sth, s);
	}

	return _fix(Choise6_body, s);
}

static Result_t Many0(Result_t (* parser)(String_t *), String_t *s) {
	Result_t Many0_body(String_t *) {
		return Combinator.Many0(parser, code);
	}

	return _fix(Many0_body, s);
}

static Result_t Many1(Result_t (* parser)(String_t *), String_t *s) {
	Result_t Many1_body(String_t *) {
		return Combinator.Many1(parser, code);
	}

	return _fix(Many1_body, s);
}

static Result_t Parser_EmptyStmt(String_t *code) {
	return Basis.Ok(code);
}

static Result_t Parser_VarName(String_t *code) {
	return Parser_Name(code);
}

static Result_t Parser_VarNames(String_t *code) {
	Result_t adtnVarNames(String_t *code) {
		Result_t comma(String_t *code) {
			return Parser.Char.Char(',', code);
		}

		return Bind(
			comma, Parser_VarName,

			code
		);
	}

	return Bind(Parser_VarName, adtnVarNames, code);
}

static Result_t Parser_StdType(String_t *code) {
	List_t *types = List.New();
	types->Add(types, String.New(u8"integer"));
	types->Add(types, String.New(u8"boolean"));
	types->Add(types, String.New(u8"char"));

	return Parser.String.OneOf(types, code);
}

static Result_t Parser_ArrType(String_t *code) {
	Result_t array(String_t *code) {
		return Parser.String.Match(u8"array", code);
	}

	Result_t open(String_t *code) {
		return Parser.Char.Char('[', code);
	}

	Result_t close(String_t *code) {
		return Parser.Char.Char(']', code);
	}

	Result_t of(String_t *code) {
		return Parser.String.Match(u8"of", code);
	}

	return Bind6(
		array, open, Parser_UInt, close, of, Parser_StdType,

		code
	);
}

static Result_t Parser_Type(String_t *code) {
	return Combinator.Choise(
		Parser_StdType,
		Parser_ArrType,

		code
	);
}

static Result_t Parser_Stmt(String_t *code) {

}

static Result_t Parser_VarDecl(String_t *code) {
	Result_t var(String_t *code) {
		return Parser.String.Match(String.New(u8"var"), code);
	}

	Result_t VarDecl(String_t *code) {
		Result_t colon(String_t *code) {
			return Parser.Char.Char(':', code);
		}

		Result_t semicolon(String_t *code) {
			return Parser.Char.Char(';', code);
		}

		return Bind4(
			Parser_VarNames, colon, Parser_Type, semicolon,

			code
		);
	}

	Result_t VarDecls(String_t *code) {
		return Many0(VarDecl, code);
	}

	return Bind3(
		var, VarDecl,
		VarDecls,

		code
	);
}

static Result_t Parser_SubProgDecl(String_t *code) {
	Result_t procedure(String_t *code) {
		return Parser.String.Match(String.New(u8"procedure"), code);
	}

	Result_t Parser_FormalParamX(String_t *code) {
		Result_t result = Parser_FormalParam(code);
		return (result.Reply == Failed) ?
			Basis.Ok(code) : result;
	}

	Result_t semicolon(String_t *code) {
		return Parser.Char.Char(';', code);
	}

	Result_t Parser_VarDeclX(String_t *code) {
		Result_t result = Parser_VarDecl(code);
		return (result.Reply == Failed) ?
			Basis.Ok(code) : result;
	}

	return Bind7(
		procedure, Parser_ProcName, Parser_FormalParamX, semicolon,
			Parser_VarDeclX,
			Parser_CompoundStmt,
		semicolon

		code
	);
}

static Result_t Parser_CompoundStmt(String_t *code) {
	Result_t begin(String_t *code) {
		return Parser.String.Match(String.New(u8"begin"), code);
	}

	Result_t adtnStmts(String_t *code) {
		Result_t semicolon(String_t *code) {
			return Parser.Char.Char(';', code);
		}

		Result_t adtnStmt(String_t *code) {
			return Bind(
				semicolon, Parser_Stmt,

				code
			);
		}

		return Many0(adtnStmt, code);
	}

	Result_t end(String_t *code) {
		return Parser.String.Match(String.New(u8"end"), code);
	}

	return Bind4(
		begin, Parser_Stmt, adtnStmts, end,
		
		code
	);
}

static Result_t Parser_Block(String_t *code) {
	Result_t VarDecl_or_SubProgDecl(String_t *code) {
		return Choise(
			Parser_VarDecl,
			Parser_SubProgDecl,

			code
		);
	}

	Result_t Repeat_VarDecl_or_SubProgDecl(String_t *code) {
		return Many0(VarDecl_or_SubProgDecl, code);
	}

	return Bind(
		Repeat_VarDecl_or_SubProgDecl,
		Parser_CompoundStmt,

		code
	);
}

static Result_t Parser_Program(String_t *code) {
	Result_t program(String_t *code) {
		Parser.String.Match(String.New(u8"program"), code);
	}

	Result_t name(String_t *code) {
		Result_t nonsemic(String_t *code) {
			return Parser.Char.NonChar(';', code);
		}

		return Many1(nonsemic, code);
	}

	Result_t semicolon(String_t *code) {
		return Parser.Char.Char(';', code);
	}

	Result_t end(String_t *code) {
		return Parser.String.Match(String.New(u8"end"), code);
	}

	Result_t dot(String_t *code) {
		return Parser.Char.Char('.', code);
	}

	return Bind7(
		program, name, semicolon,
		Parser_Block,
		end, dot, _Separators0

		code
	);
}

static ParseResult_t Execute(String_t *code) {
	lineNum = 1;

	Result_t result = Invoker.Parse(Parser_Program, code);

	return (ParseResult_t){
		.Succeeded		= result.Reply == Succeeded,
		.ErrorLine		= lineNum,
		.Precipitate	= result.Precipitate,
		.Subsequent		= result.Subsequent,
	};
}

_MPLParser MPLParser = {
	.Execute = Execute,
};
