#include "MPLParser.h"

static SeqAnswer_t SeqParser_VarName(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t r = SeqParsers.Complete(MPLLexer.Parser_Name, seq, NULL);

	/****************************************/
	if (r.Reply == Reply.Ok)
		printf(u8" %s", String.GetPrimitive(
			(seq->GetStringiser(seq))(Seq.GetLast(seq))
		));
	/****************************************/

	return r;
}

static SeqAnswer_t SeqParser_ProcName(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t r = SeqParsers.Complete(MPLLexer.Parser_Name, seq, NULL);

	/****************************************/
	if (r.Reply == Reply.Ok)
		printf(u8" %s", String.GetPrimitive(
			(seq->GetStringiser(seq))(Seq.GetLast(seq))
		));
	/****************************************/

	return r;
}

static SeqAnswer_t SeqParser_StdType(Seq_t *seq, Processor_t *p) {
	Seq_t *types = Seq.New(Seq.STRINGISER_STRING);
	types->Add(types, String.New(u8"integer"));
	types->Add(types, String.New(u8"boolean"));
	types->Add(types, String.New(u8"char"));

	SeqAnswer_t r = SeqParsers.OneOf(types, seq, p);

	/****************************************/
	if (r.Reply == Reply.Ok)
		printf(u8" %s", String.GetPrimitive(
			(seq->GetStringiser(seq))(Seq.GetLast(seq))
		));
	/****************************************/

	return r;
}

static SeqAnswer_t SeqParser_AddOpr(Seq_t *seq, Processor_t *p) {
	Seq_t *adds = Seq.New(Seq.STRINGISER_STRING);

	adds->Add(adds, String.New(u8"or"));
	adds->Add(adds, String.New(u8"+"));
	adds->Add(adds, String.New(u8"-"));

	return SeqParsers.OneOf(adds, seq, p);
}

static SeqAnswer_t SeqParser_MulOpr(Seq_t *seq, Processor_t *p) {
	Seq_t *muls = Seq.New(Seq.STRINGISER_STRING);

	muls->Add(muls, String.New(u8"and"));
	muls->Add(muls, String.New(u8"div"));
	muls->Add(muls, String.New(u8"*"));

	return SeqParsers.OneOf(muls, seq, p);
}

static SeqAnswer_t SeqParser_Const(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t uint_lit(Seq_t *seq, Processor_t *p) {
		return SeqParsers.Complete(MPLLexer.Parser_UInt, seq, NULL);
	} 

	SeqAnswer_t false_kwd(Seq_t *seq, Processor_t *p) {
		return SeqParsers.Match(String.New(u8"false"), seq, p);
	}

	SeqAnswer_t true_kwd(Seq_t *seq, Processor_t *p) {
		return SeqParsers.Match(String.New(u8"true"), seq, p);
	}

	SeqAnswer_t str_lit(Seq_t *seq, Processor_t *p) {
		return SeqParsers.Complete(MPLLexer.Parser_String, seq, NULL);
	}

	return SeqCombinator.Choise4(
		uint_lit,
		false_kwd,
		true_kwd,
		str_lit,

		seq, p
	);
}

static SeqAnswer_t SeqParser_Expr(Seq_t *seq, Processor_t *p);
static SeqAnswer_t SeqParser_Var(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t arrayIndexX(Seq_t *seq, Processor_t *p) {
		SeqAnswer_t arrayIndex(Seq_t *seq, Processor_t *p) {
			SeqAnswer_t open(Seq_t *seq, Processor_t *p) {
				return SeqParsers.Match(String.New(u8"["), seq, p);
			}

			SeqAnswer_t close(Seq_t *seq, Processor_t *p) {
				return SeqParsers.Match(String.New(u8"["), seq, p);
			}

			return SeqCombinator.Bind3(
				open, SeqParser_Expr, close,
				seq, p
			);
		}

		return SeqCombinator.Possibly(arrayIndex, seq, p);
	}

	return SeqCombinator.Bind(
		SeqParser_VarName, arrayIndexX,
		seq, p
	);
}

