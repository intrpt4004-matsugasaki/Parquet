#pragma once

#include "Parquet/Base/String.h"
#include "Parquet/ParserCombinator/Parser.h"

typedef struct {
	Answer_t (* Err)(String_t *, Processor_t *);
	Answer_t (* Ok)(String_t *, Processor_t *);
	Answer_t (* OkRead1)(String_t *, Processor_t *);
} _Basis;

extern _Basis Basis;

/**
 * [1] If you want to easily configure the return value of the parser:
 *
 * (1)
 * return (Answer_t){
 *     Reply		= Reply.Err,
 *     Precipitate	= "",
 *     Subsequent	= ###,
 *     Processor    = p,
 * };
 *
 * >>> return Basis.Err(###, p);
 *
 *
 * (2)
 * return (Answer_t){
 *     Reply		= Reply.Ok,
 *     Precipitate	= "",
 *     Subsequent	= ###,
 *     Processor    = p,
 * };
 *
 * >>> return Basis.Ok(###, p);
 *
 *
 * (3)
 * return (Answer_t){
 *     Reply		= Reply.Ok,
 *     Precipitate	= "" + #,
 *     Subsequent	= ##,
 *     Processor    = p,
 * };
 *
 * >>> return Basis.OkRead1(###, p);
 **/
