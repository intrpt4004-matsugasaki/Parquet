#pragma once

#include "Parquet/Base/String.h"

typedef void *Processor_t;

typedef enum {
	Reply_Ok, Reply_Err
} __Reply;

typedef int32_t Tag;
typedef struct {
	Tag Ok;
	Tag Err;
} _Reply;

extern _Reply Reply;

typedef struct {
	__Reply Reply;

	String_t *Precipitate;
	String_t *Subsequent;

	Processor_t Processor;
} Answer_t;

/**
 * [1] Parser definition:
 *  A parser is a function
 *   - which takes
 *		~ a string 's' of String_t type type to parse
 *		~ a processor 'p' of Processor_t (= void *; generic pointer) type to do arbitrary processing
 *     as arguments.
 *   - which returns a value of Answer_t type as parsing result.
 *
 * Answer_t Parser(String_t *s, Processor_t p) {
 *     return {a combinated parser}(s, p);
 * }
 *
 *
 *
 * [2] If you need to do some processing like {AST building, logging, ...} along with the parse:
 *
 * Answer_t Parser(String_t *s, Processor_t p) {
 *     Answer_t a = {a combinated parser}(s, p);
 *
 *     p->{var} = {value};
 *     p->{function}({args});
 *     ...
 *
 *     return a;
 * }
 *
 * typedef struct {
 *     {type} {var};
 *     void (* {function})({args});
 * } Runner;
 *
 * void {function}({args}) {
 *     ...	 
 * }
 * 
 * Runner *r = Memory.Allocate(sizeof(Runner));
 * r->{function} = {function};
 * Parser(String.New(u8"{text to parse}"), r);
 *
 *
 *
 * [3] If you don't need to do some processing along with the parse:
 *
 * Parser(String.New(u8"{text to parse}"), NULL);
 **/