static SeqAnswer_t SeqParser_Factor(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t exprZ(Seq_t *seq, Processor_t *p) {
		SeqAnswer_t open(Seq_t *seq, Processor_t *p) {
			return SeqParsers.Match(String.New(u8"("), seq, p);
		}

		SeqAnswer_t close(Seq_t *seq, Processor_t *p) {
			return SeqParsers.Match(String.New(u8")"), seq, p);
		}

		return SeqCombinator.Bind3(
			open, SeqParser_Expr, close,
			seq, p
		);
	}

	SeqAnswer_t invFactor(Seq_t *seq, Processor_t *p) {
		SeqAnswer_t not(Seq_t *seq, Processor_t *p) {
			return SeqParsers.Match(String.New(u8"not"), seq, p);
		}

		return SeqCombinator.Bind(
			not, SeqParser_Factor,
			seq, p
		);
	}

	SeqAnswer_t stdTexprZ(Seq_t *seq, Processor_t *p) {
		SeqAnswer_t open(Seq_t *seq, Processor_t *p) {
			return SeqParsers.Match(String.New(u8"("), seq, p);
		}

		SeqAnswer_t close(Seq_t *seq, Processor_t *p) {
			return SeqParsers.Match(String.New(u8")"), seq, p);
		}

		return SeqCombinator.Bind4(
			SeqParser_StdType, open, SeqParser_Expr, close,
			seq, p
		);
	}

	return SeqCombinator.Choise5(
		SeqParser_Var,
		SeqParser_Const,
		exprZ,
		invFactor,
		stdTexprZ,

		seq, p
	);
}

static SeqAnswer_t SeqParser_Term(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t adtnTerms0(Seq_t *seq, Processor_t *p) {
		SeqAnswer_t adtnTerm(Seq_t *seq, Processor_t *p) {
			return SeqCombinator.Bind(
				SeqParser_MulOpr, SeqParser_Factor,
				seq, p
			);
		}

		return SeqCombinator.Many0(adtnTerm, seq, p);
	}

	return SeqCombinator.Bind(
		SeqParser_Factor, adtnTerms0,
		seq, p
	);
}

static SeqAnswer_t SeqParser_LeftPart(Seq_t *seq, Processor_t *p) {
	return SeqParser_Var(seq, p);
}

static SeqAnswer_t SeqParser_SimpleExpr(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t plus_or_minus(Seq_t *seq, Processor_t *p) {
		SeqAnswer_t plus(Seq_t *seq, Processor_t *p) {
			return SeqParsers.Match(String.New(u8"+"), seq, p);
		}

		SeqAnswer_t minus(Seq_t *seq, Processor_t *p) {
			return SeqParsers.Match(String.New(u8"-"), seq, p);
		}

		return SeqCombinator.Choise(
			plus,
			minus,

			seq, p
		);
	}

	SeqAnswer_t plus_or_minusX(Seq_t *seq, Processor_t *p) {
		return SeqCombinator.Possibly(plus_or_minus, seq, p);
	}

	SeqAnswer_t adtnAdds0(Seq_t *seq, Processor_t *p) {
		SeqAnswer_t adtnAdd(Seq_t *seq, Processor_t *p) {
			return SeqCombinator.Bind(
				SeqParser_AddOpr, SeqParser_Term,
				seq, p
			);
		}

		return SeqCombinator.Many0(adtnAdd, seq, p);
	} 

	return SeqCombinator.Bind3(
		plus_or_minusX, SeqParser_Term, adtnAdds0,
		seq, p
	);
}

