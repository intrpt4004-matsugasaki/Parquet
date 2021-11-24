#pragma once

#include <Parquet.h>

typedef enum {
	Token_Name,
	Token_Keyword,
	Token_UInt,
	Token_String,
	Token_Symbol,
} Token_Type;

String_t *Token_TypeString(Token_t *t);

Answer_t Parser_Comment(String_t *s, Processor_t p);
Answer_t Parser_Separator(String_t *s, Processor_t p);
Answer_t Parser_Digit(String_t *s, Processor_t p);
Answer_t Parser_Alphabet(String_t *s, Processor_t p);
Answer_t Parser_Symbol(String_t *s, Processor_t p);
Answer_t Parser_String(String_t *s, Processor_t p);
Answer_t Parser_UInt(String_t *s, Processor_t p);
Answer_t Parser_Keyword(String_t *s, Processor_t p);
Answer_t Parser_Name(String_t *s, Processor_t p);
Answer_t Parser_Token(String_t *s, Processor_t p);
Answer_t Parser_Program(String_t *s, Processor_t p);
