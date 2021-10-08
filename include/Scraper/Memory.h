#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>

#include "Scraper/Error.h"

#define any void

typedef struct {
	any *(* Allocate)(const size_t size);
	any *(* CountedAllocate)(const size_t n, const size_t size);
	any *(* SharedAllocate)(const size_t size);

	any *(* ReAllocate)(any *ptr, const size_t size);

	void (* Free)(void *ptr);

	any *(* New)(const size_t size);
	void (* Delete)(void *ptr);
} _Memory;

extern _Memory Memory;
