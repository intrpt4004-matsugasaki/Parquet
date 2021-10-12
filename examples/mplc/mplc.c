#include <Scraper.h>

#include "MPLLexer.h"
#include "Token.h"
//#include "MPLParser.h"
//#include "AST.h"
//#include "MPLGenerator.h"

void main(const int32_t argc, uint8_t *argv[]) {
	List_t *tkns = MPLLexer.Execute(String.FromFile(argv[1]));

	for (uint32_t i = 0; i < List.GetLength(tkns); i++) {
		Token_t *tkn = List.Get(tkns, i);

		printf("(%s)[%s %d] ",
			String.GetPrimitive(tkn->GetEntity(tkn)),
			String.GetPrimitive(tkn->GetTypeString(tkn)),
			tkn->GetLine(tkn)
		);
	}
	printf("\n");

	//AST_t *ast = MPLParser.Execute(tkns);
	// = MPLGenerator.Execute(ast);
}
