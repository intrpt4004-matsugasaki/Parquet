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

static void AddAll(List_t *l, List_t *src) {
	for (uint32_t i = 0; i < List.GetLength(src); i++)
		List.Add(l, List.Get(src, i));
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

static List_t *GetHeadList(List_t *l) {
	if (List.GetLength(l) == 0) {
		Error.Panic(u8"\e[35m", u8"List.GetHeadList");
	}

	List_t *head = List.New();
	List.Add(head, List.Get(l, 0));

	return head;
}

static List_t *GetTailList(List_t *l) {
	List_t *tail = List.New();

	for (uint32_t i = 1; i < List.GetLength(l); i++)
		List.Add(tail, l->Get(l, i));

	return tail;
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

	l->Add			= Add;
	l->AddAll		= AddAll;
	l->GetLength	= GetLength;
	l->Get			= Get;
	l->GetHeadList	= GetHeadList;
	l->GetTailList	= GetTailList;
	l->IsEmpty		= IsEmpty;
	l->Delete		= Delete;

	return l;
}

_List List = {
	._ALLOCATION_BLOCK_SIZE		= 1000,

	.New						= New,
	.Delete						= Delete,

	.Add						= Add,
	.AddAll						= AddAll,

	.GetLength					= GetLength,
	.Get						= Get,

	.GetHeadList				= GetHeadList,
	.GetTailList				= GetTailList,

	.IsEmpty					= IsEmpty,
};
