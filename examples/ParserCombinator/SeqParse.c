#include <Parquet.h>

SeqAnswer_t program(List_t *seq, Processor_t *p) {
	if (seq->IsEmpty(seq)) return SeqBasis.Err(seq, p);

	Answer_t p_program(String_t *s, Processor_t *p) {
		return Parsers.String.Match(String.New(u8"program"), s, p);
	}

	String_t *s = seq->Get(seq, 0);
	Answer_t r = Invoker.Invoke(p_program, s, p);

	return (r.Reply == Reply.Ok) ? SeqBasis.OkRead1(seq, p) : SeqBasis.Err(seq, p);
}

SeqAnswer_t test(List_t *seq, Processor_t *p) {
	return SeqParsers.Match(String.New(u8"test"), seq, p);
}

SeqAnswer_t program_or_test(List_t *seq, Processor_t *p) {
	return SeqCombinator.Choise(
		program, test,
		seq, p
	);
}

SeqAnswer_t program_then_test(List_t *seq, Processor_t *p) {
	return SeqCombinator.Bind(
		program, test,
		seq, p
	);
}

void main() {
	String_t *ret(any *a) { return a; }

	List_t *seq = List.NewWithStringiser(ret);
	seq->Add(seq, String.New(u8"program"));
	SeqInvoker.ParseTest(program, seq);
	seq->Delete(seq);

	seq = List.NewWithStringiser(seq->GetStringiser(seq));
	seq->Add(seq, String.New(u8"p"));
	SeqInvoker.ParseTest(program, seq);
	seq->Delete(seq);

	seq = List.NewWithStringiser(seq->GetStringiser(seq));
	seq->Add(seq, String.New(u8"test"));
	seq->Add(seq, String.New(u8";"));
	SeqInvoker.ParseTest(program_or_test, seq);
	seq->Delete(seq);

	seq = List.NewWithStringiser(seq->GetStringiser(seq));
	seq->Add(seq, String.New(u8"program"));
	seq->Add(seq, String.New(u8"test"));
	seq->Add(seq, String.New(u8";"));
	SeqInvoker.ParseTest(program_then_test, seq);
	seq->Delete(seq);
}
