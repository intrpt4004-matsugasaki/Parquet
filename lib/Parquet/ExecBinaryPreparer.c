#include "Parquet/ExecBinaryPreparer.h"

static void DeployAll(String_t *AsmFilePath, String_t *ObjFilePath, String_t *ExecFilePath) {
	/* Assemble */
	String_t *cmd = String.Concat(String.New(u8"as -o "), ObjFilePath);
	cmd = String.Concat(cmd, String.New(u8" "));
	cmd = String.Concat(cmd, AsmFilePath);

	int32_t statusCode = system(String.GetPrimitive(cmd));

	if (!WIFEXITED(statusCode))
		Error.Panic(u8"\e[91m", u8"ExecBinaryPreparer#Deploy/as");


	/* Link */
	cmd = String.Concat(String.New(u8"ld -o "), ExecFilePath);
	cmd = String.Concat(cmd, String.New(u8" "));
	cmd = String.Concat(cmd, ObjFilePath);

	statusCode = system(String.GetPrimitive(cmd));

	if (!WIFEXITED(statusCode))
		Error.Panic(u8"\e[91m", u8"ExecBinaryPreparer#Deploy/ld");
}

static void Deploy(String_t *AsmFilePath, String_t *ExecFilePath) {
	String_t *obj = String.Concat(ExecFilePath, String.New(u8".o"));
	ExecBinaryPreparer.DeployAll(AsmFilePath, obj, ExecFilePath);

	/* Remove .o */
	int32_t statusCode = system(String.GetPrimitive(
		String.Concat(String.New(u8"rm -f "), obj)
	));

	if (!WIFEXITED(statusCode))
		Error.Panic(u8"\e[91m", u8"ExecBinaryPreparer#DeployExecutable/rm");
}

_ExecBinaryPreparer ExecBinaryPreparer = {
	.DeployAll	= DeployAll,
	.Deploy		= Deploy,
};
