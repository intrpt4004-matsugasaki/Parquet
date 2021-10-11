#include <Scraper.h>

Parse anyChar3(String_t *s) {
	Parse prs = Primitive.Char.Any(s);
	if (prs.Reply == Err) return prs;
	String_t *precip = prs.Precipitate;

	prs = Primitive.Char.Any(prs.Subsequent);
	if (prs.Reply == Err) return prs;
	precip = String.Concat(precip, prs.Precipitate);

	prs = Primitive.Char.Any(prs.Subsequent);
	if (prs.Reply == Err) return prs;
	precip = String.Concat(precip, prs.Precipitate);

	return (Parse){
		.Reply			= Ok,
		.Precipitate	= precip,
		.Subsequent		= prs.Subsequent,
	};
}

void main() {
	String_t *s = String.New(u8"var123");
	Parser.ParseTest(anyChar3, s);
}
