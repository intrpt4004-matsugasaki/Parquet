#include "TokenCollector.h"

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


static void NotifyNewToken(TokenCollector_t *pr, String_t *tkn, TokenType_t type) {
	List.Add(pr->_Token, Token.New(tkn, type, pr->_LineNum));
}

static void NotifyNewLine(TokenCollector_t *pr) {
	pr->_LineNum++;
}

static void PrintTokens(TokenCollector_t *pr) {
	for (uint32_t i = 0; i < List.GetLength(pr->_Token); i++) {
		Token_t *tkn = List.Get(pr->_Token, i);

		printf("(%s)[%s %d] ",
			String.GetPrimitive(tkn->GetEntity(tkn)),
			String.GetPrimitive(tkn->GetTypeString(tkn)),
			tkn->GetLine(tkn)
		);
	}
}

static void PrintTokenList(TokenCollector_t *pr) {
	// List拡張: 比較可能
	/*
	List_t *xs = List.New();

	for (uint32_t i = 0; i < List.GetLength(pr->_Token); i++) {
		Token_t *tkn = List.Get(pr->_Token, i);

		for (uint32_t j = 0; j < List.GetLength(xs); j++) {
			if (List.Get(xs, j)) break;
		}
	}

		printf("(%s)[%s %d] ",
			String.GetPrimitive(tkn->GetEntity(tkn)),
			String.GetPrimitive(tkn->GetTypeString(tkn)),
			tkn->GetLine(tkn)
		);
	}

	for (uint32_t i = 0; i < List.GetLength(xs); i++) {
		printf("%s %s %d\n",
			String.GetPrimitive(tkn->GetEntity(tkn)),
			String.GetPrimitive(tkn->GetTypeString(tkn)),
			tkn->GetLine(tkn)
		);
	}
	*/
}

static TokenCollector_t *New() {
	TokenCollector_t *pr = (TokenCollector_t *)(
		Memory.Allocate(sizeof(TokenCollector_t))
	);

	pr->_Token			= List.New();
	pr->_LineNum		= 1;

	pr->NotifyNewToken	= NotifyNewToken;
	pr->NotifyNewLine	= NotifyNewLine;
	pr->PrintTokens		= PrintTokens;
	pr->PrintTokenList	= PrintTokenList;

	return pr;
}

static void Delete(TokenCollector_t *pr) {
	Memory.Free(pr);
}

_TokenCollector TokenCollector = {
	.New	= New,
	.Delete	= Delete,
};
