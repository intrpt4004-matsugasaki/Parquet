#include "Parquet/ParserCombinator/Basis.h"

static Answer_t Err(String_t *s, Processor_t *p) {
	return (Answer_t){
		.Reply			= Reply.Err,
		.Precipitate	= String.New(u8""),
		.Subsequent		= s,
		.Processor		= p,
	};
}

static Answer_t Ok(String_t *s, Processor_t *p) {
	return (Answer_t){
		.Reply 			= Reply.Ok,
		.Precipitate	= String.New(u8""),
		.Subsequent		= s,
		.Processor		= p
	};
}

static Answer_t OkRead1(String_t *s, Processor_t *p) {
	return (Answer_t){
		.Reply			= Reply.Ok,
		.Precipitate	= s->Substring(s, 0, 2),
		.Subsequent		= s->Substring(s, 1, s->GetLength(s) + 1),
		.Processor		= p
	};
}

_Basis Basis = {
	.Err		= Err,
	.Ok			= Ok,
	.OkRead1	= OkRead1,
};
