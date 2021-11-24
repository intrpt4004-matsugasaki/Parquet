#include <Parquet.h>

Answer_t anyChar3(String_t *s, Processor_t *p) {
	return Combinator.Bind3(
		Parsers.Char.Any,
		Parsers.Char.Any,
		Parsers.Char.Any,
		s, p
	);
}

Answer_t anyChar6(String_t *s, Processor_t *p) {
	return Combinator.Bind(
		anyChar3,
		anyChar3,
		s, p
	);
}

Answer_t anyChar12(String_t *s, Processor_t *p) {
	return Combinator.Bind(
		anyChar6,
		anyChar6,
		s, p
	);
}

void main() {
	String_t *s = String.New(u8"var123");
	Invoker.ParseTest(anyChar3, s);
	Invoker.ParseTest(anyChar6, s);
	Invoker.ParseTest(anyChar12, s); // error
}
