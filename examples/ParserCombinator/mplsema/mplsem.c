#include <Parquet.h>

#include "MPLLexer.h"
#include "MPLParser.h"
#include "SymbolTableBuilder.h"

String_t *TokenToString(any *item) {
	return Token.GetEntity(item);
}

typedef struct {
	SyntaxErrorNotifier *SyntaxErrorNotifier;
	SymbolTableBuilder *SymbolTableBuilder;
} Runner;

void main(const int32_t argc, uint8_t *argv[]) {
	/* check args */
	if (argc != 2) {
		printf("Usage:  $ ./mplsem [FILE]\n\n");
		exit(EXIT_FAILURE);
	}

	/* tokenise */
	Answer_t r = Invoker.Invoke(
		MPLLexer.Parser_Program,
		String.FromFile(argv[1]),
		TokenCollector.New()
	);
	TokenCollector_t *collector = (TokenCollector_t *)(r.Processor);

	if (!String.IsEmpty(r.Subsequent)) {
		printf("\e[91m[error]\e[0m tokenise failed at line %d.\n", collector->GetLine(collector));
		printf("\e[4m                                                                      \e[0m\n");
		printf("\e[2m%s\e[0m", String.GetPrimitive(r.Precipitate));
		printf("\e[1m\e[3m\e[4m\e[6m%c\e[0m\n", String.GetCharAt(r.Subsequent, 0));
		exit(EXIT_FAILURE);
	}

	/* parse */
	List_t *tokens = TokenCollector.Get(collector);
	SeqAnswer_t sr = SeqInvoker.Invoke(
		MPLParser.SeqParser_Program,
		Seq.FromList(TokenToString, tokens),
		(Runner){
			.SyntaxErrorNotifier	= SyntaxErrorNotifier.New(),
			.SymbolTableBuilder		= SymbolTableBuilder.New()
		}
	);

	if (sr.Reply == Reply.Err) {
		SymbolTableBuilder_t *SymbolTableBuilder = (SymbolTableBuilder_t *)(sr.Processor.SyntaxErrorNotifier);

		printf("\e[91m[error]\e[0m parse failed at source line %d, formatted line %d.\n",
			Token.GetLine(tokens->Get(tokens, SymbolTableBuilder->GetLastIndex(SymbolTableBuilder))),
			SymbolTableBuilder->GetLine(SymbolTableBuilder)
		);
		printf("\e[4m                                                                      \e[0m\n");
		printf("%s\n", String.GetPrimitive(String.FromFile(argv[1])));
		printf("\e[4m                                                                      \e[0m\n");
		SymbolTableBuilder->Dump(SymbolTableBuilder);
		printf("\e[1m\e[3m\e[4m\e[6m%s\e[0m\n", String.GetPrimitive(
			TokenToString(tokens->Get(tokens, SymbolTableBuilder->GetLastIndex(SymbolTableBuilder)))
		));
		exit(EXIT_FAILURE);
	}

	/* semantic analysis */
	SymbolTableBuilder_t *SymbolTableBuilder = (SymbolTableBuilder_t *)(sr.Processor.SymbolTableBuilder);

}
