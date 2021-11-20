#pragma once

#include "Scraper/String.h"

#include "Scraper/Result.h"

typedef struct {
	Result_t (* Err)(String_t *);
	Result_t (* Ok)(String_t *);
	Result_t (* OkRead1)(String_t *);
} _Basis;

extern _Basis Basis;
