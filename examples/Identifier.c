#include <Scraper.h>

void main() {
	String_t *s = String.New(u8"var123");

	Parser_t *p = Parser.New();

	p->Bind(p,
		Parser.From(Primitive.Char.Lower));

	p->Bind(p,
		Parser.Many(
			Parser.From(Primitive.Char.AlphaNum)));

	p->Select(p, 
		Parser.From(Primitive.Char.Char('')),
		Parser.FromPrimitive.Char.Char(';')));

	Scraper.ParseTest(p, s);
}
