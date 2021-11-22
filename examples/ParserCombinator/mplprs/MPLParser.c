#include "MPLParser.h"

//static AST_t *ast;
static uint32_t lineNum;

static Answer_t Parser_String(String_t *s, Processor_t p) {
	Answer_t apostrophe(String_t *s, Processor_t p) {
		return Parsers.Char.Match('\'', s, p);
	}

	Answer_t content(String_t *s, Processor_t p) {
		Answer_t nonApostrophe(String_t *s, Processor_t p) {
			return Parsers.Char.NoneOf(
				String.New(u8"'"),
				s, p
			);
		}

		return Combinator.Many0(nonApostrophe, s, p);
	}

	Answer_t result = Combinator.Bind3(
		apostrophe,
		content,
		apostrophe,
		s, p
	);

/****************************************/
	if (result.Reply == Reply.Ok)
		;
/****************************************/

	return result;
}

static Answer_t Parser_UInt(String_t *s, Processor_t p) {
	Answer_t result = Combinator.Many1(Parsers.Char.Digit, s, p);

/****************************************/
	if (result.Reply == Reply.Ok)
		;
/****************************************/

	return result;
}

static Answer_t Parser_Name(String_t *s, Processor_t p) {
	Answer_t AlphaNums0(String_t *s, Processor_t p) {
		return Combinator.Many0(Parsers.Char.AlphaNum, s, p);
	}

	Answer_t result = Combinator.Bind(
		Parsers.Char.Letter, AlphaNums0,

		s, p
	);

/****************************************/
	if (result.Reply == Reply.Ok)
		;
/****************************************/

	return result;
}

