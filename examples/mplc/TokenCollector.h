#pragma once

#include <Scraper.h>

typedef enum {
	Token_Name,
	Token_Keyword,
	Token_UInt,
	Token_String,
	Token_Symbol,
} TokenType_t;


typedef struct Token_t {
	String_t *_Entity;
	TokenType_t _Type;
	uint32_t _Line;

	String_t *(* GetEntity)(struct Token_t *);
	TokenType_t (* GetType)(struct Token_t *);
	String_t *(* GetTypeString)(struct Token_t *);
	uint32_t (* GetLine)(struct Token_t *);
} Token_t;

typedef struct {
	Token_t *(* New)(String_t *tkn, TokenType_t type, uint32_t line);
	void (* Delete)(Token_t *);
} _Token;

extern _Token Token;


typedef struct TokenCollector_t {
	List_t *_Token;
	uint32_t _LineNum;

	void (* NotifyNewToken)(struct TokenCollector_t *, String_t *, TokenType_t);
	void (* NotifyNewLine)(struct TokenCollector_t *);
	void (* PrintTokens)(struct TokenCollector_t *);
	void (* PrintTokenList)(struct TokenCollector_t *);
} TokenCollector_t;

typedef struct {
	TokenCollector_t *(* New)();
	void (* Delete)(TokenCollector_t *);
} _TokenCollector;

extern _TokenCollector TokenCollector;
