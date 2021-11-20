#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>

#include "Parquet/Base/Error.h"

#define any void

typedef struct {
	any *(* Allocate)(const size_t size);
	any *(* CountedAllocate)(const size_t n, const size_t size);
	any *(* ReAllocate)(any *ptr, const size_t size);

	void (* Free)(any *ptr);
} _Memory;

extern _Memory Memory;
