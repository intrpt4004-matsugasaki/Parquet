#include "Parquet/ParserCombinator/Processors/TokenCollector/TokenCollector.h"

static void Add(TokenCollector_t *tcr, String_t *token, tag type) {
	List.Add(tcr->_Sequence, Token.New(token, type, tcr->_Line));
}

static void NewLine(TokenCollector_t *tcr) {
	tcr->_Line++;
}

static uint32_t GetLine(TokenCollector_t *tcr) {
	return tcr->_Line;
}

static List_t *Get(TokenCollector_t *tcr) {
	return tcr->_Sequence;
}

static void Delete(TokenCollector_t *tcr) {
	List.Delete(tcr->_Sequence);
	Memory.Free(tcr);
}

static TokenCollector_t *New() {
	TokenCollector_t *tcr = (TokenCollector_t *)(Memory.Allocate(sizeof(TokenCollector_t)));

	tcr->_Line		= 1;
	tcr->_Sequence	= List.New();

	tcr->Add		= Add;
	tcr->NewLine	= NewLine;
	tcr->GetLine	= GetLine;
	tcr->Get		= Get;
	tcr->Delete		= Delete;

	return tcr;
}

_TokenCollector TokenCollector = {
	.New		= New,
	.Delete		= Delete,

	.Add		= Add,
	.NewLine	= NewLine,
	.GetLine	= GetLine,
	.Get		= Get,
};
