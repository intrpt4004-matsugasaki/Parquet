#include <Parquet.h>

void main() {
	printf("%s\n\t-> %s\n",
		u8"../examples/ExecutablePreparer/HelloWorld.s",
		u8"./HelloWorld"
	);

	ExecutablePreparer.Deploy(
		String.New(u8"../examples/ExecutablePreparer/HelloWorld.s"),
		String.New(u8"./HelloWorld")
	);
}
