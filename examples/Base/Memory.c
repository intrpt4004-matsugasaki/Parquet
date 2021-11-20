#include <Parquet.h>

void main() {
	int32_t *p = Memory.Allocate(sizeof(int32_t));
	*p = 3; printf("%d\n", *p);
	int32_t *a = Memory.CountedAllocate(10, sizeof(int32_t));
	a[2] = 4; printf("%d\n", a[2]);
	a = Memory.ReAllocate(a, 100 * sizeof(int32_t));
	a[99] = 99; printf("%d\n", a[99]);

	Memory.Free(p);
	Memory.Free(a);
}