static SeqAnswer_t SeqParser_RelOpr(Seq_t *seq, Processor_t *p) {
	Seq_t *rels = Seq.New(Seq.STRINGISER_STRING);

	rels->Add(rels, String.New(u8"<>"));
	rels->Add(rels, String.New(u8"<="));
	rels->Add(rels, String.New(u8">="));
	rels->Add(rels, String.New(u8"="));
	rels->Add(rels, String.New(u8"<"));
	rels->Add(rels, String.New(u8">"));

	return SeqParsers.OneOf(rels, seq, p);
}

static SeqAnswer_t SeqParser_Expr(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t adtnSufExpr0(Seq_t *seq, Processor_t *p) {
		SeqAnswer_t adtnSufExpr(Seq_t *seq, Processor_t *p) {
			return SeqCombinator.Bind(
				SeqParser_RelOpr, SeqParser_SimpleExpr,
				seq, p
			);
		}

		return SeqCombinator.Many0(adtnSufExpr, seq, p);
	}

	return SeqCombinator.Bind(
		SeqParser_SimpleExpr, adtnSufExpr0,
		seq, p
	);
}

static SeqAnswer_t SeqParser_AssignStmt(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t assign(Seq_t *seq, Processor_t *p) {
		return SeqParsers.Match(String.New(u8":="), seq, p);
	}

	return SeqCombinator.Bind3(
		SeqParser_LeftPart, assign, SeqParser_Expr,
		seq, p
	);
}

static SeqAnswer_t SeqParser_Stmt(Seq_t *seq, Processor_t *p);
static SeqAnswer_t SeqParser_CondStmt(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t if_kwd(Seq_t *seq, Processor_t *p) {
		return SeqParsers.Match(String.New(u8"if"), seq, p);
	}

	SeqAnswer_t then_kwd(Seq_t *seq, Processor_t *p) {
		return SeqParsers.Match(String.New(u8"then"), seq, p);
	}

	SeqAnswer_t elseSecX(Seq_t *seq, Processor_t *p) {
		SeqAnswer_t elseSec(Seq_t *seq, Processor_t *p) {
			SeqAnswer_t else_kwd(Seq_t *seq, Processor_t *p) {
				return SeqParsers.Match(String.New(u8"else"), seq, p);
			}

			return SeqCombinator.Bind(
				else_kwd, SeqParser_Stmt,
				seq, p
			);
		}

		return SeqCombinator.Possibly(elseSec, seq, p);
	}

	return SeqCombinator.Bind5(
		if_kwd, SeqParser_Expr, then_kwd, SeqParser_Stmt, elseSecX,
		seq, p
	);
}

static SeqAnswer_t SeqParser_IterStmt(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t while_kwd(Seq_t *seq, Processor_t *p) {
		return SeqParsers.Match(String.New(u8"while"), seq, p);
	}

	SeqAnswer_t do_kwd(Seq_t *seq, Processor_t *p) {
		return SeqParsers.Match(String.New(u8"dp"), seq, p);
	}

	return SeqCombinator.Bind4(
		while_kwd, SeqParser_Expr, do_kwd, SeqParser_Stmt,
		seq, p
	);
}

static SeqAnswer_t SeqParser_ExitStmt(Seq_t *seq, Processor_t *p) {
	return SeqParsers.Match(String.New(u8"break"), seq, p);
}

static SeqAnswer_t SeqParser_Exprs(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t adtnExprs0(Seq_t *seq, Processor_t *p) {
		SeqAnswer_t adtnExpr(Seq_t *seq, Processor_t *p) {
			SeqAnswer_t comma(Seq_t *seq, Processor_t *p) {
				return SeqParsers.Match(String.New(u8","), seq, p);
			}

			return SeqCombinator.Bind(
				comma, SeqParser_Expr,
				seq, p
			);
		}

		return SeqCombinator.Many0(adtnExpr, seq, p);
	}

	return SeqCombinator.Bind(
		SeqParser_Expr, adtnExprs0,
		seq, p
	);
}