static Answer_t Parser_Comment(String_t *s, Processor_t p) {
	Answer_t line(String_t *s, Processor_t p) {
		Answer_t open(String_t *s, Processor_t p) {
			return Parsers.Char.Match('{', s, p);
		}

		Answer_t content(String_t *s, Processor_t p) {
			Answer_t nonClose(String_t *s, Processor_t p) {
				return Parsers.Char.UnMatch('}', s, p);
			}

			return Combinator.Many0(nonClose, s, p);
		}

		Answer_t close(String_t *s, Processor_t p) {
			return Parsers.Char.Match('}', s, p);
		}

		return Combinator.Bind3(
			open, content, close,

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

		Answer_t content(String_t *s, Processor_t p) {
			Answer_t nonClose(String_t *s, Processor_t p) {
				return Parsers.String.UnMatch(
					String.New(u8"*/"),
					s, p
				);
			}

			return Combinator.Many0(nonClose, s, p);
		}

		Answer_t close(String_t *s, Processor_t p) {
			return Parsers.String.Match(
				String.New(u8"*/"),
				s, p
			);
		}

		return Combinator.Bind3(
			open, content, close,

			s, p
		);
	}

	return Combinator.Choise(line, block, s, p);
}

static Answer_t Parser_Separator(String_t *s, Processor_t p) {
	Answer_t space_or_tab(String_t *s, Processor_t p) {
		return Combinator.Choise(
			Parsers.Char.Space,
			Parsers.Char.Tab,

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
		space_or_tab,
		newline,
		Parser_Comment,

		s, p
	); 
}

static Answer_t _Separators0(String_t *s, Processor_t p) {
	return Combinator.Many0(Parser_Separator, s, p);
}

static Answer_t _fix(Answer_t (* parser)(String_t *, Processor_t), String_t *s, Processor_t p) {
	return Combinator.Bind(_Separators0, parser, s, p);
}

static Answer_t Bind(Answer_t (* fst)(String_t *, Processor_t), Answer_t (* snd)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t _fst(String_t *s, Processor_t p) {
		return _fix(fst, s, p);
	}

	Answer_t _snd(String_t *s, Processor_t p) {
		return _fix(snd, s, p);
	}

	return Combinator.Bind(
		_fst, _snd,

		s, p
	);
}

static Answer_t Bind3(Answer_t (* fst)(String_t *, Processor_t), Answer_t (* snd)(String_t *, Processor_t), Answer_t (* trd)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t _fst(String_t *s, Processor_t p) {
		return _fix(fst, s, p);
	}

	Answer_t _snd(String_t *s, Processor_t p) {
		return _fix(snd, s, p);
	}

	Answer_t _trd(String_t *s, Processor_t p) {
		return _fix(trd, s, p);
	}

	return Combinator.Bind3(
		_fst, _snd, _trd,

		s, p
	);
}

static Answer_t Bind4(Answer_t (* fst)(String_t *, Processor_t), Answer_t (* snd)(String_t *, Processor_t), Answer_t (* trd)(String_t *, Processor_t), Answer_t (* fth)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t _fst(String_t *s, Processor_t p) {
		return _fix(fst, s, p);
	}

	Answer_t _snd(String_t *s, Processor_t p) {
		return _fix(snd, s, p);
	}

	Answer_t _trd(String_t *s, Processor_t p) {
		return _fix(trd, s, p);
	}

	Answer_t _fth(String_t *s, Processor_t p) {
		return _fix(fth, s, p);
	}

	return Combinator.Bind4(
		_fst, _snd, _trd, _fth,

		s, p
	);
}

static Answer_t Bind5(Answer_t (* fst)(String_t *, Processor_t), Answer_t (* snd)(String_t *, Processor_t), Answer_t (* trd)(String_t *, Processor_t), Answer_t (* fth)(String_t *, Processor_t), Answer_t (* fif)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t _fst(String_t *s, Processor_t p) {
		return _fix(fst, s, p);
	}

	Answer_t _snd(String_t *s, Processor_t p) {
		return _fix(snd, s, p);
	}

	Answer_t _trd(String_t *s, Processor_t p) {
		return _fix(trd, s, p);
	}

	Answer_t _fth(String_t *s, Processor_t p) {
		return _fix(fth, s, p);
	}

	Answer_t _fif(String_t *s, Processor_t p) {
		return _fix(fif, s, p);
	}

	return Combinator.Bind5(
		_fst, _snd, _trd, _fth, _fif,

		s, p
	);
}

static Answer_t Bind6(Answer_t (* fst)(String_t *, Processor_t), Answer_t (* snd)(String_t *, Processor_t), Answer_t (* trd)(String_t *, Processor_t), Answer_t (* fth)(String_t *, Processor_t), Answer_t (* fif)(String_t *, Processor_t), Answer_t (* sth)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t _fst(String_t *s, Processor_t p) {
		return _fix(fst, s, p);
	}

	Answer_t _snd(String_t *s, Processor_t p) {
		return _fix(snd, s, p);
	}

	Answer_t _trd(String_t *s, Processor_t p) {
		return _fix(trd, s, p);
	}

	Answer_t _fth(String_t *s, Processor_t p) {
		return _fix(fth, s, p);
	}

	Answer_t _fif(String_t *s, Processor_t p) {
		return _fix(fif, s, p);
	}

	Answer_t _sth(String_t *s, Processor_t p) {
		return _fix(sth, s, p);
	}

	return Combinator.Bind6(
		_fst, _snd, _trd, _fth, _fif, _sth,

		s, p
	);
}

static Answer_t Bind7(Answer_t (* fst)(String_t *, Processor_t), Answer_t (* snd)(String_t *, Processor_t), Answer_t (* trd)(String_t *, Processor_t), Answer_t (* fth)(String_t *, Processor_t), Answer_t (* fif)(String_t *, Processor_t), Answer_t (* sth)(String_t *, Processor_t), Answer_t (* svn)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t _fst(String_t *s, Processor_t p) {
		return _fix(fst, s, p);
	}

	Answer_t _snd(String_t *s, Processor_t p) {
		return _fix(snd, s, p);
	}

	Answer_t _trd(String_t *s, Processor_t p) {
		return _fix(trd, s, p);
	}

	Answer_t _fth(String_t *s, Processor_t p) {
		return _fix(fth, s, p);
	}

	Answer_t _fif(String_t *s, Processor_t p) {
		return _fix(fif, s, p);
	}

	Answer_t _sth(String_t *s, Processor_t p) {
		return _fix(sth, s, p);
	}

	Answer_t _svn(String_t *s, Processor_t p) {
		return _fix(svn, s, p);
	}

	Answer_t _binds(String_t *s, Processor_t p) {
		return Combinator.Bind6(
			_fst, _snd, _trd, _fth, _fif, _sth,

			s, p
		);
	}

	return Combinator.Bind(_binds, _svn, s, p);
}

static Answer_t Choise(Answer_t (* fst)(String_t *, Processor_t), Answer_t (* snd)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t Choise_body(String_t *s, Processor_t p) {
		return Combinator.Choise(fst, snd, s, p);
	}

	return _fix(Choise_body, s, p);
}

static Answer_t Choise3(Answer_t (* fst)(String_t *, Processor_t), Answer_t (* snd)(String_t *, Processor_t), Answer_t (* trd)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t Choise3_body(String_t *s, Processor_t p) {
		return Combinator.Choise3(fst, snd, trd, s, p);
	}

	return _fix(Choise3_body, s, p);
}

static Answer_t Choise4(Answer_t (* fst)(String_t *, Processor_t), Answer_t (* snd)(String_t *, Processor_t), Answer_t (* trd)(String_t *, Processor_t), Answer_t (* fth)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t Choise4_body(String_t *s, Processor_t p) {
		return Combinator.Choise4(fst, snd, trd, fth, s, p);
	}

	return _fix(Choise4_body, s, p);
}

static Answer_t Choise5(Answer_t (* fst)(String_t *, Processor_t), Answer_t (* snd)(String_t *, Processor_t), Answer_t (* trd)(String_t *, Processor_t), Answer_t (* fth)(String_t *, Processor_t), Answer_t (* fif)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t Choise5_body(String_t *s, Processor_t p) {
		return Combinator.Choise5(fst, snd, trd, fth, fif, s, p);
	}

	return _fix(Choise5_body, s, p);
}

static Answer_t Choise6(Answer_t (* fst)(String_t *, Processor_t), Answer_t (* snd)(String_t *, Processor_t), Answer_t (* trd)(String_t *, Processor_t), Answer_t (* fth)(String_t *, Processor_t), Answer_t (* fif)(String_t *, Processor_t), Answer_t (* sth)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t Choise6_body(String_t *s, Processor_t p) {
		return Combinator.Choise6(fst, snd, trd, fth, fif, sth, s, p);
	}

	return _fix(Choise6_body, s, p);
}

static Answer_t Choise10(
	Answer_t (* p1)(String_t *, Processor_t), Answer_t (* p2)(String_t *, Processor_t),
	Answer_t (* p3)(String_t *, Processor_t), Answer_t (* p4)(String_t *, Processor_t),
	Answer_t (* p5)(String_t *, Processor_t), Answer_t (* p6)(String_t *, Processor_t),
	Answer_t (* p7)(String_t *, Processor_t), Answer_t (* p8)(String_t *, Processor_t),
	Answer_t (* p9)(String_t *, Processor_t), Answer_t (* p10)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t Choise6_body(String_t *s, Processor_t p) {
		return Choise6(p1, p2, p3, p4, p5, p6, s, p);
	}

	Answer_t Choise4_body(String_t *s, Processor_t p) {
		return Choise4(p7, p8, p9, p10, s, p);
	}

	return Choise(
		Choise6_body,
		Choise4_body,

		s, p
	);
}

static Answer_t Many0(Answer_t (* parser)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t Many0_body(String_t *s, Processor_t p) {
		return Combinator.Many0(parser, s, p);
	}

	return _fix(Many0_body, s, p);
}

static Answer_t Many1(Answer_t (* parser)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t Many1_body(String_t *s, Processor_t p) {
		return Combinator.Many1(parser, s, p);
	}

	return _fix(Many1_body, s, p);
}

static Answer_t Parser_VarName(String_t *s, Processor_t p) {
	Answer_t r = Parser_Name(s, p);

	if (r.Reply == Reply.Ok)
		printf(u8" %s{var}", String.GetPrimitive(r.Precipitate));

	return r;
}

static Answer_t Parser_ProcName(String_t *s, Processor_t p) {
	return Parser_Name(s, p);
}

static Answer_t Parser_StdType(String_t *s, Processor_t p) {
	List_t *types = List.New();
	types->Add(types, String.New(u8"integer"));
	types->Add(types, String.New(u8"boolean"));
	types->Add(types, String.New(u8"char"));

	Answer_t r = Parsers.String.OneOf(types, s, p);

	if (r.Reply == Reply.Ok)
		printf(u8" %s", String.GetPrimitive(r.Precipitate));

	return r;
}

static Answer_t Parser_AddOpr(String_t *s, Processor_t p) {
	List_t *adds = List.New();
	adds->Add(adds, String.New(u8"or"));
	adds->Add(adds, String.New(u8"+"));
	adds->Add(adds, String.New(u8"-"));

	return Parsers.String.OneOf(adds, s, p);
}

static Answer_t Parser_MulOpr(String_t *s, Processor_t p) {
	List_t *muls = List.New();
	muls->Add(muls, String.New(u8"and"));
	muls->Add(muls, String.New(u8"div"));
	muls->Add(muls, String.New(u8"*"));

	return Parsers.String.OneOf(muls, s, p);
}

static Answer_t Parser_Const(String_t *s, Processor_t p) {
	Answer_t false_kwd(String_t *s, Processor_t p) {
		return Parsers.String.Match(String.New(u8"false"), s, p);
	}

	Answer_t true_kwd(String_t *s, Processor_t p) {
		return Parsers.String.Match(String.New(u8"true"), s, p);
	}

	return Choise4(
		Parser_UInt,
		false_kwd,
		true_kwd,
		Parser_String,

		s, p
	);
}

static Answer_t Parser_Expr(String_t *s, Processor_t p);
static Answer_t Parser_Var(String_t *s, Processor_t p) {
	Answer_t arrayIndexX(String_t *s, Processor_t p) {
		Answer_t arrayIndex(String_t *s, Processor_t p) {
			Answer_t open(String_t *s, Processor_t p) {
				return Parsers.Char.Match('[', s, p);
			}

			Answer_t close(String_t *s, Processor_t p) {
				return Parsers.Char.Match(']', s, p);
			}

			return Bind3(
				open, Parser_Expr, close,

				s, p
			);
		}

		return Combinator.Possibly(arrayIndex, s, p);
	}

	return Bind(
		Parser_VarName, arrayIndexX,

		s, p
	);
}

static Answer_t Parser_Factor(String_t *s, Processor_t p) {
	Answer_t exprZ(String_t *s, Processor_t p) {
		Answer_t open(String_t *s, Processor_t p) {
			return Parsers.Char.Match('(', s, p);
		}

		Answer_t close(String_t *s, Processor_t p) {
			return Parsers.Char.Match(')', s, p);
		}

		return Bind3(
			open, Parser_Expr, close,

			s, p
		);
	}

	Answer_t invFactor(String_t *s, Processor_t p) {
		Answer_t not(String_t *s, Processor_t p) {
			return Parsers.String.Match(String.New(u8"not"), s, p);
		}

		return Bind(
			not, Parser_Factor,

			s, p
		);
	}

	Answer_t stdTexprZ(String_t *s, Processor_t p) {
		Answer_t open(String_t *s, Processor_t p) {
			return Parsers.Char.Match('(', s, p);
		}

		Answer_t close(String_t *s, Processor_t p) {
			return Parsers.Char.Match(')', s, p);
		}

		return Bind4(
			Parser_StdType, open, Parser_Expr, close,

			s, p
		);
	}

	return Choise5(
		Parser_Var,
		Parser_Const,
		exprZ,
		invFactor,
		stdTexprZ,

		s, p
	);
}

static Answer_t Parser_Term(String_t *s, Processor_t p) {
	Answer_t adtnTerms0(String_t *s, Processor_t p) {
		Answer_t adtnTerm(String_t *s, Processor_t p) {
			return Bind(
				Parser_MulOpr, Parser_Factor,

				s, p
			);
		}

		return Many0(adtnTerm, s, p);
	}

	return Bind(
		Parser_Factor, adtnTerms0,

		s, p
	);
}

static Answer_t Parser_LeftPart(String_t *s, Processor_t p) {
	return Parser_Var(s, p);
}

static Answer_t Parser_SimpleExpr(String_t *s, Processor_t p) {
	Answer_t plus_or_minus(String_t *s, Processor_t p) {
		Answer_t plus(String_t *s, Processor_t p) {
			return Parsers.Char.Match('+', s, p);
		}

		Answer_t minus(String_t *s, Processor_t p) {
			return Parsers.Char.Match('-', s, p);
		}

		return Choise(
			plus,
			minus,

			s, p
		);
	}

	Answer_t plus_or_minusX(String_t *s, Processor_t p) {
		return Combinator.Possibly(plus_or_minus, s, p);
	}

	Answer_t adtnAdds0(String_t *s, Processor_t p) {
		Answer_t adtnAdd(String_t *s, Processor_t p) {
			return Bind(
				Parser_AddOpr, Parser_Term,

				s, p
			);
		}

		return Many0(adtnAdd, s, p);
	} 

	return Bind3(
		plus_or_minusX, Parser_Term, adtnAdds0,

		s, p
	);
}

static Answer_t Parser_RelOpr(String_t *s, Processor_t p) {
	List_t *rels = List.New();
	rels->Add(rels, String.New(u8"<>"));
	rels->Add(rels, String.New(u8"<="));
	rels->Add(rels, String.New(u8">="));
	rels->Add(rels, String.New(u8"="));
	rels->Add(rels, String.New(u8"<"));
	rels->Add(rels, String.New(u8">"));

	return Parsers.String.OneOf(rels, s, p);
}

static Answer_t Parser_Expr(String_t *s, Processor_t p) {
	Answer_t adtnSufExpr0(String_t *s, Processor_t p) {
		Answer_t adtnSufExpr(String_t *s, Processor_t p) {
			return Bind(
				Parser_RelOpr, Parser_SimpleExpr,

				s, p
			);
		}

		return Many0(adtnSufExpr, s, p);
	}

	return Bind(
		Parser_SimpleExpr, adtnSufExpr0,

		s, p
	);
}

static Answer_t Parser_AssignStmt(String_t *s, Processor_t p) {
	Answer_t assign(String_t *s, Processor_t p) {
		return Parsers.String.Match(String.New(u8":="), s, p);
	}

	return Bind3(
		Parser_LeftPart, assign, Parser_Expr,

		s, p
	);
}

static Answer_t Parser_Stmt(String_t *s, Processor_t p);
static Answer_t Parser_CondStmt(String_t *s, Processor_t p) {
	Answer_t if_kwd(String_t *s, Processor_t p) {
		return Parsers.String.Match(String.New(u8"if"), s, p);
	}

	Answer_t then_kwd(String_t *s, Processor_t p) {
		return Parsers.String.Match(String.New(u8"then"), s, p);
	}

	Answer_t elseSecX(String_t *s, Processor_t p) {
		Answer_t elseSec(String_t *s, Processor_t p) {
			Answer_t else_kwd(String_t *s, Processor_t p) {
				return Parsers.String.Match(String.New(u8"else"), s, p);
			}

			return Bind(
				else_kwd, Parser_Stmt,

				s, p
			);
		}

		return Combinator.Possibly(elseSec, s, p);
	}

	return Bind5(
		if_kwd, Parser_Expr, then_kwd, Parser_Stmt, elseSecX,

		s, p
	);
}

static Answer_t Parser_IterStmt(String_t *s, Processor_t p) {
	Answer_t while_kwd(String_t *s, Processor_t p) {
		return Parsers.String.Match(String.New(u8"while"), s, p);
	}

	Answer_t do_kwd(String_t *s, Processor_t p) {
		return Parsers.String.Match(String.New(u8"do"), s, p);
	}

	return Bind4(
		while_kwd, Parser_Expr, do_kwd, Parser_Stmt,

		s, p
	);
}

static Answer_t Parser_ExitStmt(String_t *s, Processor_t p) {
	return Parsers.String.Match(String.New(u8"break"), s, p);
}

static Answer_t Parser_Exprs(String_t *s, Processor_t p) {
	Answer_t adtnExprs0(String_t *s, Processor_t p) {
		Answer_t adtnExpr(String_t *s, Processor_t p) {
			Answer_t comma(String_t *s, Processor_t p) {
				return Parsers.Char.Match(',', s, p);
			}

			return Bind(
				comma, Parser_Expr,
				s, p
			);
		}

		return Many0(adtnExpr, s, p);
	}

	return Bind(
		Parser_Expr, adtnExprs0,

		s, p
	);
}

static Answer_t Parser_CallStmt(String_t *s, Processor_t p) {
	Answer_t call(String_t *s, Processor_t p) {
		return Parsers.String.Match(String.New(u8"if"), s, p);
	}

	Answer_t paramX(String_t *s, Processor_t p) {
		Answer_t param(String_t *s, Processor_t p) {
			Answer_t open(String_t *s, Processor_t p) {
				return Parsers.Char.Match('(', s, p);
			}

			Answer_t close(String_t *s, Processor_t p) {
				return Parsers.Char.Match(')', s, p);
			}

			return Bind3(
				open, Parser_Exprs, close,

				s, p
			);
		}

		return Combinator.Possibly(param, s, p);
	}

	return Bind3(
		call, Parser_ProcName, paramX,

		s, p
	);
}

static Answer_t Parser_RetStmt(String_t *s, Processor_t p) {
	return Parsers.String.Match(String.New(u8"return"), s, p);
}

static Answer_t Parser_InputStmt(String_t *s, Processor_t p) {
	Answer_t embeddedInst(String_t *s, Processor_t p) {
		List_t *insts = List.New();
		insts->Add(insts, String.New(u8"readln"));
		insts->Add(insts, String.New(u8"read"));

		return Parsers.String.OneOf(insts, s, p);
	}

	Answer_t paramX(String_t *s, Processor_t p) {
		Answer_t param(String_t *s, Processor_t p) {
			Answer_t open(String_t *s, Processor_t p) {
				return Parsers.Char.Match('(', s, p);
			}

			Answer_t adtnVars0(String_t *s, Processor_t p) {
				Answer_t adtnVar(String_t *s, Processor_t p) {
					Answer_t comma(String_t *s, Processor_t p) {
						return Parsers.Char.Match(',', s, p);
					}

					return Bind(
						comma, Parser_Var,

						s, p
					);
				}

				return Many0(adtnVar, s, p);
			}

			Answer_t close(String_t *s, Processor_t p) {
				return Parsers.Char.Match(')', s, p);
			}

			return Bind4(
				open, Parser_Var, adtnVars0, close,

				s, p
			);
		}

		return Combinator.Possibly(param, s, p);
	}

	return Bind(
		embeddedInst, paramX,

		s, p
	);
}

static Answer_t Parser_OutputStmt(String_t *s, Processor_t p) {
	Answer_t number(String_t *s, Processor_t p) {
		Answer_t optX(String_t *s, Processor_t p) {
			Answer_t opt(String_t *s, Processor_t p) {
				Answer_t colon(String_t *s, Processor_t p) {
					return Parsers.Char.Match(':', s, p);
				}

				return Bind(
					colon, Parser_UInt,

					s, p
				);
			}

			return Combinator.Possibly(opt, s, p);
		}

		return Bind(
			Parser_Expr, optX,

			s, p
		);
	}

	return Choise(
		number,
		Parser_String,

		s, p
	);
}

static Answer_t Parser_OutputFmt(String_t *s, Processor_t p) {
	Answer_t embeddedInst(String_t *s, Processor_t p) {
		List_t *insts = List.New();
		insts->Add(insts, String.New(u8"writeln"));
		insts->Add(insts, String.New(u8"write"));

		return Parsers.String.OneOf(insts, s, p);
	}

	Answer_t paramX(String_t *s, Processor_t p) {
		Answer_t param(String_t *s, Processor_t p) {
			Answer_t open(String_t *s, Processor_t p) {
				return Parsers.Char.Match('(', s, p);
			}

			Answer_t adtnOutputFmts0(String_t *s, Processor_t p) {
				Answer_t adtnOutputFmt(String_t *s, Processor_t p) {
					Answer_t comma(String_t *s, Processor_t p) {
						return Parsers.Char.Match(',', s, p);
					}

					return Bind(
						comma, Parser_OutputFmt,

						s, p
					);
				}

				return Many0(adtnOutputFmt, s, p);
			}

			Answer_t close(String_t *s, Processor_t p) {
				return Parsers.Char.Match(')', s, p);
			}

			return Bind4(
				open, Parser_OutputFmt, adtnOutputFmts0, close,

				s, p
			);
		}

		return Combinator.Possibly(param, s, p);
	}

	return Bind(
		embeddedInst, paramX,

		s, p
	);
}

static Answer_t Parser_Stmt(String_t *s, Processor_t p);
static Answer_t Parser_CompoundStmt(String_t *s, Processor_t p) {
	Answer_t begin(String_t *s, Processor_t p) {
		return Parsers.String.Match(String.New(u8"begin"), s, p);
	}

	Answer_t adtnStmts(String_t *s, Processor_t p) {
		Answer_t semicolon(String_t *s, Processor_t p) {
			return Parsers.Char.Match(';', s, p);
		}

		Answer_t adtnStmt(String_t *s, Processor_t p) {
			return Bind(
				semicolon, Parser_Stmt,

				s, p
			);
		}

		return Many0(adtnStmt, s, p);
	}

	Answer_t end(String_t *s, Processor_t p) {
		return Parsers.String.Match(String.New(u8"end"), s, p);
	}

	return Bind4(
		begin, Parser_Stmt, adtnStmts, end,
		
		s, p
	);
}

static Answer_t Parser_EmptyStmt(String_t *s, Processor_t p) {
	return Basis.Ok(s, p);
}

static Answer_t Parser_Stmt(String_t *s, Processor_t p) {
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

		s, p
	);
}

static Answer_t Parser_VarNames(String_t *s, Processor_t p) {
	Answer_t adtnVarNames(String_t *s, Processor_t p) {
		Answer_t comma(String_t *s, Processor_t p) {
			Answer_t r = Parsers.Char.Match(',', s, p);

			if (r.Reply == Reply.Ok)
				printf(u8",");

			return r;
		}

		return Bind(
			comma, Parser_VarName,

			s, p
		);
	}

	return Bind(Parser_VarName, adtnVarNames, s, p);
}

static Answer_t Parser_ArrType(String_t *s, Processor_t p) {
	Answer_t array(String_t *s, Processor_t p) {
		return Parsers.String.Match(String.New(u8"array"), s, p);
	}

	Answer_t open(String_t *s, Processor_t p) {
		return Parsers.Char.Match('[', s, p);
	}

	Answer_t close(String_t *s, Processor_t p) {
		return Parsers.Char.Match(']', s, p);
	}

	Answer_t of(String_t *s, Processor_t p) {
		return Parsers.String.Match(String.New(u8"of"), s, p);
	}

	return Bind6(
		array, open, Parser_UInt, close, of, Parser_StdType,

		s, p
	);
}

static Answer_t Parser_Type(String_t *s, Processor_t p) {
	return Combinator.Choise(
		Parser_StdType,
		Parser_ArrType,

		s, p
	);
}

static Answer_t Parser_VarDecl(String_t *s, Processor_t p) {
	Answer_t var(String_t *s, Processor_t p) {
		Answer_t r = Parsers.String.Match(String.New(u8"var"), s, p);

		if (r.Reply == Reply.Ok)
			printf(u8"\tvar");

		return r;
	}

	Answer_t VarDecl(String_t *s, Processor_t p) {
		Answer_t colon(String_t *s, Processor_t p) {
			Answer_t r = Parsers.Char.Match(':', s, p);

			if (r.Reply == Reply.Ok)
				printf(u8" :");

			return r;
		}

		Answer_t semicolon(String_t *s, Processor_t p) {
			Answer_t r = Parsers.Char.Match(';', s, p);

			if (r.Reply == Reply.Ok)
				printf(u8";\n");

			return r;
		}

		return Bind4(
			Parser_VarNames, colon, Parser_Type, semicolon,

			s, p
		);
	}

	Answer_t VarDecls(String_t *s, Processor_t p) {
		return Many0(VarDecl, s, p);
	}

	return Bind3(
		var, VarDecl,
		VarDecls,

		s, p
	);
}

static Answer_t Parser_FormalParam(String_t *s, Processor_t p) {
	Answer_t open(String_t *s, Processor_t p) {
		return Parsers.Char.Match('(', s, p);
	}

	Answer_t colon(String_t *s, Processor_t p) {
		return Parsers.Char.Match(':', s, p);
	}

	Answer_t adtnParams(String_t *s, Processor_t p) {
		Answer_t semicolon(String_t *s, Processor_t p) {
			return Parsers.Char.Match(';', s, p);
		}

		Answer_t adtnParam(String_t *s, Processor_t p) {
			return Bind4(
				semicolon, Parser_VarNames, colon, Parser_Type,

				s, p
			);
		}

		return Many0(adtnParam, s, p);
	}

	Answer_t close(String_t *s, Processor_t p) {
		return Parsers.Char.Match(')', s, p);
	}

	return Bind6(
		open, Parser_VarNames, colon, Parser_Type,
		adtnParams, close,

		s, p
	);
}

static Answer_t Parser_SubProgDecl(String_t *s, Processor_t p) {
	Answer_t procedure(String_t *s, Processor_t p) {
		return Parsers.String.Match(String.New(u8"procedure"), s, p);
	}

	Answer_t Parser_FormalParamX(String_t *s, Processor_t p) {
		return Combinator.Possibly(Parser_FormalParam, s, p);
	}

	Answer_t semicolon(String_t *s, Processor_t p) {
		return Parsers.Char.Match(';', s, p);
	}

	Answer_t Parser_VarDeclX(String_t *s, Processor_t p) {
		return Combinator.Possibly(Parser_VarDecl, s, p);
	}

	return Bind7(
		procedure, Parser_ProcName, Parser_FormalParamX, semicolon,
			Parser_VarDeclX,
			Parser_CompoundStmt,
		semicolon,

		s, p
	);
}

static Answer_t Parser_Block(String_t *s, Processor_t p) {
	Answer_t VarDecl_or_SubProgDecl(String_t *s, Processor_t p) {
		return Choise(
			Parser_VarDecl,
			Parser_SubProgDecl,

			s, p
		);
	}

	Answer_t Repeat_VarDecl_or_SubProgDecl(String_t *s, Processor_t p) {
		return Many0(VarDecl_or_SubProgDecl, s, p);
	}

	return Bind(
		Repeat_VarDecl_or_SubProgDecl,
		Parser_CompoundStmt,

		s, p
	);
}

static Answer_t Parser_Program(String_t *s, Processor_t p) {
	Answer_t program(String_t *s, Processor_t p) {
		Answer_t r = Parsers.String.Match(String.New(u8"program"), s, p);

		if (r.Reply == Reply.Ok)
			printf(u8"program");

		return r;
	}

	Answer_t name(String_t *s, Processor_t p) {
		Answer_t r = Many1(Parser_Name, s, p);

		if (r.Reply == Reply.Ok)
			printf(u8" %s", String.GetPrimitive(r.Precipitate));

		return r;
	}

	Answer_t semicolon(String_t *s, Processor_t p) {
		Answer_t r = Parsers.Char.Match(';', s, p);

		if (r.Reply == Reply.Ok)
			printf(u8";\n");

		return r;
	}

	Answer_t end(String_t *s, Processor_t p) {
		Answer_t r = Parsers.String.Match(String.New(u8"end"), s, p);

		if (r.Reply == Reply.Ok)
			printf(u8"end");

		return r;
	}

	Answer_t dot(String_t *s, Processor_t p) {
		Answer_t r = Parsers.Char.Match('.', s, p);
	
		if (r.Reply == Reply.Ok)
			printf(u8".");

		return r;
	}

	return Bind7(
		program, name, semicolon,
		Parser_Block,
		end, dot, _Separators0,

		s, p
	);
}

static ParseResult_t Execute(String_t *s) {
	lineNum = 1;

	Answer_t result = Invoker.Parse(Parser_Program, s);

	return (ParseResult_t){
		.Succeeded		= result.Reply == Reply.Ok,
		.Precipitate	= result.Precipitate,
		.Subsequent		= result.Subsequent,

		.ErrorLine		= lineNum,
		.ErrorMessage	= String.New("error_msg")
	};
}

_MPLParser MPLParser = {
	.Execute = Execute,
};
