#include "MPLParser.h"

//static AST_t *ast;
static uint32_t lineNum;

static Result_t Parser_String(String_t *code) {
	Result_t apostrophe(String_t *code) {
		return Parser.Char.Match('\'', code);
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
			return Parser.Char.Match('{', code);
		}

		Result_t content(String_t *code) {
			Result_t nonClose(String_t *code) {
				return Parser.Char.UnMatch('}', code);
			}

			return Combinator.Many0(nonClose, code);
		}

		Result_t close(String_t *code) {
			return Parser.Char.Match('}', code);
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

static Result_t _Separators0(String_t *s) {
	return Combinator.Many0(Parser_Separator, s);
}

static Result_t _fix(Result_t (* parser)(String_t *), String_t *s) {
	return Combinator.Bind(_Separators0, parser, s);
}

static Result_t Bind(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), String_t *s) {
	Result_t _fst(String_t *s) {
		return _fix(fst, s);
	}

	Result_t _snd(String_t *s) {
		return _fix(snd, s);
	}

	return Combinator.Bind(
		_fst, _snd,

		s
	);
}

static Result_t Bind3(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), String_t *s) {
	Result_t _fst(String_t *s) {
		return _fix(fst, s);
	}

	Result_t _snd(String_t *s) {
		return _fix(snd, s);
	}

	Result_t _trd(String_t *s) {
		return _fix(trd, s);
	}

	return Combinator.Bind3(
		_fst, _snd, _trd,

		s
	);
}

static Result_t Bind4(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), String_t *s) {
	Result_t _fst(String_t *s) {
		return _fix(fst, s);
	}

	Result_t _snd(String_t *s) {
		return _fix(snd, s);
	}

	Result_t _trd(String_t *s) {
		return _fix(trd, s);
	}

	Result_t _fth(String_t *s) {
		return _fix(fth, s);
	}

	return Combinator.Bind4(
		_fst, _snd, _trd, _fth,

		s
	);
}

static Result_t Bind5(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), Result_t (* fif)(String_t *), String_t *s) {
	Result_t _fst(String_t *s) {
		return _fix(fst, s);
	}

	Result_t _snd(String_t *s) {
		return _fix(snd, s);
	}

	Result_t _trd(String_t *s) {
		return _fix(trd, s);
	}

	Result_t _fth(String_t *s) {
		return _fix(fth, s);
	}

	Result_t _fif(String_t *s) {
		return _fix(fif, s);
	}

	return Combinator.Bind5(
		_fst, _snd, _trd, _fth, _fif,

		s
	);
}

static Result_t Bind6(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), Result_t (* fif)(String_t *), Result_t (* sth)(String_t *), String_t *s) {
	Result_t _fst(String_t *s) {
		return _fix(fst, s);
	}

	Result_t _snd(String_t *s) {
		return _fix(snd, s);
	}

	Result_t _trd(String_t *s) {
		return _fix(trd, s);
	}

	Result_t _fth(String_t *s) {
		return _fix(fth, s);
	}

	Result_t _fif(String_t *s) {
		return _fix(fif, s);
	}

	Result_t _sth(String_t *s) {
		return _fix(sth, s);
	}

	return Combinator.Bind6(
		_fst, _snd, _trd, _fth, _fif, _sth,

		s
	);
}

static Result_t Bind7(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), Result_t (* fif)(String_t *), Result_t (* sth)(String_t *), Result_t (* svn)(String_t *), String_t *s) {
	Result_t _fst(String_t *s) {
		return _fix(fst, s);
	}

	Result_t _snd(String_t *s) {
		return _fix(snd, s);
	}

	Result_t _trd(String_t *s) {
		return _fix(trd, s);
	}

	Result_t _fth(String_t *s) {
		return _fix(fth, s);
	}

	Result_t _fif(String_t *s) {
		return _fix(fif, s);
	}

	Result_t _sth(String_t *s) {
		return _fix(sth, s);
	}

	Result_t _svn(String_t *s) {
		return _fix(svn, s);
	}

	Result_t _binds(String_t *s) {
		return Combinator.Bind6(
			_fst, _snd, _trd, _fth, _fif, _sth,

			s
		);
	}

	return Combinator.Bind(_binds, _svn, s);
}

static Result_t Choise(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), String_t *s) {
	Result_t Choise_body(String_t *s) {
		return Combinator.Choise(fst, snd, s);
	}

	return _fix(Choise_body, s);
}

