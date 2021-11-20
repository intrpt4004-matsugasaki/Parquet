#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Parquet/Base/Error.h"
#include "Parquet/Base/Memory.h"

typedef struct String_t {
	int32_t _Size;
	uint8_t *_String;

	uint8_t *(* GetPrimitive)(struct String_t *);
	uint32_t (* GetLength)(struct String_t *);
	uint8_t (* GetCharAt)(struct String_t *, const uint32_t index);
	uint8_t (* GetHeadChar)(struct String_t *);

	struct String_t *(* Substring)(struct String_t *, const uint32_t beginIndex, const uint32_t lastIndex);
	struct String_t *(* Concat)(struct String_t *, struct String_t *anString);
	struct String_t *(* Copy)(struct String_t *);

	bool (* IsEmpty)(struct String_t *);
	bool (* Equals)(struct String_t *, struct String_t *anString);
	bool (* StartsWith)(struct String_t *, struct String_t *prefix);
	bool (* StartsWithChar)(struct String_t *, const uint8_t ch);

	int32_t (* FirstIndexOf)(struct String_t *, const uint8_t ch);
	int32_t (* LastIndexOf)(struct String_t *, const uint8_t ch);

	void (* Delete)(struct String_t *);
} String_t;

typedef struct {
	uint8_t NUL;

	String_t *(* New)(const uint8_t *);
	String_t *(*  FromChar)(const uint8_t ch);
	String_t *(* FromFile)(const uint8_t *path);
	void (* Delete)(String_t *);

	uint8_t *(* GetPrimitive)(String_t *);
	uint32_t (* GetLength)(String_t *);
	uint8_t (* GetCharAt)(String_t *, const uint32_t index);
	uint8_t (* GetHeadChar)(String_t *);

	String_t *(* Substring)(String_t *, const uint32_t beginIndex, const uint32_t lastIndex);
	String_t *(* Concat)(String_t *, String_t *anString);
	String_t *(* Copy)(String_t *);

	bool (* IsEmpty)(String_t *);
	bool (* Equals)(String_t *, String_t *anString);
	bool (* StartsWith)(String_t *, String_t *prefix);
	bool (* StartsWithChar)(String_t *, const uint8_t ch);

	int32_t (* FirstIndexOf)(String_t *, const uint8_t ch);
	int32_t (* LastIndexOf)(String_t *, const uint8_t ch);
} _String;

extern _String String;
