#include "Token.h"

static String_t *GetEntity(Token_t *t) {
	return t->_Entity;
}

static TokenType_t GetType(Token_t *t) {
	return t->_Type;
}

static uint32_t GetLine(Token_t *t) {
	return t->_Line;
}

static String_t *GetTypeString(Token_t *t) {
	switch (t->GetType(t)) {
		case Token_Name:		return String.New(u8"Name");
		case Token_Keyword:		return String.New(u8"Keyword");
		case Token_UInt:		return String.New(u8"UInt");
		case Token_String:		return String.New(u8"String");
		case Token_Symbol:		return String.New(u8"Symbol");
	}
}

static Token_t *Token_New(String_t *tkn, TokenType_t type, uint32_t line) {
	Token_t *t = (Token_t *)(Memory.Allocate(sizeof(Token_t)));

	t->_Entity			= tkn;
	t->_Type			= type;
	t->_Line			= line;

	t->GetEntity		= GetEntity;
	t->GetType			= GetType;
	t->GetTypeString	= GetTypeString;
	t->GetLine			= GetLine;

	return t;
}

static void Token_Delete(Token_t *t) {
	Memory.Free(t);
}

_Token Token = {
	.New	= Token_New,
	.Delete	= Token_Delete,
};
