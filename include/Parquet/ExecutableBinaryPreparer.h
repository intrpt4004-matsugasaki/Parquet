#pragma once

#include <stdlib.h>

#include "Parquet/Base/String.h"

typedef struct {
	void (* Realise)(String_t *AsmFilePath, String_t *ObjFilePath, String_t *ExecFilePath);
} _ExecutableBinaryPreparer;

extern _ExecutableBinaryPreparer ExecutableBinaryPreparer;
