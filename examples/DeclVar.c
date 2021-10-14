#include <Scraper.h>

String_t *ident;

Result_t declVar(String_t *s) {
	Result_t var(String_t *s) {
		return Primitive.String.Match(
			String.New(u8"var"),
			s
		);
	}

	Result_t prs = Parser.Bind(
		var,
		Primitive.Char.Space,
		s
	);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  String_t *precip = prs.Precipitate;

	Result_t alnums(String_t *s) {
		return Parser.Many0(
			Primitive.Char.AlphaNum,
			s
		);
	}

	prs = Parser.Bind(
		Primitive.Char.Lower,
		alnums,
		prs.Subsequent
	);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  precip = String.Concat(precip, prs.Precipitate);
  ident = prs.Precipitate;

	prs = Primitive.Char.Char(';', prs.Subsequent);
	  if (prs.Reply == Err) return Parser.makeErr(s);
	  precip = String.Concat(precip, prs.Precipitate);

	return (Result_t){
		.Reply			= Ok,
		.Precipitate	= precip,
		.Subsequent		= prs.Subsequent,
	};
}

void main() {
	String_t *s = String.New(u8"var mIkO352;");

	/* 簡易テスタ */
	Parser.ParseTest(declVar, s);
	printf(u8"varname: %s\n", String.GetPrimitive(ident));

	/* 解析動作のみ */
	Parser.Invoke(declVar, String.New(u8"var parser3;"));
	printf(u8"varname: %s\n", String.GetPrimitive(ident));

	Parser.ParseTest(declVar, String.New(u8"var Parser;")); // error
	Parser.ParseTest(declVar, String.New(u8"var 9arser;")); // error
	Parser.ParseTest(declVar, String.New(u8"var parser ;")); // error
	Parser.ParseTest(declVar, String.New(u8"var  parser ;")); // error
	Parser.ParseTest(declVar, String.New(u8" var parser ;")); // error
	Parser.ParseTest(declVar, String.New(u8"vaa parser ;")); // error
	Parser.ParseTest(declVar, String.New(u8"var parser; ")); // Ok...
}
