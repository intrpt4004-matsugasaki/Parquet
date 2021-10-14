#include <Scraper.h>

Result_t anyChar3(String_t *s) {
	return Parser.Bind3(
		Primitive.Char.Any,
		Primitive.Char.Any,
		Primitive.Char.Any,
		s
	);
}

Result_t anyChar6(String_t *s) {
	return Parser.Bind(
		anyChar3,
		anyChar3,
		s
	);
}

Result_t anyChar12(String_t *s) {
	return Parser.Bind(
		anyChar6,
		anyChar6,
		s
	);
}

void main() {
	String_t *s = String.New(u8"var123");
	Parser.ParseTest(anyChar3, s);
	Parser.ParseTest(anyChar6, s);
	Parser.ParseTest(anyChar12, s); // error
}