static SeqAnswer_t SeqParser_CallStmt(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t call(Seq_t *seq, Processor_t *p) {
		return SeqParsers.Match(String.New(u8"call"), seq, p);
	}

	SeqAnswer_t paramX(Seq_t *seq, Processor_t *p) {
		SeqAnswer_t param(Seq_t *seq, Processor_t *p) {
			SeqAnswer_t open(Seq_t *seq, Processor_t *p) {
				return SeqParsers.Match(String.New(u8"("), seq, p);
			}

			SeqAnswer_t close(Seq_t *seq, Processor_t *p) {
				return SeqParsers.Match(String.New(u8")"), seq, p);
			}

			return SeqCombinator.Bind3(
				open, SeqParser_Exprs, close,
				seq, p
			);
		}

		return SeqCombinator.Possibly(param, seq, p);
	}

	return SeqCombinator.Bind3(
		call, SeqParser_ProcName, paramX,
		seq, p
	);
}

static SeqAnswer_t SeqParser_RetStmt(Seq_t *seq, Processor_t *p) {
	return SeqParsers.Match(String.New(u8"return"), seq, p);
}

static SeqAnswer_t SeqParser_InputStmt(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t embeddedInst(Seq_t *seq, Processor_t *p) {
		Seq_t *insts = Seq.New(Seq.STRINGISER_STRING);

		insts->Add(insts, String.New(u8"readln"));
		insts->Add(insts, String.New(u8"read"));

		return SeqParsers.OneOf(insts, seq, p);
	}

	SeqAnswer_t paramX(Seq_t *seq, Processor_t *p) {
		SeqAnswer_t param(Seq_t *seq, Processor_t *p) {
			SeqAnswer_t open(Seq_t *seq, Processor_t *p) {
				return SeqParsers.Match(String.New(u8"("), seq, p);
			}

			SeqAnswer_t adtnVars0(Seq_t *seq, Processor_t *p) {
				SeqAnswer_t adtnVar(Seq_t *seq, Processor_t *p) {
					SeqAnswer_t comma(Seq_t *seq, Processor_t *p) {
						return SeqParsers.Match(String.New(u8","), seq, p);
					}

					return SeqCombinator.Bind(
						comma, SeqParser_Var,
						seq, p
					);
				}

				return SeqCombinator.Many0(adtnVar, seq, p);
			}

			SeqAnswer_t close(Seq_t *seq, Processor_t *p) {
				return SeqParsers.Match(String.New(u8")"), seq, p);
			}

			return SeqCombinator.Bind4(
				open, SeqParser_Var, adtnVars0, close,
				seq, p
			);
		}

		return SeqCombinator.Possibly(param, seq, p);
	}

	return SeqCombinator.Bind(
		embeddedInst, paramX,
		seq, p
	);
}

static SeqAnswer_t SeqParser_OutputStmt(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t number(Seq_t *seq, Processor_t *p) {
		SeqAnswer_t optX(Seq_t *seq, Processor_t *p) {
			SeqAnswer_t opt(Seq_t *seq, Processor_t *p) {
				SeqAnswer_t colon(Seq_t *seq, Processor_t *p) {
					return SeqParsers.Match(String.New(u8":"), seq, p);
				}

				SeqAnswer_t uint_lit(Seq_t *seq, Processor_t *p) {
					return SeqParsers.Complete(MPLLexer.Parser_UInt, seq, p);
				}

				return SeqCombinator.Bind(
					colon, uint_lit,
					seq, p
				);
			}

			return SeqCombinator.Possibly(opt, seq, p);
		}

		return SeqCombinator.Bind(
			SeqParser_Expr, optX,
			seq, p
		);
	}

	SeqAnswer_t str_lit(Seq_t *seq, Processor_t *p) {
		return SeqParsers.Complete(MPLLexer.Parser_String, seq, p);
	}

	return SeqCombinator.Choise(
		number,
		str_lit,

		seq, p
	);
}