static Result_t Choise3(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), String_t *s) {
	Result_t Choise3_body(String_t *s) {
		return Combinator.Choise3(fst, snd, trd, s);
	}

	return _fix(Choise3_body, s);
}

static Result_t Choise4(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), String_t *s) {
	Result_t Choise4_body(String_t *s) {
		return Combinator.Choise4(fst, snd, trd, fth, s);
	}

	return _fix(Choise4_body, s);
}

static Result_t Choise5(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), Result_t (* fif)(String_t *), String_t *s) {
	Result_t Choise5_body(String_t *s) {
		return Combinator.Choise5(fst, snd, trd, fth, fif, s);
	}

	return _fix(Choise5_body, s);
}

static Result_t Choise6(Result_t (* fst)(String_t *), Result_t (* snd)(String_t *), Result_t (* trd)(String_t *), Result_t (* fth)(String_t *), Result_t (* fif)(String_t *), Result_t (* sth)(String_t *), String_t *s) {
	Result_t Choise6_body(String_t *s) {
		return Combinator.Choise6(fst, snd, trd, fth, fif, sth, s);
	}

	return _fix(Choise6_body, s);
}


static Result_t Choise10(
	Result_t (* p1)(String_t *), Result_t (* p2)(String_t *),
	Result_t (* p3)(String_t *), Result_t (* p4)(String_t *),
	Result_t (* p5)(String_t *), Result_t (* p6)(String_t *),
	Result_t (* p7)(String_t *), Result_t (* p8)(String_t *),
	Result_t (* p9)(String_t *), Result_t (* p10)(String_t *), String_t *s) {
	Result_t Choise6_body(String_t *s) {
		return Choise6(p1, p2, p3, p4, p5, p6, s);
	}

	Result_t Choise4_body(String_t *s) {
		return Choise4(p7, p8, p9, p10, s);
	}

	return Choise(
		Choise6_body,
		Choise4_body,

		s
	);
}

static Result_t Many0(Result_t (* parser)(String_t *), String_t *s) {
	Result_t Many0_body(String_t *s) {
		return Combinator.Many0(parser, s);
	}

	return _fix(Many0_body, s);
}

static Result_t Many1(Result_t (* parser)(String_t *), String_t *s) {
	Result_t Many1_body(String_t *s) {
		return Combinator.Many1(parser, s);
	}

	return _fix(Many1_body, s);
}

static Result_t Parser_VarName(String_t *code) {
	return Parser_Name(code);
}

static Result_t Parser_ProcName(String_t *code) {
	return Parser_Name(code);
}

static Result_t Parser_StdType(String_t *code) {
	List_t *types = List.New();
	types->Add(types, String.New(u8"integer"));
	types->Add(types, String.New(u8"boolean"));
	types->Add(types, String.New(u8"char"));

	return Parser.String.OneOf(types, code);
}

static Result_t Parser_AddOpr(String_t *code) {
	List_t *adds = List.New();
	adds->Add(adds, String.New(u8"or"));
	adds->Add(adds, String.New(u8"+"));
	adds->Add(adds, String.New(u8"-"));

	return Parser.String.OneOf(adds, code);
}

static Result_t Parser_MulOpr(String_t *code) {
	List_t *muls = List.New();
	muls->Add(muls, String.New(u8"and"));
	muls->Add(muls, String.New(u8"div"));
	muls->Add(muls, String.New(u8"*"));

	return Parser.String.OneOf(muls, code);
}

static Result_t Parser_Const(String_t *code) {
	Result_t false_kwd(String_t *code) {
		return Parser.String.Match(String.New(u8"false"), code);
	}

	Result_t true_kwd(String_t *code) {
		return Parser.String.Match(String.New(u8"true"), code);
	}

	return Choise4(
		Parser_UInt,
		false_kwd,
		true_kwd,
		Parser_String,

		code
	);
}

