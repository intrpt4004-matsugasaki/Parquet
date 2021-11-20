#include <Parquet.h>

void main() {
	printf("%s\n\t-> %s\n\t-> %s\n",
		u8"../examples/ExecutableBinaryPreparer/HelloWorld.s",
		u8"./HelloWorld.o",
		u8"./HelloWorld"
	);

	ExecutableBinaryPreparer.Realise(
		String.New(u8"../examples/ExecutableBinaryPreparer/HelloWorld.s"),
		String.New(u8"./HelloWorld.o"),
		String.New(u8"./HelloWorld")
	);
}
