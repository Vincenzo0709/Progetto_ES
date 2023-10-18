#include "demo_system.h"
#include "dev_access.h"

#include "md5.h"
#include "img.h"

size_t memprint(const void *src, size_t len)
{
    size_t i;
    for (i = 0; i < len; i++) {
        uint8_t byte = ((uint8_t *)src)[i];
        uint8_t high = byte / 16;
        uint8_t low = byte % 16;
        putchar(high + ((high >= 0xa) ? 'W' : '0'));
        putchar(low + ((low >= 0xa) ? 'W' : '0'));
    }
    
    return i;
}

uint8_t hash[16];
uint8_t cdi[16];

void main(void)
{
	puts("hashTrue:\n\t");
	memprint(hashTrue, 16);
	puts("\n\n");
	
	md5(hash, (uint8_t *)0x00100000, len);
	
	puts("hash:\n\t");
	memprint(hash, 16);
	puts("\n\n");
	
	if (memcmp(hashTrue, hash, 16) != 0) {
		puts("hashTrue != hash\n");
		puts("Code in RAM will not be executed\n");
		while (1);
	}
	
	puts("hashTrue == hash\n");
	puts("Code in RAM will be executed\n\n");
	
	hmac(cdi, "FrateMerola", 11, hash, 16);
	
	puts("cdi:\n\t");
	memprint(cdi, 16);
	puts("\n");
}
