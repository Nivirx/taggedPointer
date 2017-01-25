#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

//Bitmask to mask the lower 7 bytes, use NOT to mask MSB
#define USABLE_PTR		0x00ffffffffffffff

//Mask first byte of a (uint64_t)*  and return a (uint64_t)*
#define DETAG_64(a)		(uint64_t*)((uintptr_t)a & (uintptr_t)USABLE_PTR))

//Return the first byte of a (uint64_t)* as a uint8_t
#define RETTAG_64(a)	(uint8_t)( ((uintptr_t)a & ~USABLE_PTR) >> 56 )

//Generates a (uint64_t*) mask from a byte (uint8_t)
#define BYTE_TAG_64(a)	(uint64_t*)( ((uintptr_t)a) << 56  )

int main(int argc, char** argv) {
	uint64_t* ptr1 = (uint64_t*)malloc(sizeof(uint64_t));
	*ptr1 = 1735;

	uint64_t* taggedPtr = BYTE_TAG_64(0xAC);
	printf("tag: %p\n", taggedPtr);

	taggedPtr = (uint64_t*)((uintptr_t)ptr1 | (uintptr_t)taggedPtr);

	printf("Ptr1: %p\n", ptr1);
	printf("taggedPtr: %p\n", taggedPtr);

	printf("%ld\n", *ptr1);
	printf("%ld\n", *DETAG_64(taggedPtr);
	printf("The tag is %x\n", RETTAG_64(taggedPtr));

	free(ptr1);
	return 0;
}