static Result_t Parser_Var(String_t *code);
static Result_t Parser_Expr(String_t *code);
static Result_t Parser_Factor(String_t *code) {
	Result_t exprZ(String_t *code) {
		Result_t open(String_t *code) {
			return Parser.Char.Match('(', code);
		}

		Result_t close(String_t *code) {
			return Parser.Char.Match(')', code);
		}

		return Bind3(
			open, Parser_Expr, close,

			code
		);
	}

	Result_t invFactor(String_t *code) {
		Result_t not(String_t *code) {
			return Parser.String.Match(String.New(u8"not"), code);
		}

		return Bind(
			not, Parser_Factor,

			code
		);
	}

	Result_t stdTexprZ(String_t *code) {
		Result_t open(String_t *code) {
			return Parser.Char.Match('(', code);
		}

		Result_t close(String_t *code) {
			return Parser.Char.Match(')', code);
		}

		return Bind4(
			Parser_StdType, open, Parser_Expr, close,

			code
		);
	}

	return Choise5(
		Parser_Var,
		Parser_Const,
		exprZ,
		invFactor,
		stdTexprZ,

		code
	);
}

static Result_t Parser_Term(String_t *code) {
	Result_t adtnTerms0(String_t *code) {
		Result_t adtnTerm(String_t *code) {
			return Bind(
				Parser_MulOpr, Parser_Factor,

				code
			);
		}

		return Many0(adtnTerm, code);
	}

	return Bind(
		Parser_Factor, adtnTerms0,

		code
	);
}

static Result_t Parser_Var(String_t *code) {
	Result_t arrayIndexX(String_t *code) {
		Result_t arrayIndex(String_t *code) {
			Result_t open(String_t *code) {
				return Parser.Char.Match('[', code);
			}

			Result_t close(String_t *code) {
				return Parser.Char.Match(']', code);
			}

			return Bind3(
				open, Parser_Expr, close,

				code
			);
		}

		return Combinator.Possibly(arrayIndex, code);
	}

	return Bind(
		Parser_VarName, arrayIndexX,

		code
	);
}

static Result_t Parser_LeftPart(String_t *code) {
	return Parser_Var(code);
}

static Result_t Parser_SimpleExpr(String_t *code) {
	Result_t plus_or_minus(String_t *code) {
		Result_t plus(String_t *code) {
			return Parser.Char.Match('+', code);
		}

		Result_t minus(String_t *code) {
			return Parser.Char.Match('-', code);
		}

		return Choise(
			plus,
			minus,

			code
		);
	}

	Result_t plus_or_minusX(String_t *code) {
		return Combinator.Possibly(plus_or_minus, code);
	}

	Result_t adtnAdds0(String_t *code) {
		Result_t adtnAdd(String_t *code) {
			return Bind(
				Parser_AddOpr, Parser_Term,

				code
			);
		}

		return Many0(adtnAdd, code);
	} 

	return Bind3(
		plus_or_minusX, Parser_Term, adtnAdds0,

		code
	);
}

static Result_t Parser_RelOpr(String_t *code) {
	List_t *rels = List.New();
	rels->Add(rels, String.New(u8"<>"));
	rels->Add(rels, String.New(u8"<="));
	rels->Add(rels, String.New(u8">="));
	rels->Add(rels, String.New(u8"="));
	rels->Add(rels, String.New(u8"<"));
	rels->Add(rels, String.New(u8">"));

	return Parser.String.OneOf(rels, code);
}

static Result_t Parser_Expr(String_t *code) {
	Result_t adtnSufExpr0(String_t *code) {
		Result_t adtnSufExpr(String_t *code) {
			return Bind(
				Parser_RelOpr, Parser_SimpleExpr,

				code
			);
		}

		return Many0(adtnSufExpr, code);
	}

	return Bind(
		Parser_SimpleExpr, adtnSufExpr0,

		code
	);
}

static Result_t Parser_AssignStmt(String_t *code) {
	Result_t assign(String_t *code) {
		return Parser.String.Match(String.New(u8":="), code);
	}

	return Bind3(
		Parser_LeftPart, assign, Parser_Expr,

		code
	);
}

static Result_t Parser_Stmt(String_t *code);
static Result_t Parser_CondStmt(String_t *code) {
	Result_t if_kwd(String_t *code) {
		return Parser.String.Match(String.New(u8"if"), code);
	}

	Result_t then_kwd(String_t *code) {
		return Parser.String.Match(String.New(u8"then"), code);
	}

	Result_t elseSecX(String_t *code) {
		Result_t elseSec(String_t *code) {
			Result_t else_kwd(String_t *code) {
				return Parser.String.Match(String.New(u8"else"), code);
			}

			return Bind(
				else_kwd, Parser_Stmt,

				code
			);
		}

		return Combinator.Possibly(elseSec, code);
	}

	return Bind5(
		if_kwd, Parser_Expr, then_kwd, Parser_Stmt, elseSecX,

		code
	);
}

