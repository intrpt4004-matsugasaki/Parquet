#pragma once

#include "Parquet/Base/String.h"

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
