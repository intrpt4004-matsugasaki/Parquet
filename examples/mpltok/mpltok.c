#include <Scraper.h>

#include "MPLLexer.h"
#include "Token.h"

void main(const int32_t argc, uint8_t *argv[]) {
	if (argc != 2) {
		printf("Usage:  $ ./mpltok [FILE]\n\n");
		exit(EXIT_FAILURE);
	}

	LexResult_t res = MPLLexer.Execute(String.FromFile(argv[1]));

	if (!res.Succeeded) {
		printf("\e[91m[error]\e[0m tokenise failed at line %d.\n", res.ErrorLine);
		printf("\e[4m                                                                      \e[0m\n");
		printf("\e[2m%s\e[0m", String.GetPrimitive(res.Precipitate));
		printf("\e[1m\e[3m\e[4m\e[6m%c\e[0m\n", String.GetCharAt(res.Subsequent, 0));
		exit(EXIT_FAILURE);
	}

	List_t *tkns = res.TokenList;
	for (uint32_t i = 0; i < List.GetLength(tkns); i++) {
		Token_t *tkn = List.Get(tkns, i);

		printf("(%s)[%s %d] ",
			String.GetPrimitive(tkn->GetEntity(tkn)),
			String.GetPrimitive(tkn->GetTypeString(tkn)),
			tkn->GetLine(tkn)
		);
	}
	printf("\n");
}
