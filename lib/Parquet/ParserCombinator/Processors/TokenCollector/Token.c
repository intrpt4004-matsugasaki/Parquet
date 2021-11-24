#include "Parquet/ParserCombinator/Processors/TokenCollector/Token.h"

static String_t *GetEntity(Token_t *tkn) {
	return tkn->_Entity;
}

static tag GetType(Token_t *tkn) {
	return tkn->_Type;	
}

static uint32_t GetLine(Token_t *tkn) {
	return tkn->_Line;
}

static void Delete(Token_t *tkn) {
	Memory.Free(tkn);
}

static Token_t *New(String_t *token, tag type, uint32_t line) {
	Token_t *tkn = (Token_t *)(Memory.Allocate(sizeof(Token_t)));

	tkn->_Entity	= String.Copy(token);
	tkn->_Type		= type;
	tkn->_Line		= line;

	tkn->GetEntity	= GetEntity;
	tkn->GetType	= GetType;
	tkn->GetLine	= GetLine;
	tkn->Delete		= Delete;

	return tkn;
}

_Token Token = {
	.New		= New,
	.Delete		= Delete,

	.GetEntity	= GetEntity,
	.GetType	= GetType,
	.GetLine	= GetLine,
};
