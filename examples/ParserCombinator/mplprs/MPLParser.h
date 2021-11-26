#pragma once

#include <Parquet.h>

#include "MPLLexer.h"

typedef struct {
	SeqAnswer_t (* SeqParser_VarName)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_ProcName)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_Const)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_StdType)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_AddOpr)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_MulOpr)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_RelOpr)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_Var)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_Factor)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_Term)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_LeftPart)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_SimpleExpr)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_Expr)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_AssignStmt)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_CondStmt)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_IterStmt)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_ExitStmt)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_Exprs)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_CallStmt)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_RetStmt)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_InputStmt)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_OutputStmt)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_OutputFmt)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_CompoundStmt)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_Stmt)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_VarNames)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_ArrType)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_Type)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_VarDecl)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_FormalParam)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_SubProgDecl)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_Block)(Seq_t *seq, Processor_t *p);
	SeqAnswer_t (* SeqParser_Program)(Seq_t *seq, Processor_t *p);
} _MPLParser;

extern _MPLParser MPLParser;
