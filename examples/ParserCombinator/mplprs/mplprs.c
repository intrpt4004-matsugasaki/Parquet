#include <Parquet.h>

#include "MPLParser.h"

void main(const int32_t argc, uint8_t *argv[]) {
	MPLParser.Execute(String.FromFile(argv[1]));

/*
	ParseResult_t res = MPLParser.Execute(String.FromFile(argv[1]));

	if (!res.Succeeded) {
		printf("\e[91m[error]\e[0m parse failed at line %d.\n\n", res.ErrorLine);
		printf("\e[2m%s\e[0m", String.GetPrimitive(res.Precipitate));
		//printf("\e[1m\e[3m\e[4m\e[6m%c\e[0m\n", String.GetCharAt(res.Subsequent, 0));
		printf("\e[1m\e[3m\e[4m\e[6m%c\e[0m", String.GetCharAt(res.Subsequent, 0));
		printf("\e[2m%s\n", String.GetPrimitive(String.Substring(res.Subsequent, 1, String.GetLength(res.Subsequent))));
		exit(EXIT_FAILURE);
	}

	printf("\e[2m%s\e[0m", String.GetPrimitive(res.Precipitate));
	printf("\e[1m\e[3m\e[4m\e[6m%c\e[0m\n", String.GetCharAt(res.Subsequent, 0));
*/
}
