#include "SymbolTableBuilder.h"

static SymbolTableBuilder_t *New() {
	SymbolTableBuilder_t *p = (SymbolTableBuilder_t *)(Memory.Allocate(sizeof(SymbolTableBuilder_t)));

	return p;
}

static void Delete(SymbolTableBuilder_t *p) {
	Memory.Free(p);
}

_SymbolTableBuilder SymbolTableBuilder = {
	.New	= New,
	.Delete	= Delete,
};
