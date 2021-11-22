#include "Parquet/ParserCombinator/Invoker.h"

static Answer_t Invoke(Answer_t (* parser)(String_t *, Processor_t), String_t *s, Processor_t p) {
	return parser(s, p);
}

static Answer_t Parse(Answer_t (* parser)(String_t *, Processor_t), String_t *s) {
	return Invoker.Invoke(parser, s, NULL);
}

static void InvokeTest(Answer_t (* parser)(String_t *, Processor_t), String_t *s, Processor_t p) {
	Answer_t result = Invoker.Invoke(parser, s, p);
	if (result.Reply == Reply.Err) {
		printf("Parser.InvokeTest: parse failed.\n");
		return;
	}

	if (!result.Subsequent->IsEmpty(result.Subsequent)) {
		printf("Parser.InvokeTest: parse incorrect.\n");
		printf("\"%s\" [%s]\n", String.GetPrimitive(result.Precipitate), String.GetPrimitive(result.Subsequent));
		return;
	}

	printf("\"%s\"\n", String.GetPrimitive(result.Precipitate));
}

static void ParseTest(Answer_t (* parser)(String_t *, Processor_t), String_t *s) {
	Answer_t result = Invoker.Parse(parser, s);
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
	.Invoke			= Invoke,
	.Parse			= Parse,
	.InvokeTest		= InvokeTest,
	.ParseTest		= ParseTest,
};
