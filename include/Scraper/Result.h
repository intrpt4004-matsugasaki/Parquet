#pragma once

#include "Scraper/String.h"

typedef struct {
	/*enum {
		Consumed,
		Empty,
	} Consumed;*/

	enum {
		Succeeded,
		Failed,
	} Reply;

	String_t *Precipitate;
	String_t *Subsequent;
} Result_t;
