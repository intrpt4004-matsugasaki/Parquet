#include "Parquet/Base/Seq.h"

static String_t *(* GetStringiser(Seq_t *seq))(any *item) {
	return seq->_Stringiser;
}

static void Add(Seq_t *seq, any *item) {
	if (Seq.GetLength(seq) + 1 >= seq->_Size) {
		seq->_Size += Seq._ALLOCATION_BLOCK_SIZE;
		seq->_Item = Memory.ReAllocate(
			seq->_Item,
			seq->_Size * sizeof(any *)
		);
	}

	seq->_Item[Seq.GetLength(seq)] = item;
	seq->_Length++;
}

static void AddAll(Seq_t *seq, Seq_t *src) {
	for (uint32_t i = 0; i < Seq.GetLength(src); i++)
		Seq.Add(seq, Seq.Get(src, i));
}

static uint32_t GetLength(Seq_t *seq) {
	return seq->_Length;
}

static any *Get(Seq_t *seq, const uint32_t idx) {
	if (Seq.GetLength(seq) <= idx) {
		Error.Panic(u8"\e[35m", u8"Seq.Get");
	}
	return seq->_Item[idx];
}

static any *GetLast(Seq_t *seq) {
	return seq->_Item[seq->_Length - 1];
}

static Seq_t *GetHeadSeq(Seq_t *seq) {
	if (Seq.GetLength(seq) == 0) {
		Error.Panic(u8"\e[35m", u8"Seq.GetHeadSeq");
	}

	Seq_t *head = Seq.Duplicate(seq);
	Seq.Add(head, Seq.Get(seq, 0));

	return head;
}

static Seq_t *GetTailSeq(Seq_t *seq) {
	Seq_t *tail = Seq.Duplicate(seq);

	for (uint32_t i = 1; i < Seq.GetLength(seq); i++)
		Seq.Add(tail, seq->Get(seq, i));

	return tail;
}

static Seq_t *Duplicate(Seq_t *seq) {
	return Seq.New(Seq.GetStringiser(seq));
}

static bool IsEmpty(Seq_t *seq) {
	return seq->_Length == 0;
}

static void Delete(Seq_t *seq) {
	for (uint32_t i = 0; i < Seq.GetLength(seq); i++)
		Memory.Free(seq->_Item[i]);

	Memory.Free(seq);
}

static Seq_t *New(String_t *(* stringiser)(any *item)) {
	Seq_t *seq = (Seq_t *)(Memory.Allocate(sizeof(Seq_t)));

	seq->_Size			= Seq._ALLOCATION_BLOCK_SIZE;
	seq->_Length		= 0;
	seq->_Item			= Memory.CountedAllocate(Seq._ALLOCATION_BLOCK_SIZE, sizeof(any *));
	seq->_Stringiser	= stringiser;

	seq->GetStringiser			= GetStringiser;
	seq->Add					= Add;
	seq->AddAll					= AddAll;
	seq->GetLength				= GetLength;
	seq->Get					= Get;
	seq->GetLast				= GetLast;
	seq->GetHeadSeq				= GetHeadSeq;
	seq->GetTailSeq				= GetTailSeq;
	seq->Duplicate				= Duplicate;
	seq->IsEmpty				= IsEmpty;
	seq->Delete					= Delete;

	return seq;
}

static String_t *STRINGISER_STRING(any *item) {
	return item;
}

_Seq Seq = {
	._ALLOCATION_BLOCK_SIZE		= 1000,
	.STRINGISER_STRING			= STRINGISER_STRING,

	.New						= New,
	.Delete						= Delete,

	.GetStringiser				= GetStringiser,

	.Add						= Add,
	.AddAll						= AddAll,

	.GetLength					= GetLength,
	.Get						= Get,

	.GetLast					= GetLast,

	.GetHeadSeq					= GetHeadSeq,
	.GetTailSeq					= GetTailSeq,

	.Duplicate					= Duplicate,

	.IsEmpty					= IsEmpty,
};
