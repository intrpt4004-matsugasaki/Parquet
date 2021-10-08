#include "Scraper.h"

void main() {
	String_t s = String.New(u8"var123");

	Parser_t p = Parser.New();

	p->Bind(p,
		Parser.New(Primitive.Char.Lower));

	p->Bind(p,
		Parser.Many(
			Parser.New(Primitive.Char.AlphaNum)));

	p->Select(p, 
		Parser.New(Primitive.Char.Char('')),
		Parser.New(Primitive.Char.Char(';')));

	Scraper.ParseTest(p, s);
}
