#include <Parquet.h>

#include "MPLParser.h"

void main(const int32_t argc, uint8_t *argv[]) {
	ParseResult_t res = MPLParser.Execute(String.FromFile(argv[1]));

	if (!res.Succeeded) {
		printf("\e[91m[error]\e[0m parse failed at line %d.\n\n", res.ErrorLine);
		printf("\e[2m%s\e[0m", String.GetPrimitive(res.Precipitate));
		printf("\e[1m\e[3m\e[4m\e[6m%c\e[0m\n", String.GetCharAt(res.Subsequent, 0));
		exit(EXIT_FAILURE);
	}

	printf("\e[2m%s\e[0m", String.GetPrimitive(res.Precipitate));
	printf("\e[1m\e[3m\e[4m\e[6m%c\e[0m\n", String.GetCharAt(res.Subsequent, 0));
}
