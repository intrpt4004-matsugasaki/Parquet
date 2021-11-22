#include "Parquet/ParserCombinator/Invoker.h"

static Answer_t Parse(Answer_t (* parser)(String_t *, Processor_t), String_t *s, Processor_t p) {
	return parser(s, p);
}

static void Invoke(Answer_t (* parser)(String_t *, Processor_t), String_t *s, Processor_t p) {
	parser(s, p);
}

static void ParseTest(Answer_t (* parser)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t result = Invoker.Parse(parser, s, p);
	if (result.Reply == Reply.Err) {
		printf("Parser.ParseTest: parse failed.\n");
		return;
	}

	if (!result.Subsequent->IsEmpty(result.Subsequent)) {
		printf("Parser.ParseTest: parse incorrect.\n");
		printf("\"%s\" [%s]\n", String.GetPrimitive(result.Precipitate), String.GetPrimitive(result.Subsequent));
		return;
	}

	printf("\"%s\"\n", String.GetPrimitive(result.Precipitate));
}

_Invoker Invoker = {
	.Parse			= Parse,
	.Invoke			= Invoke,
	.ParseTest		= ParseTest,
};
