#pragma once

#include "Parquet/Base/Tag.h"
#include "Parquet/Base/String.h"

typedef struct Token_t {
	String_t *_Entity;
	tag _Type;
	uint32_t _Line;

	String_t *(* GetEntity)(struct Token_t *);
	tag (* GetType)(struct Token_t *);
	uint32_t (* GetLine)(struct Token_t *);

	void (* Delete)(struct Token_t *);
} Token_t;

typedef struct {
	Token_t *(* New)(String_t *str, tag type, uint32_t line);
	void (* Delete)(Token_t *);

	String_t *(* GetEntity)(Token_t *);
	tag (* GetType)(Token_t *);
	uint32_t (* GetLine)(Token_t *);
} _Token;

extern _Token Token;
