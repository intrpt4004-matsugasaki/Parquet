#include "Parquet/ParserCombinator/Basis.h"

static Result_t Err(String_t *s) {
	return (Result_t){
		.Reply			= Failed,
		.Precipitate	= String.New(u8""),
		.Subsequent		= s,
	};
}

static Result_t Ok(String_t *s) {
	return (Result_t){
		.Reply 			= Succeeded,
		.Precipitate	= String.New(u8""),
		.Subsequent		= s,
	};
}

static Result_t OkRead1(String_t *s) {
	return (Result_t){
		.Reply			= Succeeded,
		.Precipitate	= s->Substring(s, 0, 2),
		.Subsequent		= s->Substring(s, 1, s->GetLength(s) + 1),
	};
}

_Basis Basis = {
	.Err		= Err,
	.Ok			= Ok,
	.OkRead1	= OkRead1,
};
