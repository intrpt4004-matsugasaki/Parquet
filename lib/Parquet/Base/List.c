#include "Parquet/Base/List.h"

static void Add(List_t *l, any *item) {
	if (List.GetLength(l) + 1 >= l->_Size) {
		l->_Size += List._ALLOCATION_BLOCK_SIZE;
		l->_Item = Memory.ReAllocate(
			l->_Item,
			l->_Size * sizeof(any *)
		);
	}

	l->_Item[List.GetLength(l)] = item;
	l->_Length++;
}

static uint32_t GetLength(List_t *l) {
	return l->_Length;
}

static any *Get(List_t *l, const uint32_t idx) {
	if (List.GetLength(l) <= idx) {
		Error.Panic(u8"\e[35m", u8"List.Get");
	}
	return l->_Item[idx];
}

static bool IsEmpty(List_t *l) {
	return l->_Length == 0;
}

static void Delete(List_t *l) {
	for (uint32_t i = 0; i < List.GetLength(l); i++)
		Memory.Free(l->_Item[i]);

	Memory.Free(l);
}

static List_t *New() {
	List_t *l = (List_t *)(Memory.Allocate(sizeof(List_t)));

	l->_Size		= List._ALLOCATION_BLOCK_SIZE;
	l->_Length		= 0;
	l->_Item		= Memory.CountedAllocate(List._ALLOCATION_BLOCK_SIZE, sizeof(any *));

	l->Add								= Add;
	l->GetLength						= GetLength;
	l->Get								= Get;
	l->IsEmpty							= IsEmpty;
	l->Delete							= Delete;

	return l;
}

_List List = {
	._ALLOCATION_BLOCK_SIZE			= 1000,

	.New							= New,
	.Delete							= Delete,

	.Add							= Add,

	.GetLength						= GetLength,
	.Get							= Get,

	.IsEmpty						= IsEmpty,
};