static SeqAnswer_t SeqParser_OutputFmt(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t embeddedInst(Seq_t *seq, Processor_t *p) {
		Seq_t *insts = Seq.New(Seq.STRINGISER_STRING);

		insts->Add(insts, String.New(u8"writeln"));
		insts->Add(insts, String.New(u8"write"));

		return SeqParsers.OneOf(insts, seq, p);
	}

	SeqAnswer_t paramX(Seq_t *seq, Processor_t *p) {
		SeqAnswer_t param(Seq_t *seq, Processor_t *p) {
			SeqAnswer_t open(Seq_t *seq, Processor_t *p) {
				return SeqParsers.Match(String.New(u8"("), seq, p);
			}

			SeqAnswer_t adtnOutputFmts0(Seq_t *seq, Processor_t *p) {
				SeqAnswer_t adtnOutputFmt(Seq_t *seq, Processor_t *p) {
					SeqAnswer_t comma(Seq_t *seq, Processor_t *p) {
						return SeqParsers.Match(String.New(u8","), seq, p);
					}

					return SeqCombinator.Bind(
						comma, SeqParser_OutputFmt,
						seq, p
					);
				}

				return SeqCombinator.Many0(adtnOutputFmt, seq, p);
			}

			SeqAnswer_t close(Seq_t *seq, Processor_t *p) {
				return SeqParsers.Match(String.New(u8")"), seq, p);
			}

			return SeqCombinator.Bind4(
				open, SeqParser_OutputFmt, adtnOutputFmts0, close,
				seq, p
			);
		}

		return SeqCombinator.Possibly(param, seq, p);
	}

	return SeqCombinator.Bind(
		embeddedInst, paramX,
		seq, p
	);
}

static SeqAnswer_t SeqParser_Stmt(Seq_t *seq, Processor_t *p);
static SeqAnswer_t SeqParser_CompoundStmt(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t begin(Seq_t *seq, Processor_t *p) {
		return SeqParsers.Match(String.New(u8"begin"), seq, p);
	}

	SeqAnswer_t adtnStmts(Seq_t *seq, Processor_t *p) {
		SeqAnswer_t semicolon(Seq_t *seq, Processor_t *p) {
			return SeqParsers.Match(String.New(u8";"), seq, p);
		}

		SeqAnswer_t adtnStmt(Seq_t *seq, Processor_t *p) {
			return SeqCombinator.Bind(
				semicolon, SeqParser_Stmt,
				seq, p
			);
		}

		return SeqCombinator.Many0(adtnStmt, seq, p);
	}

	SeqAnswer_t end(Seq_t *seq, Processor_t *p) {
		SeqAnswer_t r = SeqParsers.Match(String.New(u8"end"), seq, p);

		/****************************************/
		if (r.Reply == Reply.Ok)
			printf(u8"end");
		/****************************************/

		return r;
	}

	return SeqCombinator.Bind4(
		begin, SeqParser_Stmt, adtnStmts, end,
		seq, p
	);
}

/*static SeqAnswer_t SeqParser_EmptyStmt(Seq_t *seq, Processor_t *p) {
	return SeqBasis.Ok(seq, p);
}*/

static SeqAnswer_t SeqParser_Stmt(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t part1(Seq_t *seq, Processor_t *p) {
		return SeqCombinator.Choise6(
			SeqParser_AssignStmt,
			SeqParser_CondStmt,
			SeqParser_IterStmt,
			SeqParser_ExitStmt,
			SeqParser_CallStmt,
			SeqParser_RetStmt,

			seq, p
		);
	}

	return SeqCombinator.Choise4(
		part1,
		SeqParser_InputStmt,
		SeqParser_OutputStmt,
		SeqParser_CompoundStmt,
//		SeqParser_EmptyStmt,

		seq, p
	);
}

