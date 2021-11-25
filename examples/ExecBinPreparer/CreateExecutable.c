#include <Parquet.h>

void main() {
	printf("%s\n\t-> %s\n",
		u8"../examples/ExecBinPreparer/HelloWorld.s",
		u8"./HelloWorld"
	);

	ExecBinPreparer.Deploy(
		String.New(u8"../examples/ExecBinPreparer/HelloWorld.s"),
		String.New(u8"./HelloWorld")
	);
}
