#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "Parquet/Base/Any.h"
#include "Parquet/Base/Error.h"
#include "Parquet/Base/Memory.h"
#include "Parquet/Base/String.h"

typedef struct Seq_t {
	uint32_t _Size;
	uint32_t _Length;
	any **_Item;
	String_t *(* _Stringiser)(any *item);

	String_t *(*(* GetStringiser)(struct Seq_t *)) (any *item);

	void (* Add)(struct Seq_t *, any *item);
	void (* AddAll)(struct Seq_t *, struct Seq_t *);

	uint32_t (* GetLength)(struct Seq_t *);
	any *(* Get)(struct Seq_t *, const uint32_t idx);

	any *(* GetHead)(struct Seq_t *);

	struct Seq_t *(* GetHeadSeq)(struct Seq_t *);
	struct Seq_t *(* GetTailSeq)(struct Seq_t *);

	struct Seq_t *(* Duplicate)(struct Seq_t *);

	bool (* IsEmpty)(struct Seq_t *);

	void (* Delete)(struct Seq_t *);
} Seq_t;

typedef struct {
	uint32_t _ALLOCATION_BLOCK_SIZE;

	String_t *(* STRINGISER_STRING)(any *item);

	Seq_t *(* New)(String_t *(* stringiser)(any *item));
	void (* Delete)(Seq_t *);

	String_t *(*(* GetStringiser)(Seq_t *)) (any *item);

	void (* Add)(Seq_t *, any *item);
	void (* AddAll)(Seq_t *, Seq_t *);

	uint32_t (* GetLength)(Seq_t *);
	any *(* Get)(Seq_t *, const uint32_t idx);

	any *(* GetHead)(Seq_t *);

	Seq_t *(* GetHeadSeq)(Seq_t *);
	Seq_t *(* GetTailSeq)(Seq_t *);

	Seq_t *(* Duplicate)(Seq_t *);

	bool (* IsEmpty)(Seq_t *);
} _Seq;

extern _Seq Seq;
