#pragma once

#include <stdlib.h>

#include "Parquet/Base/String.h"

typedef struct {
	void (* DeployAll)(String_t *AsmFilePath, String_t *ObjFilePath, String_t *ExecFilePath);
	void (* Deploy)(String_t *AsmFilePath, String_t *ExecFilePath);
} _ExecBinaryPreparer;

extern _ExecBinaryPreparer ExecBinaryPreparer;
