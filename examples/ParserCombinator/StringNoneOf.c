#include <Parquet.h>

Answer_t parser(String_t *s, Processor_t *p) {
	List_t *pats = List.New();

	pats->Add(pats, String.New(u8"aaaa"));
	pats->Add(pats, String.New(u8"bb"));
	pats->Add(pats, String.New(u8"ccc"));
	pats->Add(pats, String.New(u8"d"));

	return Parsers.String.NoneOf(pats, s, p);
}

void main() {
	String_t *s = String.New(u8"abc");
	Invoker.ParseTest(parser, s);

	s = String.New(u8"d");
	Invoker.ParseTest(parser, s);
}
