#pragma once

#include <Scraper.h>

#include "TokenCollector.h"

typedef struct {
	TokenCollector_t *(* Invoke)(String_t *code);
} _MPLParser;

extern _MPLParser MPLParser;
