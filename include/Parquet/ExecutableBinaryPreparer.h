#pragma once

#include <stdlib.h>

#include "Parquet/Base/String.h"

typedef struct {
	void (* Deploy)(String_t *AsmFilePath, String_t *ObjFilePath, String_t *ExecFilePath);
	void (* DeployExecutable)(String_t *AsmFilePath, String_t *ExecFilePath);
} _ExecutableBinaryPreparer;

extern _ExecutableBinaryPreparer ExecutableBinaryPreparer;
