#include <Parquet.h>

void main() {
	printf("%s\n\t-> %s\n",
		u8"../examples/ExecBinaryPreparer/HelloWorld.s",
		u8"./HelloWorld"
	);

	ExecBinaryPreparer.Deploy(
		String.New(u8"../examples/ExecBinaryPreparer/HelloWorld.s"),
		String.New(u8"./HelloWorld")
	);
}