static SeqAnswer_t SeqParser_VarNames(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t adtnVarNames(Seq_t *seq, Processor_t *p) {
		SeqAnswer_t comma(Seq_t *seq, Processor_t *p) {
			SeqAnswer_t r = SeqParsers.Match(String.New(u8","), seq, p);

			/****************************************/
			if (r.Reply == Reply.Ok)
				printf(u8",");
			/****************************************/

			return r;
		}

		return SeqCombinator.Bind(
			comma, SeqParser_VarName,
			seq, p
		);
	}

	return SeqCombinator.Bind(
		SeqParser_VarName, adtnVarNames,
		seq, p
	);
}

static SeqAnswer_t SeqParser_ArrType(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t array(Seq_t *seq, Processor_t *p) {
		return SeqParsers.Match(String.New(u8"array"), seq, p);
	}

	SeqAnswer_t open(Seq_t *seq, Processor_t *p) {
		return SeqParsers.Match(String.New(u8"["), seq, p);
	}

	SeqAnswer_t uint_lit(Seq_t *seq, Processor_t *p) {
		return SeqParsers.Complete(MPLLexer.Parser_UInt, seq, p);
	}

	SeqAnswer_t close(Seq_t *seq, Processor_t *p) {
		return SeqParsers.Match(String.New(u8"]"), seq, p);
	}

	SeqAnswer_t of(Seq_t *seq, Processor_t *p) {
		return SeqParsers.Match(String.New(u8"of"), seq, p);
	}

	return SeqCombinator.Bind6(
		array, open, uint_lit, close, of, SeqParser_StdType,
		seq, p
	);
}

static SeqAnswer_t SeqParser_Type(Seq_t *seq, Processor_t *p) {
	return SeqCombinator.Choise(
		SeqParser_StdType,
		SeqParser_ArrType,

		seq, p
	);
}

static SeqAnswer_t SeqParser_VarDecl(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t var(Seq_t *seq, Processor_t *p) {
		SeqAnswer_t r = SeqParsers.Match(String.New(u8"var"), seq, p);

		/****************************************/
		if (r.Reply == Reply.Ok)
			printf(u8"\tvar");
		/****************************************/

		return r;
	}

	SeqAnswer_t VarDecl(Seq_t *seq, Processor_t *p) {
		SeqAnswer_t colon(Seq_t *seq, Processor_t *p) {
			SeqAnswer_t r = SeqParsers.Match(String.New(u8":"), seq, p);

			/****************************************/
			if (r.Reply == Reply.Ok)
				printf(u8" :");
			/****************************************/

			return r;
		}

		SeqAnswer_t semicolon(Seq_t *seq, Processor_t *p) {
			SeqAnswer_t r = SeqParsers.Match(String.New(u8";"), seq, p);

			/****************************************/
			if (r.Reply == Reply.Ok)
				printf(u8";\n");
			/****************************************/

			return r;
		}

		return SeqCombinator.Bind4(
			SeqParser_VarNames, colon, SeqParser_Type, semicolon,
			seq, p
		);
	}

	SeqAnswer_t VarDecls(Seq_t *seq, Processor_t *p) {
		return SeqCombinator.Many0(VarDecl, seq, p);
	}

	return SeqCombinator.Bind3(
		var, VarDecl, VarDecls,
		seq, p
	);
}

static SeqAnswer_t SeqParser_FormalParam(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t open(Seq_t *seq, Processor_t *p) {
		return SeqParsers.Match(String.New(u8"("), seq, p);
	}

	SeqAnswer_t colon(Seq_t *seq, Processor_t *p) {
		return SeqParsers.Match(String.New(u8":"), seq, p);
	}

	SeqAnswer_t adtnParams(Seq_t *seq, Processor_t *p) {
		SeqAnswer_t semicolon(Seq_t *seq, Processor_t *p) {
			return SeqParsers.Match(String.New(u8";"), seq, p);
		}

		SeqAnswer_t adtnParam(Seq_t *seq, Processor_t *p) {
			return SeqCombinator.Bind4(
				semicolon, SeqParser_VarNames, colon, SeqParser_Type,
				seq, p
			);
		}

		return SeqCombinator.Many0(adtnParam, seq, p);
	}

	SeqAnswer_t close(Seq_t *seq, Processor_t *p) {
		return SeqParsers.Match(String.New(u8")"), seq, p);
	}

	return SeqCombinator.Bind6(
		open, SeqParser_VarNames, colon, SeqParser_Type,
		adtnParams, close,

		seq, p
	);
}

