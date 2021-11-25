#include "Parquet/ParserCombinator/Sequence/SeqInvoker.h"

static SeqAnswer_t Invoke(SeqAnswer_t (* seqParser)(List_t *, Processor_t *), List_t *seq, Processor_t *p) {
	return seqParser(seq, p);
}

static SeqAnswer_t Parse(SeqAnswer_t (* seqParser)(List_t *, Processor_t *), List_t *seq) {
	return SeqInvoker.Invoke(seqParser, seq, NULL);
}

static void InvokeTest(SeqAnswer_t (* seqParser)(List_t *, Processor_t *), List_t *seq, Processor_t *p) {
	SeqAnswer_t result = SeqInvoker.Invoke(seqParser, seq, p);
	if (result.Reply == Reply.Err) {
		printf("SeqInvoker.InvokeTest: parse failed.\n");
		return;
	}

	if (!result.Subsequent->IsEmpty(result.Subsequent)) {
		printf("SeqInvoker.InvokeTest: parse incorrect.\n");

		for (uint32_t i = 0; i < List.GetLength(result.Precipitate); i++)
			printf("(%s) ", String.GetPrimitive(List.Get(result.Precipitate, i)));
		printf("\n");

		for (uint32_t i = 0; i < List.GetLength(result.Subsequent); i++)
			printf("[%s] ", String.GetPrimitive(List.Get(result.Subsequent, i)));
		printf("\n");

		return;
	}

	for (uint32_t i = 0; i < List.GetLength(result.Precipitate); i++)
		printf("(%s) ", String.GetPrimitive(List.Get(result.Precipitate, i)));
	printf("\n");
}

static void ParseTest(SeqAnswer_t (* seqParser)(List_t *, Processor_t *), List_t *seq) {
	SeqAnswer_t result = SeqInvoker.Parse(seqParser, seq);
	if (result.Reply == Reply.Err) {
		printf("SeqInvoker.ParseTest: parse failed.\n");
		return;
	}

	if (!result.Subsequent->IsEmpty(result.Subsequent)) {
		printf("SeqInvoker.ParseTest: parse incorrect.\n");

		for (uint32_t i = 0; i < List.GetLength(result.Precipitate); i++)
			printf("(%s) ", String.GetPrimitive(List.Get(result.Precipitate, i)));
		printf("\n");

		for (uint32_t i = 0; i < List.GetLength(result.Subsequent); i++)
			printf("[%s] ", String.GetPrimitive(List.Get(result.Subsequent, i)));
		printf("\n");

		return;
	}

	for (uint32_t i = 0; i < List.GetLength(result.Precipitate); i++)
		printf("(%s) ", String.GetPrimitive(List.Get(result.Precipitate, i)));
	printf("\n");
}

_SeqInvoker SeqInvoker = {
	.Invoke			= Invoke,
	.Parse			= Parse,
	.InvokeTest		= InvokeTest,
	.ParseTest		= ParseTest,
};
