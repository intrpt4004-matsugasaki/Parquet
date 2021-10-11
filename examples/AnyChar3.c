#include <Scraper.h>

Parse anyChar3(String_t *s) {
	return Parser.Bind3(
		Primitive.Char.Any,
		Primitive.Char.Any,
		Primitive.Char.Any,
		s
	);
}

Parse anyChar6(String_t *s) {
	return Parser.Bind(
		anyChar3,
		anyChar3,
		s
	);
}

void main() {
	String_t *s = String.New(u8"var123");
	Parser.ParseTest(anyChar3, s);

	Parser.ParseTest(anyChar6, s);
}
