#include "Printer.h"

static void Stack(Printer_t *p, String_t *text) {
	List.Add(p->_Stack, String.Copy(text));
	p->_LastIndex++;
}

static void Space(Printer_t *p) {
	List.Add(p->_Stack, String.New(u8" "));
}

static void Feed(Printer_t *p) {
	List.Add(p->_Stack, String.New(u8"\n"));
	p->_Line++;
}

static void Advance(Printer_t *p) {
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

static void Entry(Printer_t *p) {
	p->_Entry = true;
	//p->_IndentCnt = p->_Indents;
}

static bool CursorIsInInside(Printer_t *p) {
	return p->_Entry;
}

static void Escape(Printer_t *p) {
	p->_Entry = false;
}

static void Dump(Printer_t *p) {
	for (uint32_t i = 0; i < List.GetLength(p->_Stack); i++)
		printf("\e[2m%s\e[0m", String.GetPrimitive(List.Get(p->_Stack, i)));
}

static uint32_t GetLine(Printer_t *p) {
	return p->_Line;
}

static uint32_t GetLastIndex(Printer_t *p) {
	return p->_LastIndex;
}

static Printer_t *New() {
	Printer_t *p = (Printer_t *)(Memory.Allocate(sizeof(Printer_t)));

	p->_Stack		= List.New();
	p->_Indents		= 0;
	p->_Indent		= String.New(u8"  ");
	p->_Entry		= false;
	p->_IndentCnt	= 0;
	p->_Line		= 1;
	p->_LastIndex	= 0;

	p->Stack			= Stack;
	p->Space			= Space;
	p->Feed				= Feed;
	p->Advance			= Advance;
	p->Elevate			= Elevate;
	p->Demote			= Demote;
	p->Entry			= Entry;
	p->CursorIsInInside	= CursorIsInInside;
	p->Escape			= Escape;
	p->Dump				= Dump;
	p->GetLine			= GetLine;
	p->GetLastIndex		= GetLastIndex;

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
