#pragma once

#include "Scraper/String.h"
#include "Scraper/List.h"

typedef struct {
} Parse;

typedef struct Parser_t {
	List_t *_Parser;

	void (* Bind)(struct Parser_t *, struct Parser_t *p);
	void (* Select)(struct Parser_t *, struct Parser_t *left, struct Parser_t *right);
	void (* Run)(struct Parser_t *);
} Parser_t;

typedef struct {
	Parser_t *(* New)();
	Parser_t *(* From)(Parse (* primitive)(String_t *));
} _Parser;

extern _Parser Parser;
