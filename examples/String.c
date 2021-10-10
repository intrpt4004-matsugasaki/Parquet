#include <Scraper.h>

void main() {
	String_t *s = String.New(u8"hello string world!");
	String_t *e = String.New(u8"");

	printf("%s %d\n", s->GetPrimitive(s), s->GetLength(s));
	printf("%s %d\n", String.GetPrimitive(s), String.GetLength(s));

	printf("%c %c\n", s->GetCharAt(s, 1), s->GetHeadChar(s));
	printf("%c %c\n", String.GetCharAt(s, 1), String.GetHeadChar(s));

	printf("%s %s\n", String.GetPrimitive(s->Substring(s, 3, 10)), String.GetPrimitive(String.Substring(s, 2, 6)));

	printf("%d %d\n", s->IsEmpty(s), String.IsEmpty(e));
	printf("%d %d\n", s->Equals(s, e), String.Equals(e, e));

	printf("%d %d\n", s->StartsWith(s, String.New("hello")), String.StartsWith(s, String.New("hel")));
	printf("%d %d\n", s->StartsWithChar(s, 'h'), String.StartsWithChar(s, 'e'));
}
