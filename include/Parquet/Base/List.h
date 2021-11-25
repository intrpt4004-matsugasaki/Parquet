#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "Parquet/Base/Any.h"
#include "Parquet/Base/Error.h"
#include "Parquet/Base/Memory.h"
#include "Parquet/Base/String.h"

typedef struct List_t {
	uint32_t _Size;
	uint32_t _Length;
	any **_Item;

	bool _ContainsStringiser;
	String_t *(* _Stringiser)(any *item);

	bool (* ContainsStringiser)(struct List_t *);
	void (* SetStringiser)(struct List_t *, String_t *(* stringiser)(any *item));
	String_t *(*(* GetStringiser)(struct List_t *)) (any *item);

	void (* Add)(struct List_t *, any *item);
	void (* AddAll)(struct List_t *, struct List_t *);

	uint32_t (* GetLength)(struct List_t *);
	any *(* Get)(struct List_t *, const uint32_t idx);

	struct List_t *(* GetHeadList)(struct List_t *);
	struct List_t *(* GetTailList)(struct List_t *);

	struct List_t *(* GetListWhoseBasisWasDuplicated)(struct List_t *);

	bool (* IsEmpty)(struct List_t *);

	void (* Delete)(struct List_t *);
} List_t;

typedef struct {
	uint32_t _ALLOCATION_BLOCK_SIZE;

	List_t *(* New)();
	List_t *(* NewWithStringiser)(String_t *(* stringiser)(any *item));
	void (* Delete)(List_t *);

	bool (* ContainsStringiser)(List_t *);
	void (* SetStringiser)(List_t *, String_t *(* stringiser)(any *item));
	String_t *(*(* GetStringiser)(List_t *)) (any *item);

	void (* Add)(List_t *, any *item);
	void (* AddAll)(List_t *, List_t *);

	uint32_t (* GetLength)(List_t *);
	any *(* Get)(List_t *, const uint32_t idx);

	List_t *(* GetHeadList)(List_t *);
	List_t *(* GetTailList)(List_t *);

	List_t *(* GetListWhoseBasisWasDuplicated)(List_t *);

	bool (* IsEmpty)(List_t *);
} _List;

extern _List List;
