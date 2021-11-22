#include <Parquet.h>

String_t *ident;

Answer_t declVar(String_t *s, Processor_t p) {
	Answer_t var_space(String_t *s, Processor_t p) {
		Answer_t var(String_t *s, Processor_t p) {
			return Parsers.String.Match(
				String.New(u8"var"),
				s, p
			);
		}

		return Combinator.Bind(
			var,
			Parsers.Char.Space,
			s, p
		);
	}

	Answer_t varname(String_t *s, Processor_t p) {
		Answer_t alnums0(String_t *s, Processor_t p) {
			return Combinator.Many0(
				Parsers.Char.AlphaNum,
				s, p
			);
		}

		return Combinator.Bind(
			Parsers.Char.Lower,
			alnums0,
			s, p
		);
	}

	Answer_t semic(String_t *s, Processor_t p) {
		return Parsers.Char.Match(';', s, p);
	}

	Answer_t result = Invoker.Parse(var_space, s);
	if (result.Reply == Reply.Err) return Basis.Err(s, p);
	String_t *precip = result.Precipitate;

	result = Invoker.Parse(varname, result.Subsequent);
	if (result.Reply == Reply.Err) return Basis.Err(s, p);
	precip = String.Concat(precip, result.Precipitate);
	ident = result.Precipitate;

	result = Invoker.Parse(semic, result.Subsequent);
	if (result.Reply == Reply.Err) return Basis.Err(s, p);

	return (Answer_t){
		.Reply			= Reply.Ok,
		.Precipitate	= String.Concat(precip, result.Precipitate),
		.Subsequent		= result.Subsequent,
	};
}

void main() {
	String_t *s = String.New(u8"var mIkO352;");

	/* 簡易テスタ */
	Invoker.ParseTest(declVar, s); // Ok
	printf(u8"varname: %s\n", String.GetPrimitive(ident));

	/* 解析動作のみ */
	Invoker.Parse(declVar, String.New(u8"var parser3;")); // Ok
	printf(u8"varname: %s\n", String.GetPrimitive(ident));

	Invoker.ParseTest(declVar, String.New(u8"var Parser;")); // error
	Invoker.ParseTest(declVar, String.New(u8"var 9arser;")); // error
	Invoker.ParseTest(declVar, String.New(u8"var parser ;")); // error
	Invoker.ParseTest(declVar, String.New(u8"var  parser ;")); // error
	Invoker.ParseTest(declVar, String.New(u8" var parser ;")); // error
	Invoker.ParseTest(declVar, String.New(u8"vaa parser ;")); // error
	Invoker.ParseTest(declVar, String.New(u8"var parser; ")); // incorrect
}
