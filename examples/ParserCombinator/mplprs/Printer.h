#pragma once

#include <Parquet.h>

#include <stdio.h>

typedef struct Printer_t {
	List_t *_Stack;

	uint32_t _Indents;
	String_t *_Indent;

	uint32_t _Line;
	uint32_t _LastIndex;

	void (* Stack)(struct Printer_t *, String_t *text);

	void (* Space)(struct Printer_t *);
	void (* Feed)(struct Printer_t *);
	void (* Advance)(struct Printer_t *);

	void (* Elevate)(struct Printer_t *);
	void (* Demote)(struct Printer_t *);

	void (* Dump)(struct Printer_t *);
	uint32_t (* GetLine)(struct Printer_t *);
	uint32_t (* GetLastIndex)(struct Printer_t *);
} Printer_t;

typedef struct {
	Printer_t *(* New)();
	void (* Delete)(Printer_t *);
} _Printer;

extern _Printer Printer;
