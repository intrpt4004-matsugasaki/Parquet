#include "Scraper/Invoker.h"

static Result_t Parse(Result_t (* parser)(String_t *), String_t *s) {
	return parser(s);
}

static void Invoke(Result_t (* parser)(String_t *), String_t *s) {
	parser(s);
}

static void ParseTest(Result_t (* parser)(String_t *), String_t *s) {
	Result_t result = Invoker.Parse(parser, s);
	if (result.Reply == Failed) {
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
