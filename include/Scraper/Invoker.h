#pragma once

#include "Scraper/String.h"

#include "Scraper/Result.h"

typedef struct {
	Result_t (* Parse)(Result_t (* parser)(String_t *), String_t *);
	void (* Invoke)(Result_t (* parser)(String_t *), String_t *);
	void (* ParseTest)(Result_t (* parser)(String_t *), String_t *);
} _Invoker;

extern _Invoker Invoker;
