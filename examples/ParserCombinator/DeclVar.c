#include <Parquet.h>

String_t *ident;

Result_t declVar(String_t *s) {
	Result_t var_space(String_t *s) {
		Result_t var(String_t *s) {
			return Parser.String.Match(
				String.New(u8"var"),
				s
			);
		}

		return Combinator.Bind(
			var,
			Parser.Char.Space,
			s
		);
	}

	Result_t varname(String_t *s) {
		Result_t alnums0(String_t *s) {
			return Combinator.Many0(
				Parser.Char.AlphaNum,
				s
			);
		}

		return Combinator.Bind(
			Parser.Char.Lower,
			alnums0,
			s
		);
	}

	Result_t semic(String_t *s) {
		return Parser.Char.Match(';', s);
	}

	Result_t result = Invoker.Parse(var_space, s);
	if (result.Reply == Failed) return Basis.Err(s);
	String_t *precip = result.Precipitate;

	result = Invoker.Parse(varname, result.Subsequent);
	if (result.Reply == Failed) return Basis.Err(s);
	precip = String.Concat(precip, result.Precipitate);
	ident = result.Precipitate;

	result = Invoker.Parse(semic, result.Subsequent);
	if (result.Reply == Failed) return Basis.Err(s);

	return (Result_t){
		.Reply			= Succeeded,
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
	Invoker.Invoke(declVar, String.New(u8"var parser3;")); // Ok
	printf(u8"varname: %s\n", String.GetPrimitive(ident));

	Invoker.ParseTest(declVar, String.New(u8"var Parser;")); // error
	Invoker.ParseTest(declVar, String.New(u8"var 9arser;")); // error
	Invoker.ParseTest(declVar, String.New(u8"var parser ;")); // error
	Invoker.ParseTest(declVar, String.New(u8"var  parser ;")); // error
	Invoker.ParseTest(declVar, String.New(u8" var parser ;")); // error
	Invoker.ParseTest(declVar, String.New(u8"vaa parser ;")); // error
	Invoker.ParseTest(declVar, String.New(u8"var parser; ")); // incorrect
}
