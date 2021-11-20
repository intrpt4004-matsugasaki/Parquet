#include <Parquet.h>

Result_t anyChar3(String_t *s) {
	return Combinator.Bind3(
		Parser.Char.Any,
		Parser.Char.Any,
		Parser.Char.Any,
		s
	);
}

Result_t anyChar6(String_t *s) {
	return Combinator.Bind(
		anyChar3,
		anyChar3,
		s
	);
}

Result_t anyChar12(String_t *s) {
	return Combinator.Bind(
		anyChar6,
		anyChar6,
		s
	);
}

void main() {
	String_t *s = String.New(u8"var123");
	Invoker.ParseTest(anyChar3, s);
	Invoker.ParseTest(anyChar6, s);
	Invoker.ParseTest(anyChar12, s); // error
}