static Result_t Parser_IterStmt(String_t *code) {
	Result_t while_kwd(String_t *code) {
		return Parser.String.Match(String.New(u8"while"), code);
	}

	Result_t do_kwd(String_t *code) {
		return Parser.String.Match(String.New(u8"do"), code);
	}

	return Bind4(
		while_kwd, Parser_Expr, do_kwd, Parser_Stmt,

		code
	);
}

static Result_t Parser_ExitStmt(String_t *code) {
	return Parser.String.Match(String.New(u8"break"), code);
}

static Result_t Parser_Exprs(String_t *code) {
	Result_t adtnExprs0(String_t *code) {
		Result_t adtnExpr(String_t *code) {
			Result_t comma(String_t *code) {
				return Parser.Char.Match(',', code);
			}

			return Bind(
				comma, Parser_Expr,
				code
			);
		}

		return Many0(adtnExpr, code);
	}

	return Bind(
		Parser_Expr, adtnExprs0,

		code
	);
}

static Result_t Parser_CallStmt(String_t *code) {
	Result_t call(String_t *code) {
		return Parser.String.Match(String.New(u8"if"), code);
	}

	Result_t paramX(String_t *code) {
		Result_t param(String_t *code) {
			Result_t open(String_t *code) {
				return Parser.Char.Match('(', code);
			}

			Result_t close(String_t *code) {
				return Parser.Char.Match(')', code);
			}

			return Bind3(
				open, Parser_Exprs, close,

				code
			);
		}

		return Combinator.Possibly(param, code);
	}

	return Bind3(
		call, Parser_ProcName, paramX,

		code
	);
}

static Result_t Parser_RetStmt(String_t *code) {
	return Parser.String.Match(String.New(u8"return"), code);
}

static Result_t Parser_InputStmt(String_t *code) {
	Result_t embeddedInst(String_t *code) {
		List_t *insts = List.New();
		insts->Add(insts, String.New(u8"readln"));
		insts->Add(insts, String.New(u8"read"));

		return Parser.String.OneOf(insts, code);
	}

	Result_t paramX(String_t *code) {
		Result_t param(String_t *code) {
			Result_t open(String_t *code) {
				return Parser.Char.Match('(', code);
			}

			Result_t adtnVars0(String_t *code) {
				Result_t adtnVar(String_t *code) {
					Result_t comma(String_t *code) {
						return Parser.Char.Match(',', code);
					}

					return Bind(
						comma, Parser_Var,

						code
					);
				}

				return Many0(adtnVar, code);
			}

			Result_t close(String_t *code) {
				return Parser.Char.Match(')', code);
			}

			return Bind4(
				open, Parser_Var, adtnVars0, close,

				code
			);
		}

		return Combinator.Possibly(param, code);
	}

	return Bind(
		embeddedInst, paramX,

		code
	);
}

static Result_t Parser_OutputStmt(String_t *code) {
	Result_t number(String_t *code) {
		Result_t optX(String_t *code) {
			Result_t opt(String_t *code) {
				Result_t colon(String_t *code) {
					return Parser.Char.Match(':', code);
				}

				return Bind(
					colon, Parser_UInt,

					code
				);
			}

			return Combinator.Possibly(opt, code);
		}

		return Bind(
			Parser_Expr, optX,

			code
		);
	}

	return Choise(
		number,
		Parser_String,

		code
	);
}

static Result_t Parser_OutputFmt(String_t *code) {
	Result_t embeddedInst(String_t *code) {
		List_t *insts = List.New();
		insts->Add(insts, String.New(u8"writeln"));
		insts->Add(insts, String.New(u8"write"));

		return Parser.String.OneOf(insts, code);
	}

	Result_t paramX(String_t *code) {
		Result_t param(String_t *code) {
			Result_t open(String_t *code) {
				return Parser.Char.Match('(', code);
			}

			Result_t adtnOutputFmts0(String_t *code) {
				Result_t adtnOutputFmt(String_t *code) {
					Result_t comma(String_t *code) {
						return Parser.Char.Match(',', code);
					}

					return Bind(
						comma, Parser_OutputFmt,

						code
					);
				}

				return Many0(adtnOutputFmt, code);
			}

			Result_t close(String_t *code) {
				return Parser.Char.Match(')', code);
			}

			return Bind4(
				open, Parser_OutputFmt, adtnOutputFmts0, close,

				code
			);
		}

		return Combinator.Possibly(param, code);
	}

	return Bind(
		embeddedInst, paramX,

		code
	);
}