static SeqAnswer_t SeqParser_SubProgDecl(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t procedure(Seq_t *seq, Processor_t *p) {
		return SeqParsers.Match(String.New(u8"procedure"), seq, p);
	}

	SeqAnswer_t SeqParser_FormalParamX(Seq_t *seq, Processor_t *p) {
		return SeqCombinator.Possibly(SeqParser_FormalParam, seq, p);
	}

	SeqAnswer_t semicolon(Seq_t *seq, Processor_t *p) {
		return SeqParsers.Match(String.New(u8";"), seq, p);
	}

	SeqAnswer_t SeqParser_VarDeclX(Seq_t *seq, Processor_t *p) {
		return SeqCombinator.Possibly(SeqParser_VarDecl, seq, p);
	}

	SeqAnswer_t decl(Seq_t *seq, Processor_t *p) {
		return SeqCombinator.Bind4(
			procedure, SeqParser_ProcName, SeqParser_FormalParamX, semicolon,
			seq, p
		);
	}

	return SeqCombinator.Bind4(
		decl,
			SeqParser_VarDeclX,
			SeqParser_CompoundStmt,
		semicolon,
		seq, p
	);
}

static SeqAnswer_t SeqParser_Block(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t VarDecl_or_SubProgDecl(Seq_t *seq, Processor_t *p) {
		return SeqCombinator.Choise(
			SeqParser_VarDecl,
			SeqParser_SubProgDecl,
			seq, p
		);
	}

	SeqAnswer_t VarDecl_or_SubProgDecl_0(Seq_t *seq, Processor_t *p) {
		return SeqCombinator.Many0(VarDecl_or_SubProgDecl, seq, p);
	}

	return SeqCombinator.Bind(
		VarDecl_or_SubProgDecl_0,
		SeqParser_CompoundStmt,
		seq, p
	);
}

static SeqAnswer_t SeqParser_Program(Seq_t *seq, Processor_t *p) {
	SeqAnswer_t program(Seq_t *seq, Processor_t *p) {
		SeqAnswer_t r = SeqParsers.Match(String.New(u8"program"), seq, p);

		/****************************************/
		if (r.Reply == Reply.Ok)
			printf(u8"program");
		/****************************************/

		return r;
	}

	SeqAnswer_t name(Seq_t *seq, Processor_t *p) {
		Answer_t name_p(String_t *s, Processor_t *p) {
			return Combinator.Many1(MPLLexer.Parser_Name, s, p);
		}

		SeqAnswer_t r = SeqParsers.Complete(name_p, seq, p);
		/****************************************/
		if (r.Reply == Reply.Ok)
			printf(u8" %s", String.GetPrimitive(
				(seq->GetStringiser(seq))(Seq.GetLast(seq))
			));
		/****************************************/

		return r;
	}

	SeqAnswer_t semicolon(Seq_t *seq, Processor_t *p) {
		SeqAnswer_t r = SeqParsers.Match(String.New(u8";"), seq, p);

		/****************************************/
		if (r.Reply == Reply.Ok)
			printf(u8";\n");
		/****************************************/

		return r;
	}

	SeqAnswer_t dot(Seq_t *seq, Processor_t *p) {
		SeqAnswer_t r = SeqParsers.Match(String.New(u8"."), seq, p);

		/****************************************/
		if (r.Reply == Reply.Ok)
			printf(u8".");
		/****************************************/

		return r;
	}

	return SeqCombinator.Bind5(
		program, name, semicolon,
		SeqParser_Block, dot,
		seq, p
	);
}

_MPLParser MPLParser = {
	.SeqParser_Program	= SeqParser_Program,
};
