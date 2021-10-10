#include <Scraper.h>

void parse(String_t *s) {
	Parse prs = Primitive.Char.Any(s);
	if (prs.Reply == Err) {
		printf("parse failed.\n");
		return;
	}
	printf("%s:%s\n",
		String.GetPrimitive(prs.Precipitate),
		String.GetPrimitive(prs.Subsequent)
	);


	prs = Primitive.Char.Any(prs.Subsequent);
	if (prs.Reply == Err) {
		printf("parse failed.\n");
		return;
	}
	printf("%s:%s\n",
		String.GetPrimitive(prs.Precipitate),
		String.GetPrimitive(prs.Subsequent)
	);


	prs = Primitive.Char.Any(prs.Subsequent);
	if (prs.Reply == Err) {
		printf("parse failed.\n");
		return;
	}
	printf("%s:%s\n",
		String.GetPrimitive(prs.Precipitate),
		String.GetPrimitive(prs.Subsequent)
	);
}

void main() {
	String_t *s = String.New(u8"var123");
	parse(s);
}
