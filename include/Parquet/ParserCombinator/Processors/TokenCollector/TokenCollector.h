#pragma once

#include "Parquet/Base/Memory.h"
#include "Parquet/Base/Tag.h"
#include "Parquet/Base/String.h"
#include "Parquet/Base/List.h"
#include "Parquet/ParserCombinator/Processors/TokenCollector/Token.h"

typedef struct TokenCollector_t {
	uint32_t _Line;
	List_t *_Sequence;

	void (* Add)(struct TokenCollector_t *, String_t *token, tag type);
	void (* NewLine)(struct TokenCollector_t *);
	uint32_t (* GetLine)(struct TokenCollector_t *);
	List_t *(* Get)(struct TokenCollector_t *);

	void (* Delete)(struct TokenCollector_t *);
} TokenCollector_t;

typedef struct {
	TokenCollector_t *(* New)();
	void (* Delete)(TokenCollector_t *);

	void (* Add)(TokenCollector_t *, String_t *token, tag type);
	void (* NewLine)(TokenCollector_t *);
	uint32_t (* GetLine)(TokenCollector_t *);
	List_t *(* Get)(TokenCollector_t *);
} _TokenCollector;

extern _TokenCollector TokenCollector;
