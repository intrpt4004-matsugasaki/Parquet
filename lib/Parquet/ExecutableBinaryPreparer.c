#include "Parquet/ExecutableBinaryPreparer.h"

static void Realise(String_t *AsmFilePath, String_t *ObjFilePath, String_t *ExecFilePath) {
	/* Assemble */
	String_t *cmd = String.Concat(String.New(u8"as -o "), ObjFilePath);
	cmd = String.Concat(cmd, String.New(u8" "));
	cmd = String.Concat(cmd, AsmFilePath);

	int32_t statusCode = system(String.GetPrimitive(cmd));

	if (!WIFEXITED(statusCode))
		Error.Panic(u8"\e[91m", u8"ExecutableBinaryPreparer/Realise/as");


	/* Link */
	cmd = String.Concat(String.New(u8"ld -o "), ExecFilePath);
	cmd = String.Concat(cmd, String.New(u8" "));
	cmd = String.Concat(cmd, ObjFilePath);

	statusCode = system(String.GetPrimitive(cmd));

	if (!WIFEXITED(statusCode))
		Error.Panic(u8"\e[91m", u8"ExecutableBinaryPreparer/Realise/ld");
}

_ExecutableBinaryPreparer ExecutableBinaryPreparer = {
	.Realise = Realise,
};
