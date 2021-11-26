#include "Printer.h"

static void Stack(Printer_t *p, String_t *text) {
	List.Add(p->_Stack, String.Copy(text));
}

static void Space(Printer_t *p) {
	List.Add(p->_Stack, String.New(u8" "));
}

static void Feed(Printer_t *p) {
	List.Add(p->_Stack, String.New(u8"\n"));

	for (uint32_t i = 0; i < p->_Indents; i++)
		List.Add(p->_Stack, p->_Indent);
}

static void Elevate(Printer_t *p) {
	p->_Indents++;
}

static void Demote(Printer_t *p) {
	if (p->_Indents == 0) return;

	p->_Indents--;
}

static void Dump(Printer_t *p) {
	for (uint32_t i = 0; i < List.GetLength(p->_Stack); i++)
		printf("%s", List.Get(p->_Stack, i));
}

static Printer_t *New() {
	Printer_t *p = (Printer_t *)(Memory.Allocate(sizeof(Printer_t)));

	p->_Stack	= List.New();
	p->_Indents	= 0;
	p->_Indent	= String.New(u8"  ");

	p->Stack	= Stack;
	p->Space	= Space;
	p->Feed		= Feed;
	p->Elevate	= Elevate;
	p->Demote	= Demote;
	p->Dump		= Dump;

	return p;
}

static void Delete(Printer_t *p) {
	List.Delete(p->_Stack);
	String.Delete(p->_Indent);
	Memory.Free(p);
}

_Printer Printer = {
	.New	= New,
	.Delete	= Delete,
};
