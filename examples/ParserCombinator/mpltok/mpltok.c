#include <Parquet.h>

#include "MPLLexer.h"

void main(const int32_t argc, uint8_t *argv[]) {
	if (argc != 2) {
		printf("Usage:  $ ./mpltok [FILE]\n\n");
		exit(EXIT_FAILURE);
	}

	Answer_t r = Invoker.Invoke(Parser_Program, String.FromFile(argv[1]), TokenCollector.New());
	TokenCollector_t *collector = (TokenCollector_t *)(r.Processor);

	if (r.Reply == Reply.Err) {
		printf("\e[91m[error]\e[0m tokenise failed at line %d.\n", collector->GetLine(collector));
		printf("\e[4m                                                                      \e[0m\n");
		printf("\e[2m%s\e[0m", String.GetPrimitive(r.Precipitate));
		printf("\e[1m\e[3m\e[4m\e[6m%c\e[0m\n", String.GetCharAt(r.Subsequent, 0));
		exit(EXIT_FAILURE);
	}

	List_t *tkns = collector->Get(collector);
	for (uint32_t i = 0; i < List.GetLength(tkns); i++) {
		Token_t *tkn = List.Get(tkns, i);

		printf("(%s)[%s %d] ",
			String.GetPrimitive(tkn->GetEntity(tkn)),
			String.GetPrimitive(TokenTypeString(tkn)),
			tkn->GetLine(tkn)
		);
	}
	printf("\n");
}
