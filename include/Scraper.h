#pragma once

#include "Scraper/Error.h"
#include "Scraper/String.h"
#include "Scraper/List.h"

#include "Scraper/Parser.h"
#include "Scraper/Primitive.h"

typedef struct {
	void (* ParseTest)(Parser_t *, String_t *);
} _Scraper;

extern _Scraper Scraper;
