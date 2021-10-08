#include "Scraper/Memory.h"

static any *_Inspect(any *ptr) {
	if (ptr == NULL) Error.Panic(u8"\e[36m", u8"Memory.*");
	return ptr;
}

static any *Allocate(const size_t size) {
	return _Inspect(malloc(size));
}

static any *CountedAllocate(const size_t n, const size_t size) {
	return _Inspect(calloc(n, size));
}

static any *SharedAllocate(const size_t size) {
	return _Inspect(
		mmap(
			NULL,
			size,
			PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_ANONYMOUS,
			-1, 0
		)
	);
}

static any *ReAllocate(any *ptr, const size_t size) {
	return _Inspect(realloc(ptr, size));
}

static void Free(any *ptr) {
	free(ptr);
}

static void Delete(any *ptr) {
	if (ptr == NULL) return;

	free(ptr);
	ptr = NULL;
}

_Memory Memory = {
	.Allocate					= Allocate,
	.CountedAllocate			= CountedAllocate,
	.SharedAllocate				= SharedAllocate,
	.ReAllocate					= ReAllocate,
	.Free						= Free,

	.New						= Allocate,
	.Delete						= Delete,
};