static Result_t Parser_Stmt(String_t *code);
static Result_t Parser_CompoundStmt(String_t *code) {
	Result_t begin(String_t *code) {
		return Parser.String.Match(String.New(u8"begin"), code);
	}

	Result_t adtnStmts(String_t *code) {
		Result_t semicolon(String_t *code) {
			return Parser.Char.Match(';', code);
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

static Result_t Parser_EmptyStmt(String_t *code) {
	return Basis.Ok(code);
}

static Result_t Parser_Stmt(String_t *code) {
	return Choise10(
		Parser_AssignStmt,
		Parser_CondStmt,
		Parser_IterStmt,
		Parser_ExitStmt,
		Parser_CallStmt,
		Parser_RetStmt,
		Parser_InputStmt,
		Parser_OutputStmt,
		Parser_CompoundStmt,
		Parser_EmptyStmt,

		code
	);
}

static Result_t Parser_VarNames(String_t *code) {
	Result_t adtnVarNames(String_t *code) {
		Result_t comma(String_t *code) {
			return Parser.Char.Match(',', code);
		}

		return Bind(
			comma, Parser_VarName,

			code
		);
	}

	return Bind(Parser_VarName, adtnVarNames, code);
}

static Result_t Parser_ArrType(String_t *code) {
	Result_t array(String_t *code) {
		return Parser.String.Match(String.New(u8"array"), code);
	}

	Result_t open(String_t *code) {
		return Parser.Char.Match('[', code);
	}

	Result_t close(String_t *code) {
		return Parser.Char.Match(']', code);
	}

	Result_t of(String_t *code) {
		return Parser.String.Match(String.New(u8"of"), code);
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

static Result_t Parser_VarDecl(String_t *code) {
	Result_t var(String_t *code) {
		return Parser.String.Match(String.New(u8"var"), code);
	}

	Result_t VarDecl(String_t *code) {
		Result_t colon(String_t *code) {
			return Parser.Char.Match(':', code);
		}

		Result_t semicolon(String_t *code) {
			return Parser.Char.Match(';', code);
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

static Result_t Parser_FormalParam(String_t *code) {
	Result_t open(String_t *code) {
		return Parser.Char.Match('(', code);
	}

	Result_t colon(String_t *code) {
		return Parser.Char.Match(':', code);
	}

	Result_t adtnParams(String_t *code) {
		Result_t semicolon(String_t *code) {
			return Parser.Char.Match(';', code);
		}

		Result_t adtnParam(String_t *code) {
			return Bind4(
				semicolon, Parser_VarNames, colon, Parser_Type,

				code
			);
		}

		return Many0(adtnParam, code);
	}

	Result_t close(String_t *code) {
		return Parser.Char.Match(')', code);
	}

	return Bind6(
		open, Parser_VarNames, colon, Parser_Type,
		adtnParams, close,

		code
	);
}

static Result_t Parser_SubProgDecl(String_t *code) {
	Result_t procedure(String_t *code) {
		return Parser.String.Match(String.New(u8"procedure"), code);
	}

	Result_t Parser_FormalParamX(String_t *code) {
		return Combinator.Possibly(Parser_FormalParam, code);
	}

	Result_t semicolon(String_t *code) {
		return Parser.Char.Match(';', code);
	}

	Result_t Parser_VarDeclX(String_t *code) {
		return Combinator.Possibly(Parser_VarDecl, code);
	}

	return Bind7(
		procedure, Parser_ProcName, Parser_FormalParamX, semicolon,
			Parser_VarDeclX,
			Parser_CompoundStmt,
		semicolon,

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
			return Parser.Char.UnMatch(';', code);
		}

		return Many1(nonsemic, code);
	}

	Result_t semicolon(String_t *code) {
		return Parser.Char.Match(';', code);
	}

	Result_t end(String_t *code) {
		return Parser.String.Match(String.New(u8"end"), code);
	}

	Result_t dot(String_t *code) {
		return Parser.Char.Match('.', code);
	}

	return Bind7(
		program, name, semicolon,
		Parser_Block,
		end, dot, _Separators0,

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
