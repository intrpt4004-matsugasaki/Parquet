#include <Parquet.h>

void main() {
	List_t *lis = List.New();

	lis->Add(lis, String.New(u8"test string"));
	lis->Add(lis, String.New(u8"test string 2"));
	lis->Add(lis, String.New(u8"test string 3"));

	for (uint32_t i = 0; i < lis->GetLength(lis); i++) {
		printf("%s\n", String.GetPrimitive(lis->Get(lis, i)));
	}

	lis->Delete(lis);
	printf("\n");


	/* 大量確保/解放 */
	lis = List.New();

	const uint32_t SIZE = 5000;	
	for (uint32_t i = 0; i < SIZE; i++) {
		lis->Add(lis, String.New("*****"));

		if (i % List._ALLOCATION_BLOCK_SIZE == 999)
			printf("%d\n", lis->GetLength(lis));
	}

	List.Delete(lis);
}
