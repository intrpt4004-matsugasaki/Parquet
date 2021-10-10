#include "Scraper/Memory.h"

static any *_Inspect(any *ptr) {
	if (ptr == NULL) Error.Panic(u8"\e[36m", u8"Memory._Inspect: malloc failed");
	return ptr;
}

static any *Allocate(const size_t size) {
	return _Inspect(malloc(size));
}

static any *CountedAllocate(const size_t n, const size_t size) {
	return _Inspect(calloc(n, size));
}

static any *ReAllocate(any *ptr, const size_t size) {
	return _Inspect(realloc(ptr, size));
}

static void Free(any *ptr) {
	free(ptr);
}

_Memory Memory = {
	.Allocate					= Allocate,
	.CountedAllocate			= CountedAllocate,
	.ReAllocate					= ReAllocate,

	.Free						= Free,
};
